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

#include "mks_util.h"

#include "../../MarlinCore.h"

unsigned int mks_getTickDiff(unsigned int curTick, unsigned int lastTick) {
  return TICK_CYCLE * (lastTick <= curTick ? (curTick - lastTick) : (0xFFFFFFFF - lastTick + curTick));
}

void lvgl_log(lv_log_level_t level, const char * file, uint32_t line, const char * fnName, const char * dsc) 
{
    MKS_TRACE("(", line, ") ", fnName, " : ", dsc);
}

void serial_trace_msg()  { static PGMSTR(tracemagic, "-TRACE--MSG--"); serialprintPGM(tracemagic); }
void serial_trace_sta()  { static PGMSTR(tracemagic, "-TRACE-START-"); serialprintPGM(tracemagic); }
void serial_trace_end()  { static PGMSTR(tracemagic, "-TRACE--END--"); serialprintPGM(tracemagic); }