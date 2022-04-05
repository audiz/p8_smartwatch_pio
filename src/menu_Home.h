/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#pragma once

#include "Arduino.h"
#include "display.h"
#include "ble.h"
#include "screen_style.h"
#include <lvgl.h>
#include "battery.h"
#include "class.h"

class HomeScreen : public Screen
{
public:
  static HomeScreen *getInstance();

  virtual void touchData(touch_data_struct touch_data);

  virtual void setBleInfo(const char *text);

  virtual void setHRM(const char *text);

  virtual void setHRM(uint8_t data);

  virtual void pre();

  virtual void main()
  {

  }

  virtual void up()
  {
    //inc_vars_menu();
  }

  virtual void down()
  {
    //dec_vars_menu();
  }

  virtual void left()
  {
  }

  virtual void right();


  virtual void button_push(int length)
  {
    //sleep_down();
  }

private:
  lv_obj_t *label_battery;
  lv_obj_t *label;
  lv_obj_t *status_label;
  lv_obj_t *ble_label;
  lv_obj_t *minHr_label;
  lv_obj_t *maxHr_label;
  lv_obj_t *avgHr_label;
  lv_style_t st;
  const char *text_label = "Heart Rate";
  const char *text_ble_label = "HRM";
  const char *text_status_label = "search ant+";
  lv_obj_t * chart;
  lv_chart_series_t * ser1;
  /* Here will be the instance stored. */
  static HomeScreen *instance;
  /* Private constructor to prevent instancing. */
  HomeScreen();
};