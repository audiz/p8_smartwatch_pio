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

class StatScreen : public Screen
{
public:
  virtual void pre()
  {
    set_gray_screen_style(&lv_font_roboto_28);

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Stat screen");
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -60);

    minHr_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(minHr_label, "%i", min_hr);
    lv_label_set_align(minHr_label, LV_ALIGN_IN_BOTTOM_LEFT);
    lv_obj_align(minHr_label, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    maxHr_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(maxHr_label, "%i", max_hr);
    lv_label_set_align(maxHr_label, LV_ALIGN_IN_TOP_LEFT);
    lv_obj_align(maxHr_label, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

    avgHr_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(avgHr_label, "%i", avg_hr);
    lv_label_set_align(avgHr_label, LV_ALIGN_IN_LEFT_MID);
    lv_obj_align(avgHr_label, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 0);

  }

  virtual void main()
  {
  }

  virtual void left()
  {
    display_home();
  }

  void setHRM(uint8_t data)
  {
    avg_hr = data;

    if (min_hr == 0 || min_hr > data) {
      min_hr = data;
    }

    if (max_hr == 0 || max_hr < data) {
      max_hr = data;
    }

    if (is_current_screen(this))
    {
        lv_label_set_text_fmt(minHr_label, "%i", min_hr);
        lv_obj_align(minHr_label, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

        lv_label_set_text_fmt(maxHr_label, "%i", max_hr);
        lv_obj_align(maxHr_label, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

        lv_label_set_text_fmt(avgHr_label, "%i", avg_hr);
        lv_obj_align(avgHr_label, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 0);
    }
  }

private:
  lv_obj_t *label;
  lv_obj_t *minHr_label;
  lv_obj_t *maxHr_label;
  lv_obj_t *avgHr_label;
  short min_hr = 0;
  short max_hr = 0;
  short avg_hr = 0;
};

inline StatScreen statScreen;
