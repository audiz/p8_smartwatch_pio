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

#include "pinout.h"
#include "inputoutput.h"
#include "antclient.h"
#include "menu_Home.h"
#include "watchdog.h"
#include "fast_spi.h"
#include "i2c.h"
#include "backlight.h"
#include "display.h"
#include "screen_style.h"
#include "sleep.h"
#include "interrupt.h"

HomeScreen* bootScreenPtr = HomeScreen::getInstance();

void setup() {
  //Serial.begin(9600);
  initRTC2();
  init_fast_spi();//needs to be before init_display and external flash
  init_i2c();//needs to be before init_hrs3300, init_touch and init_accl
  init_inputoutput();
  init_backlight();
  init_display();
  set_backlight(3);
  init_battery();

  bootScreenPtr->init();

  init_ant_client();
  init_interrupt();//must be after ble!!!

  pinMode(STATUS_LED, OUTPUT);
}

void loop() {
  //sd_app_evt_wait();

  /*if (get_button()) {
    if(ledState) {
       disable_ble();
       set_backlight(0);
       display_enable(false);
       //disable_hardware();
       sleep_wait();
       ledState = LOW;
    } else {
      if (!Bluefruit.connected()) {
        bootScreenPtr->setHRM("HRM");
        enable_ble();
      }
      set_backlight(1);
      display_enable(true);
      ledState = HIGH;
    }
    //digitalWrite(STATUS_LED, ledState);
    delay(1000);
  }*/

   gets_interrupt_flag();//check interrupt flags and do something with it
}