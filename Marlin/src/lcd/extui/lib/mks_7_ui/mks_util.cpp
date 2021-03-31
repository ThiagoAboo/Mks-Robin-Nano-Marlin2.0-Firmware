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
    String debug = file;
    debug.concat("(");
    debug.concat(line);
    debug.concat(") ");
    debug.concat(fnName);
    debug.concat(" : ");
    debug.concat(dsc);
    debug.concat("\n");

    SERIAL_ECHO(debug.c_str());
}

void mks_trace_start(const char * msg) {
  #if ENABLED(MARLIN_DEV_MODE)
    SERIAL_ECHO_MSG("Iniciando ", msg);
    delay(10);
  #endif
}

void mks_trace_end(const char * msg) {
  #if ENABLED(MARLIN_DEV_MODE)
    SERIAL_ECHO_MSG("Finalizado ", msg);
    delay(10);
  #endif
}

void mks_trace_end_start(const char * msg1, const char * msg2) {
  #if ENABLED(MARLIN_DEV_MODE)
    SERIAL_ECHO_MSG("Finalizado ", msg1);
    SERIAL_ECHO_MSG("Iniciando ", msg2);
    delay(10);
  #endif
}

void mks_trace(const char * V, ...) {
  #if ENABLED(MARLIN_DEV_MODE)
    SERIAL_ECHO_F(V);
    delay(10);
  #endif
}