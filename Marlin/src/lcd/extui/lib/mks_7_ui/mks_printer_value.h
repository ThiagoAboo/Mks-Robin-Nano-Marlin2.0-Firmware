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

enum {
  MKS_VALUE_TEMP_EXTRUDER,
  MKS_VALUE_TEMP_BED,
  MKS_VALUE_TARGET_EXTRUDER,
  MKS_VALUE_TARGET_BED,
  MKS_VALUE_MIN_EXTRUDER,
  MKS_VALUE_MAX_EXTRUDER,
  MKS_VALUE_MIN_BED,
  MKS_VALUE_MAX_BED,
  MKS_WIFI_SSID,
  MKS_WIFI_PWS
};
typedef uint8_t mks_printer_value_t;

extern float mks_get_value(mks_printer_value_t item, uint8_t index);
extern const char * mks_get_valueChar(mks_printer_value_t item, uint8_t index);

extern void mks_set_value(mks_printer_value_t item, uint8_t index, float value);
extern void mks_set_valueChar(mks_printer_value_t item, uint8_t index, const char * value);

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
#endif