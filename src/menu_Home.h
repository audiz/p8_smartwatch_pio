/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#pragma once

#ifndef MENU_HOME
#define MENU_HOME 1
#endif

#if MENU_HOME

#include "Arduino.h"
#include "class.h"
#include "display.h"
#include "ble.h"
#include "screen_style.h"
#include <lvgl.h>
#include "battery.h"


class HomeScreen : public Screen
{
public:
  static HomeScreen *getInstance();

  virtual void init();

  virtual void setBleInfo(const char *text);

  virtual void setHRM(uint8_t data);

  virtual void setHRM(const char *text);

  virtual void pre()
  {

  }

  virtual void main()
  {

  }

  virtual void up()
  {
    inc_vars_menu();
  }

  virtual void down()
  {
    dec_vars_menu();
  }

  virtual void left()
  {
  }

  virtual void right()
  {
  }

  virtual void button_push(int length)
  {
    sleep_down();
  }

private:
  lv_obj_t *label_battery;
  lv_obj_t *label;
  lv_obj_t *status_label;
  lv_obj_t *ble_label;
  lv_style_t st;
  /* Here will be the instance stored. */
  static HomeScreen *instance;
  /* Private constructor to prevent instancing. */
  HomeScreen();
};

#endif