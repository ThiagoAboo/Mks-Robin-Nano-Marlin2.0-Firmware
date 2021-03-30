/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "../../../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_7_UI

#ifdef __cplusplus
  extern "C" { /* C-declarations for C++ */
#endif

#include <lvgl.h>
#include "mks_layout_style.h"

extern void mks_layout_status(lv_obj_t * parent, lv_event_cb_t event);
extern void mks_layout_status_update();

void mks_layout_status_container(lv_obj_t * parent);
void mks_layout_status_temp(lv_event_cb_t event, mks_layout_item_t item);
void mks_layout_status_position(lv_event_cb_t event);
const char * mks_layout_status_temp_value(mks_layout_item_t item, uint8_t index);

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
#endif