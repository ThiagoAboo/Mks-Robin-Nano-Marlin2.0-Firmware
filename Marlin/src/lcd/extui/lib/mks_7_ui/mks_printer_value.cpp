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
#include "../../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_7_UI

#include "mks_main_ui.h"
#include "../../../../module/temperature.h"

float mks_get_value(mks_printer_value_t item, uint8_t index) {
    MSK_TRACE_START(__func__);
    switch (item) {
    case MKS_VALUE_TEMP_EXTRUDER:
        return thermalManager.temp_hotend[index].celsius;
        break;
    
    case MKS_VALUE_TARGET_EXTRUDER:
        return thermalManager.temp_hotend[index].target;
        break;
    
    case MKS_VALUE_MIN_EXTRUDER:
        if (index == 0) { return (float)HEATER_0_MINTEMP; }
        else {
        #if DISABLED(SINGLENOZZLE) && HAS_MULTI_EXTRUDER
            return (uint32_t)HEATER_1_MINTEMP;
        #else
            return 0;
        #endif
        }
        break;
        
    case MKS_VALUE_MAX_EXTRUDER:
        if (index == 0) { return (float)HEATER_0_MAXTEMP; }
        else {
        #if DISABLED(SINGLENOZZLE) && HAS_MULTI_EXTRUDER
            return (uint32_t)HEATER_1_MAXTEMP;
        #else
            return 0;
        #endif
        }
        break;

    case MKS_VALUE_TEMP_BED:
        #if HAS_HEATED_BED
            return thermalManager.temp_bed.celsius;
        #else
            return 0;
        #endif
        break;
    
    case MKS_VALUE_TARGET_BED:
        #if HAS_HEATED_BED
            return thermalManager.temp_bed.target;
        #else
            return 0;
        #endif
        break;
    
    case MKS_VALUE_MIN_BED:
        #if HAS_HEATED_BED
            return (float)BED_MINTEMP;
        #else
            return 0;
        #endif
        break;
    
    case MKS_VALUE_MAX_BED:
        #if HAS_HEATED_BED
            return (float)BED_MAXTEMP;
        #else
            return 0;
        #endif
        break;

    default:
        return 0;
        break;
    }
    MSK_TRACE_END(__func__);
}

const char * mks_get_valueChar(mks_printer_value_t item, uint8_t index) {
    MSK_TRACE_START(__func__);
    switch (item) {
    case MKS_WIFI_SSID:
        return "";
        break;
    
    default:
        return "";
        break;
    }
    MSK_TRACE_END(__func__);
}

void mks_set_value(mks_printer_value_t item, uint8_t index, float value) {
    switch (item) {
    case MKS_VALUE_TARGET_EXTRUDER:
        thermalManager.temp_hotend[index].target = (uint8_t)value;
        uint16_t maxtemp;
        if (index == 0) maxtemp = (HEATER_0_MAXTEMP - (WATCH_TEMP_INCREASE + TEMP_HYSTERESIS + 1));
        #if DISABLED(SINGLENOZZLE) && HAS_MULTI_EXTRUDER
            if (index == 1) maxtemp = (HEATER_1_MAXTEMP - (WATCH_TEMP_INCREASE + TEMP_HYSTERESIS + 1));
        #endif
        if ((int)thermalManager.temp_hotend[index].target > maxtemp) {
            thermalManager.temp_hotend[index].target = maxtemp;
        }
        thermalManager.start_watching_hotend(index);
        break;
    
    case MKS_VALUE_TARGET_BED:
        #if HAS_HEATED_BED
          thermalManager.temp_bed.target = (uint8_t)value;
          if ((int)thermalManager.temp_bed.target > BED_MAXTEMP - (WATCH_BED_TEMP_INCREASE + TEMP_BED_HYSTERESIS + 1)) {
            thermalManager.temp_bed.target = (float)BED_MAXTEMP - (WATCH_BED_TEMP_INCREASE + TEMP_BED_HYSTERESIS + 1);
          }
          thermalManager.start_watching_bed();
        #endif
        break;
    
    default:
        break;
    }
}

void mks_set_valueChar(mks_printer_value_t item, uint8_t index, const char * value) {
    MSK_TRACE_START(__func__);
    switch (item) {
    case MKS_WIFI_SSID:
        break;
    
    default:
        break;
    }
    MSK_TRACE_END(__func__);
}

#endif