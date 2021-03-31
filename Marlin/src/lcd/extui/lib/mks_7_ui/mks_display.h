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

#ifdef __cplusplus
  extern "C" { /* C-declarations for C++ */
#endif

#ifndef PGM_P
  #define PGM_P const char *
#endif

//#define LV_COLOR_BACKGROUND LV_COLOR_MAKE(0x1A, 0x1A, 0x1A)

extern void mks_init_spi();
extern void mks_lv_register();
extern void mks_draw_error_message(PGM_P const msg);
extern void mks_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p);
extern void mks_disp_string(uint16_t x, uint16_t y, const char * string, uint16_t charColor, uint16_t bkColor);
extern void mks_disp_char_1624(uint16_t x, uint16_t y, uint8_t c, uint16_t charColor, uint16_t bkColor);

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
#endif