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

extern void mks_layout_init();
extern void mks_layout_event(lv_obj_t * obj, lv_event_t event);
extern void mks_layout_callback(mks_layout_item_t item, lv_obj_t * parent);

void mks_create_main_panel(lv_obj_t * parent);

#if LV_USE_ANIMATION
  void tab_content_anim_create(lv_obj_t * parent);
  void tab_changer_task_cb(lv_task_t * task);
#endif

#if LV_USE_THEME_MATERIAL
  extern void mks_color_chg_event_cb(lv_obj_t * sw, lv_event_t e);
#endif

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
#endif