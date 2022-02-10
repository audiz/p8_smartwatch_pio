/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Arduino.h"
#include "class.h"
#include "menu.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "screen_style.h"
#include <lvgl.h>

class BootScreen : public Screen
{
public:
  virtual void pre()
  {
    set_gray_screen_style(&lv_font_roboto_28);

    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Booting\n"
                             "P8");
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -60);
  }

  virtual void main()
  {
  }

  virtual void right()
  {
    display_home();
  }

private:
};

BootScreen bootScreen;
