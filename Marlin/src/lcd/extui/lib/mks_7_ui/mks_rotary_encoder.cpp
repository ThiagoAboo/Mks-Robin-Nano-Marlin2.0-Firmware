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

#include "../../../../MarlinCore.h"
#include "../../../../inc/MarlinConfig.h"

#include "mks_main_ui.h"
#include "../../../marlinui.h"

int16_t enc_diff = 0;
lv_indev_state_t state = LV_INDEV_STATE_REL;

void mks_encoder_init() {
  mks_trace_start(__func__);
  #if BUTTON_EXISTS(EN1)
    SET_INPUT_PULLUP(BTN_EN1);
  #endif
  #if BUTTON_EXISTS(EN2)
    SET_INPUT_PULLUP(BTN_EN2);
  #endif
  #if BUTTON_EXISTS(ENC)
    SET_INPUT_PULLUP(BTN_ENC);
  #endif

  #if BUTTON_EXISTS(BACK)
    SET_INPUT_PULLUP(BTN_BACK);
  #endif

  #if BUTTON_EXISTS(UP)
    SET_INPUT(BTN_UP);
  #endif
  #if BUTTON_EXISTS(DWN)
    SET_INPUT(BTN_DWN);
  #endif
  #if BUTTON_EXISTS(LFT)
    SET_INPUT(BTN_LFT);
  #endif
  #if BUTTON_EXISTS(RT)
    SET_INPUT(BTN_RT);
  #endif
  mks_trace_end(__func__);
}
 
bool mks_mousewheel_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data) {
  (void) indev_drv;   /*Unused*/
  data->state = state;
  data->enc_diff = enc_diff;
  enc_diff = 0;
  return false;       /*No more data to read so return false*/
}

void mks_update_encoder() {
  static uint32_t encoder_time1;
  uint32_t tmpTime, diffTime = 0;
  tmpTime = millis();
  diffTime = mks_getTickDiff(tmpTime, encoder_time1);

  if (diffTime > 50) {
    #if HAS_ENCODER_WHEEL
      #if ANY_BUTTON(EN1, EN2, ENC, BACK)
        uint8_t newbutton = 0;
        #if BUTTON_EXISTS(EN1)
          if (BUTTON_PRESSED(EN1)) newbutton |= EN_A;
        #endif
        #if BUTTON_EXISTS(EN2)
          if (BUTTON_PRESSED(EN2)) newbutton |= EN_B;
        #endif
        #if BUTTON_EXISTS(ENC)
          if (BUTTON_PRESSED(ENC)) newbutton |= EN_C;
        #endif
        #if BUTTON_EXISTS(BACK)
          if (BUTTON_PRESSED(BACK)) newbutton |= EN_D;
        #endif
      #else
        constexpr uint8_t newbutton = 0;
      #endif

      static uint8_t buttons = 0;
      buttons = newbutton;
      static uint8_t lastEncoderBits;

      #define encrot0 0
      #define encrot1 1
      #define encrot2 2
      
      uint8_t enc = 0;
      if (buttons & EN_A) enc |= B01;
      if (buttons & EN_B) enc |= B10;
      if (enc != lastEncoderBits) {
        switch (enc) {
          case encrot1:
            if (lastEncoderBits == encrot0) {
              enc_diff--;
              encoder_time1 = tmpTime;
            }
            break;
          case encrot2:
            if (lastEncoderBits == encrot0) {
              enc_diff++;
              encoder_time1 = tmpTime;
            }
            break;
        }
        lastEncoderBits = enc;
      }
      static uint8_t last_button_state = LV_INDEV_STATE_REL;
      const uint8_t enc_c = (buttons & EN_C) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
      if (enc_c != last_button_state) {
        state = enc_c ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
        last_button_state = enc_c;
      }

    #endif // HAS_ENCODER_WHEEL

  } // next_button_update_ms
}

#endif