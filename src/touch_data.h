/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Arduino.h"

struct touch_data_struct {
  byte gesture;
  byte touchpoints;
  byte event;
  int xpos;
  int ypos;
  int last_xpos;
  int last_ypos;
  uint8_t version15;
  uint8_t versionInfo[3];
};