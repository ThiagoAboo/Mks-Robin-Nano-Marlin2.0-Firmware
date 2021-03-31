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
#include "../../../../libs/W25Qxx.h"
#include "../../../tft_io/tft_io.h"

MKS_CFG_ITMES mks_CfgItems;

void mks_load_spi_flash() {
    MSK_TRACE_START(__func__);

    mks_CfgItems.theme_dark         = 0x02;
    mks_CfgItems.wifi_mode_sel      = MKS_STA_MODEL;
    mks_CfgItems.wifi_type          = MKS_ESP_WIFI;

    #if LV_USE_THEME_MATERIAL
        mks_CfgItems.theme_dark = LV_THEME_MATERIAL_FLAG_LIGHT;
    #endif
    
    W25QXX.SPI_FLASH_BufferRead((uint8_t *)&mks_CfgItems.spi_flash_flag, MKS_VAR_INF_ADDR, sizeof(mks_CfgItems.spi_flash_flag));
    if (mks_CfgItems.spi_flash_flag == MKS_FLASH_INF_VALID_FLAG) {
        W25QXX.SPI_FLASH_BufferRead((uint8_t *)&mks_CfgItems, MKS_VAR_INF_ADDR, sizeof(mks_CfgItems));
    }
    else {
        mks_CfgItems.spi_flash_flag = MKS_FLASH_INF_VALID_FLAG;
        W25QXX.SPI_FLASH_SectorErase(MKS_VAR_INF_ADDR);
        W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&mks_CfgItems, MKS_VAR_INF_ADDR, sizeof(mks_CfgItems));
        //init gcode command
        W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&mks_custom_gcode_command[0], MKS_AUTO_LEVELING_COMMAND_ADDR, 100);
        W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&mks_custom_gcode_command[1], MKS_OTHERS_COMMAND_ADDR_1, 100);
        W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&mks_custom_gcode_command[2], MKS_OTHERS_COMMAND_ADDR_2, 100);
        W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&mks_custom_gcode_command[3], MKS_OTHERS_COMMAND_ADDR_3, 100);
        W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&mks_custom_gcode_command[4], MKS_OTHERS_COMMAND_ADDR_4, 100);
    }
    
    const byte rot = (TFT_ROTATION & TFT_ROTATE_180) ? 0xEE : 0x00;
    if (mks_CfgItems.disp_rotation_180 != rot) {
        mks_CfgItems.disp_rotation_180 = rot;
        mks_update_spi_flash();
    }
    
    uint8_t F[4] = {'N','A','N','O'};
    W25QXX.SPI_FLASH_BlockErase(REFLSHE_FLGA_ADD + 32 - 64*1024);
    W25QXX.SPI_FLASH_BufferWrite(F,REFLSHE_FLGA_ADD,4);

    MSK_TRACE_END(__func__);
}

void mks_update_spi_flash() {
  uint8_t command_buf[512];

  W25QXX.init(SPI_QUARTER_SPEED);
  //read back the gcode command befor erase spi flash
  W25QXX.SPI_FLASH_BufferRead((uint8_t *)&command_buf, MKS_GCODE_COMMAND_ADDR, sizeof(command_buf));
  W25QXX.SPI_FLASH_SectorErase(MKS_VAR_INF_ADDR);
  W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&mks_CfgItems, MKS_VAR_INF_ADDR, sizeof(mks_CfgItems));
  W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&command_buf, MKS_GCODE_COMMAND_ADDR, sizeof(command_buf));
}

#endif