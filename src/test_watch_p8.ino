/**
 * @file sketch_jan11a_test_watch_p8.ino
 * 
 * https://community.platformio.org/t/custom-nrf52832-board-pinout/24491/4
 * 
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//#define NRF_SDH_CLOCK_LF_SRC 0
//#define NRF_SDH_CLOCK_LF_RC_CTIV 16
//#define NRF_SDH_CLOCK_LF_RC_TEMP_CTIV 2
//#define NRF_SDH_CLOCK_LF_ACCURACY 1

/* HRM Service Definitions
 * Heart Rate Monitor Service:  0x180D
 * Heart Rate Measurement Char: 0x2A37 (Mandatory)
 * Body Sensor Location Char:   0x2A38 (Optional)
 */
#include "pinout.h"
#include "inputoutput.h"
#include "bluefruit.h"

#define UUID16_SVC_HEART_RATE                                 0x180D

BLEClientService        hrms(UUID16_SVC_HEART_RATE);
BLEClientCharacteristic hrmc(UUID16_CHR_HEART_RATE_MEASUREMENT);
BLEClientCharacteristic bslc(UUID16_CHR_BODY_SENSOR_LOCATION);

#include "menu_Boot.h"
#include "watchdog.h"
#include "fast_spi.h"
#include "i2c.h"
#include "backlight.h"
#include "display.h"
#include "screen_style.h"
#include "sleep.h"

uint16_t conn_handle_main;

void setup() {
  //Serial.begin(9600);
  init_fast_spi();//needs to be before init_display and external flash
  //init_i2c();//needs to be before init_hrs3300, init_touch and init_accl
  init_inputoutput();
  init_backlight();
  init_display();
  set_backlight(3);
  init_battery();

  bootScreen.init();

  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH);

  // Initialize Bluefruit with maximum connections as Peripheral = 0, Central = 1
  // SRAM usage required by SoftDevice will increase dramatically with number of connections
  Bluefruit.begin(0, 1);
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  //Bluefruit.setTxPower(-40);

  /* Set the device name */
  Bluefruit.setName("Bluefruit52 Central");

  // Initialize HRM client
  hrms.begin();

  // Initialize client characteristics of HRM.
  // Note: Client Char will be added to the last service that is begin()ed.
  bslc.begin();

  // set up callback for receiving measurement
  hrmc.setNotifyCallback(hrm_notify_callback);
  hrmc.begin();

  Bluefruit.setConnLedInterval(250);

  // Callbacks for Central
  Bluefruit.Central.setDisconnectCallback(disconnect_callback);
  Bluefruit.Central.setConnectCallback(connect_callback);

  /* Start Central Scanning
   * - Enable auto scan if disconnected
   * - Interval = 100 ms, window = 80 ms
   * - Don't use active scan
   * - Filter only accept HRM service
   * - Start(timeout) with timeout = 0 will scan forever (until connected)
   */
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.setStopCallback(scan_stop_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  //Bluefruit.Scanner.filterUuid(hrms.uuid);
  Bluefruit.Scanner.useActiveScan(false); // Request scan response data
  Bluefruit.Scanner.start(0);                   // // 0 = Don't stop scanning after n seconds
  digitalWrite(STATUS_LED, LOW);
 
  bootScreen.setBleInfo("BLE ... ");
}

int ledState = HIGH;

void loop() {
  if (get_button()) {
    if(ledState) {
       bootScreen.setHRM("HRM");
       Bluefruit.Scanner.restartOnDisconnect(false);
       Bluefruit.disconnect(conn_handle_main);
       //set_backlight(0);
       //display_enable(false);
       disable_hardware();
       ledState = LOW;
    } else {
      if (!Bluefruit.connected()) {
        bootScreen.setHRM("HRM");
        Bluefruit.Scanner.restartOnDisconnect(true);
        Bluefruit.begin(0, 1);
        Bluefruit.Scanner.start(0);  
      }
      set_backlight(1);
      display_enable(true);
      ledState = HIGH;
    }
    //digitalWrite(STATUS_LED, ledState);
    delay(1000);
  
  }
}

