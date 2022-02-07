#pragma once
#include "Arduino.h"

#include "pinout.h"
#include "inputoutput.h"
#include "bluefruit.h"

/* HRM Service Definitions
 * Heart Rate Monitor Service:  0x180D
 * Heart Rate Measurement Char: 0x2A37 (Mandatory)
 * Body Sensor Location Char:   0x2A38 (Optional)
 */

#define UUID16_SVC_HEART_RATE                                 0x180D

void hrm_notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len);
void disconnect_callback(uint16_t conn_handle, uint8_t reason);
void connect_callback(uint16_t conn_handle);
void scan_callback(ble_gap_evt_adv_report_t* report);
void scan_stop_callback(void);
void disable_ble();
void enable_ble();

void init_ant_client();
