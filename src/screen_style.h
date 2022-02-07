/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

//#pragma once
#ifndef screen_style_h
#define screen_style_h

#include "Arduino.h"
#include <lvgl.h>

void set_gray_screen_style( lv_font_t * font = LV_FONT_DEFAULT);

void set_main_color(int new_color);

void set_grad_color(int new_color);

void set_font_color(int new_color);

int get_main_color();

int get_grad_color();

int get_font_color();

#endif