/**
 * Callback invoked when scanner pick up an advertising data
 * @param report Structural advertising data
 */
void scan_callback(ble_gap_evt_adv_report_t* report)
{
  //digitalWrite(STATUS_LED, HIGH);
  // Since we configure the scanner with filterUuid()
  // Scan callback only invoked for device with hrm service advertised
  // Connect to device with HRM service in advertising
  bootScreen.setBleInfo("scan");
  Bluefruit.Central.connect(report);
}

/**
 * Callback invoked when scanner pick up an advertising data
 * @param report Structural advertising data
 */
void scan_stop_callback(void)
{
  //digitalWrite(STATUS_LED, HIGH);
  bootScreen.setBleInfo("stop_callback");
}


/**
 * Callback invoked when an connection is established
 * @param conn_handle
 */
void connect_callback(uint16_t conn_handle)
{
  
  conn_handle_main &= conn_handle;
  //digitalWrite(STATUS_LED, HIGH);
  //Serial.println("Connected");
  //Serial.print("Discovering HRM Service ... ");
  bootScreen.setBleInfo("connect");

  // If HRM is not found, disconnect and return
  if ( !hrms.discover(conn_handle) )
  {
    // disconnect since we couldn't find HRM service
    Bluefruit.disconnect(conn_handle);

    return;
  }
  // Once HRM service is found, we continue to discover its characteristic

  //Serial.print("Discovering Measurement characteristic ... ");
  if ( !hrmc.discover() )
  {
    // Measurement chr is mandatory, if it is not found (valid), then disconnect
    //Serial.println("Measurement characteristic is mandatory but not found");
    Bluefruit.disconnect(conn_handle);
    return;
  }

  // Measurement is found, continue to look for option Body Sensor Location
  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.body_sensor_location.xml
  // Body Sensor Location is optional, print out the location in text if present
  //Serial.print("Discovering Body Sensor Location characteristic ... ");
  if ( bslc.discover() )
  {
    // Body sensor location value is 8 bit
    const char* body_str[] = { "Other", "Chest", "Wrist", "Finger", "Hand", "Ear Lobe", "Foot" };

    // Read 8-bit BSLC value from peripheral
    uint8_t loc_value = bslc.read8();
    
    //Serial.print("Body Location Sensor: ");
    //Serial.println(body_str[loc_value]);
  } else {
    //Serial.println("Found NONE");
  }

  // Reaching here means we are ready to go, let's enable notification on measurement chr
  if ( hrmc.enableNotify() )
  {
    //Serial.println("Ready to receive HRM Measurement value");
  }else
  {
    //Serial.println("Couldn't enable notify for HRM Measurement. Increase DEBUG LEVEL for troubleshooting");
  }
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  //digitalWrite(STATUS_LED, HIGH);
  (void) conn_handle;
  (void) reason;
  bootScreen.setBleInfo("disconnect");
  //tftPrintInfo(String(MSG_DISCONNECTED) + String(": ") + String(retries));
  //Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

/**
 * Hooked callback that triggered when a measurement value is sent from peripheral
 * @param chr   Pointer client characteristic that even occurred,
 *              in this example it should be hrmc
 * @param data  Pointer to received data
 * @param len   Length of received data
 */
void hrm_notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len)
{
  //bootScreen.setBleInfo("Data received ... ");
  //digitalWrite(STATUS_LED, HIGH);
  //bootScreen.setBleInfo("hrm_notify_callback ... ");

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.heart_rate_measurement.xml
  // Measurement contains of control byte0 and measurement (8 or 16 bit) + optional field
  // if byte0's bit0 is 0 --> measurement is 8 bit, otherwise 16 bit.
  //Serial.print("HRM Measurement: ");
  //bootScreen.setBleInfo("hrm_notify_callback ... ");

  if ( data[0] & bit(0) )
  {
    uint16_t value;
    memcpy(&value, data+1, 2);
    //Serial.println(value);
  }
  else
  {
    //bootScreen.setBleInfo("Data 2 received ... ");
    bootScreen.setHRM(data[1]);
    //Serial.println(data[1]);
  }
}
