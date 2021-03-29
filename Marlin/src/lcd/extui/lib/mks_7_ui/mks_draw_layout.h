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

#include "../../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_7_UI

#include <stdio.h>

#ifdef __cplusplus
  extern "C" { /* C-declarations for C++ */
#endif

#include <lvgl.h>

enum {
  DEFAULT,
  MKS_UI
};
typedef uint8_t mks_layout_t;

enum {
  MKS_LAYOUT_INIT,
  MKS_LAYOUT_MAIN_PANEL,
  MKS_LAYOUT_REFRESH
};
typedef uint8_t mks_layout_item_t;

typedef void (*mks_layout_cb)(mks_layout_item_t item, lv_obj_t * parent);

extern void mks_clear_disp();

extern void mks_add_rotary_group(lv_obj_t * obj);
extern void mks_layout_set_cb(mks_layout_cb l);
extern void mks_draw_layout_load();
extern void mks_draw_layout();

extern lv_obj_t * mks_draw_button(const char * name, uint16_t id, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);
extern lv_obj_t * mks_draw_label(const char * msg, uint16_t id, lv_align_t alignLabel, lv_align_t alignObj, lv_coord_t x_ofs, lv_coord_t y_ofs);
extern void mks_change_label_text(lv_obj_t * obj, const char * msg, lv_align_t alignLabel);

extern void mks_event_handler(lv_obj_t * obj, lv_event_t event);

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
#endif