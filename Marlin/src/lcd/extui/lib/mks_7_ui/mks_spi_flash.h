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

static const char mks_custom_gcode_command[][100] = {
  "G28\nG29\nM500",
  "G28",
  "G28",
  "G28",
  "G28"
};

typedef struct {
  uint32_t spi_flash_flag;
  uint8_t wifi_mode_sel;
  uint8_t wifi_type;
  uint32_t theme_dark;
  bool encoder_enable;
} MKS_CFG_ITMES;

extern MKS_CFG_ITMES mks_CfgItems;

#define MKS_AP_MODEL          0x01
#define MKS_STA_MODEL         0x02
#define MKS_ESP_WIFI          0x02

// SD card information first addr
#define MKS_VAR_INF_ADDR                    0x000000
#define MKS_FLASH_INF_VALID_FLAG            0x20201118

//Store some gcode commands, such as auto leveling commands
#define MKS_GCODE_COMMAND_ADDR              MKS_VAR_INF_ADDR + 3*1024
#define MKS_AUTO_LEVELING_COMMAND_ADDR      MKS_GCODE_COMMAND_ADDR
#define MKS_OTHERS_COMMAND_ADDR_1           MKS_AUTO_LEVELING_COMMAND_ADDR + 100
#define MKS_OTHERS_COMMAND_ADDR_2           MKS_OTHERS_COMMAND_ADDR_1 + 100
#define MKS_OTHERS_COMMAND_ADDR_3           MKS_OTHERS_COMMAND_ADDR_2 + 100
#define MKS_OTHERS_COMMAND_ADDR_4           MKS_OTHERS_COMMAND_ADDR_3 + 100

extern void mks_load_spi_flash();
extern void mks_update_spi_flash();

#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
#endif