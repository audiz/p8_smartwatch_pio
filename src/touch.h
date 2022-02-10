/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include "touch_data.h"

#define TOUCH_NO_GESTURE 0x00
#define TOUCH_SLIDE_DOWN 0x01
#define TOUCH_SLIDE_UP 0x02
#define TOUCH_SLIDE_LEFT 0x03
#define TOUCH_SLIDE_RIGHT 0x04
#define TOUCH_SINGLE_CLICK 0x05
#define TOUCH_DOUBLE_CLICK 0x0B
#define TOUCH_LONG_PRESS 0x0C

void init_touch();
void sleep_touch(bool state);
void set_new_touch_interrupt();
bool get_new_touch_interrupt();
bool get_was_touched();
void set_was_touched(bool state);
void get_read_touch();
touch_data_struct get_touch();
