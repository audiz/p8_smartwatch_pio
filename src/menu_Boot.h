/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
//#pragma once

#ifndef MENU_BOOT
#define MENU_BOOT 1
#endif

#if MENU_BOOT

#include "Arduino.h"
#include "display.h"
#include "ble.h"
#include "screen_style.h"
#include <lvgl.h>
#include "battery.h"

class BootScreen
{
  public:
   static BootScreen* getInstance();

   virtual void init();

   virtual void one();

   virtual void another();

   virtual void setBleInfo(const char * text);

   virtual void setHRM(uint8_t data);

   virtual void setHRM(const char * text);

  private:
    lv_obj_t *label_battery;
    lv_obj_t *label;
    lv_obj_t *status_label;
    lv_obj_t *ble_label;
    lv_style_t st;
    /* Here will be the instance stored. */
    static BootScreen* instance;
    /* Private constructor to prevent instancing. */
    BootScreen();
};

#endif