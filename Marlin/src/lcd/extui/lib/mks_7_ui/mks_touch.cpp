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

#include "mks_util.h"

#if ENABLED(TOUCH_SCREEN_CALIBRATION)
  #include "../../../tft_io/touch_calibration.h"
#endif

#include HAL_PATH(../../../../HAL, tft/xpt2046.h)
XPT2046 touch;

#include "mks_main_ui.h"

static lv_obj_t * status_label;
static lv_obj_t * point_label;

void mks_init_touch() {
  MSK_TRACE_START(__func__);
  touch.Init();
  MSK_TRACE_END(__func__);
}

void mks_create_touch() {
  MSK_TRACE_START(__func__);

  #if ENABLED(TOUCH_SCREEN_CALIBRATION)
    // If calibration is required, let's trigger it now, handles the case when there is default value in configuration files
    if (!touch_calibration.calibration_loaded()) {
      mks_CfgItems.touch_calibration = true;
      mks_clear_disp();
      mks_draw_touch_calibration_screen();
    }
  #endif

  MSK_TRACE_END(__func__);
}

void mks_draw_touch_calibration_screen() {
  status_label = mks_draw_label(GET_TEXT(MSG_CALIBRATION_FAILED), LV_LABEL_ALIGN_CENTER, LV_ALIGN_CENTER, 0, 0);
  point_label = mks_draw_label(LV_SYMBOL_PLUS, LV_LABEL_ALIGN_CENTER, LV_ALIGN_CENTER, 0, 0);
  mks_lv_update_touch_calibration_screen();
}

bool mks_get_point(int16_t *x, int16_t *y) {
  bool is_touched = (touch_calibration.calibration.orientation == TOUCH_PORTRAIT ? touch.getRawPoint(y, x) : touch.getRawPoint(x, y));
  
  //bool is_touched = touch.getRawPoint(x, y);
  if (!is_touched) return false;

  #if ENABLED(TOUCH_SCREEN_CALIBRATION)
    const calibrationState state = touch_calibration.get_calibration_state();
    if (state >= CALIBRATION_TOP_LEFT && state <= CALIBRATION_BOTTOM_RIGHT) {
      if (touch_calibration.handleTouch(*x, *y)) mks_lv_update_touch_calibration_screen();
      return false;
    }
    if (is_touched && touch_calibration.calibration.orientation != TOUCH_ORIENTATION_NONE) {
      *x = int16_t((int32_t(*x) * touch_calibration.calibration.x) >> 16) + touch_calibration.calibration.offset_x;
      *y = int16_t((int32_t(*y) * touch_calibration.calibration.y) >> 16) + touch_calibration.calibration.offset_y;
    }
  #else
    bool is_touched = (TOUCH_ORIENTATION == TOUCH_PORTRAIT ? io.getRawPoint(y, x) : io.getRawPoint(x, y));
    *x = int16_t((int32_t(*x) * TOUCH_CALIBRATION_X) >> 16) + TOUCH_OFFSET_X;
    *y = int16_t((int32_t(*y) * TOUCH_CALIBRATION_Y) >> 16) + TOUCH_OFFSET_Y;
  #endif

  return is_touched;
}

void mks_lv_update_touch_calibration_screen() {
  MSK_TRACE_START(__func__);

  uint16_t x, y;

  calibrationState calibration_stage = touch_calibration.get_calibration_state();
  if (calibration_stage == CALIBRATION_NONE) {
    // start and clear screen
    calibration_stage = touch_calibration.calibration_start();
  }
  else {
    // clear last cross
    x = touch_calibration.calibration_points[_MIN(calibration_stage - 1, CALIBRATION_BOTTOM_RIGHT)].x;
    y = touch_calibration.calibration_points[_MIN(calibration_stage - 1, CALIBRATION_BOTTOM_RIGHT)].y;
    //mks_drawCross(x, y, LV_COLOR_WHITE.full);
  }

  const char * str = GET_TEXT(MSG_CALIBRATION_FAILED);
  if (calibration_stage < CALIBRATION_SUCCESS) {
    // handle current state
    switch (calibration_stage) {
      case CALIBRATION_TOP_LEFT: str = GET_TEXT(MSG_TOP_LEFT); break;
      case CALIBRATION_TOP_RIGHT:  str = GET_TEXT(MSG_TOP_RIGHT); break;
      case CALIBRATION_BOTTOM_LEFT: str = GET_TEXT(MSG_BOTTOM_LEFT); break;
      case CALIBRATION_BOTTOM_RIGHT: str = GET_TEXT(MSG_BOTTOM_RIGHT); break;
      default: break;
    }

    x = touch_calibration.calibration_points[calibration_stage].x;
    y = touch_calibration.calibration_points[calibration_stage].y;
    //mks_drawCross(x, y, LV_COLOR_BLACK.full);
    lv_obj_set_x(point_label, x);
    lv_obj_set_y(point_label, y);
  }
  else {
    // end calibration
    str = calibration_stage == CALIBRATION_SUCCESS ? GET_TEXT(MSG_CALIBRATION_COMPLETED) : GET_TEXT(MSG_CALIBRATION_FAILED);
    touch_calibration.calibration_end();
    lv_obj_del(point_label);
    mks_draw_button(GET_TEXT(MSG_BUTTON_DONE), MKS_LAYOUT_INIT, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
    mks_CfgItems.touch_calibration = false;
  }

  // draw current message
  mks_change_label_text(status_label, str, LV_LABEL_ALIGN_CENTER);

  MSK_TRACE_END(__func__);
}

bool mks_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data) {
  static int16_t last_x = 0, last_y = 0;
  static uint8_t last_touch_state = LV_INDEV_STATE_REL;
  static int32_t touch_time1 = 0;
  uint32_t tmpTime, diffTime = 0;

  tmpTime = millis();
  diffTime = mks_getTickDiff(tmpTime, touch_time1);
  if (diffTime > 20) {
    if (mks_get_point(&last_x, &last_y)) {
      if (last_touch_state == LV_INDEV_STATE_PR) return false;
      data->state = LV_INDEV_STATE_PR;

      // Set the coordinates (if released use the last-pressed coordinates)
      data->point.x = last_x;
      data->point.y = last_y;

      MKS_TRACE("TOUCH_X:", data->point.x, ", TOUCH_Y:", data->point.y);

      last_x = last_y = 0;
      last_touch_state = LV_INDEV_STATE_PR;
    }
    else {
      if (last_touch_state == LV_INDEV_STATE_PR) { data->state = LV_INDEV_STATE_REL; }
      last_touch_state = LV_INDEV_STATE_REL;
    }

    touch_time1 = tmpTime;
  }

  return false; // Return `false` since no data is buffering or left to read
}

#endif