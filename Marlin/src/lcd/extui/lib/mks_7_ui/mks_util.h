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

#include <lvgl.h>

#define TICK_CYCLE        1

extern void lvgl_log(lv_log_level_t level, const char * file, uint32_t line, const char * fnName, const char * dsc);
extern unsigned int mks_getTickDiff(unsigned int curTick, unsigned int lastTick);
extern void mks_trace_start(const char * msg);
extern void mks_trace_end(const char * msg);
extern void mks_trace_end_start(const char * msg1, const char * msg2);
extern void mks_trace(const char * V, ...);

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
#endif