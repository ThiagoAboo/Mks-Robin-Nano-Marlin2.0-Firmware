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
#include "mks_main_ui.h"

#if HAS_TFT_LVGL_7_UI

#include <SPI.h>

#include "../../../../MarlinCore.h"
#include "../../../../sd/cardreader.h"
#include "../../../../module/motion.h"
#include "../../../../module/planner.h"
#include "../../../../inc/MarlinConfig.h"

char public_buf_m[100] = {0};
char public_buf_l[30];

void MKS_TASK_HANDLER() {
  lv_task_handler();
  
  //TERN_(HAS_GCODE_PREVIEW, disp_pre_gcode(2, 36));

  //GUI_RefreshPage();

  //TERN_(MKS_WIFI_MODULE, get_wifi_commands());

  #if HAS_ROTARY_ENCODER
    mks_update_encoder();
  #endif
  
  //mks_task_handler();
  //if (marlin_state == MF_SD_COMPLETE) lv_print_finished();
}

void mks_printer_state_polling() {}

void mks_tft_init() {
  lv_log_register_print_cb(lvgl_log);

  mks_init_spi();
  mks_init_touch();
  mks_load_spi_flash();
  lv_init();
  mks_lv_register();

  systick_attach_callback(mks_SysTick_Callback);

  mks_encoder_init();
  mks_draw_layout_load();
  
  mks_create_touch();
  if (!mks_CfgItems.touch_calibration) {
    mks_draw_layout();
  }
}

void mks_SysTick_Callback() {
  lv_tick_inc(1);
}

#endif