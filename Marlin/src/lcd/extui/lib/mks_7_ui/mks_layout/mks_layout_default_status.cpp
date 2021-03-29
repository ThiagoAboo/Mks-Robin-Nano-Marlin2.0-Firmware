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
#include "../mks_main_ui.h"

#if HAS_TFT_LVGL_7_UI

#include "mks_layout_default_status.h"
#include "../../../../../MarlinCore.h"

lv_obj_t * cont;

void mks_layout_status(lv_obj_t * parent, lv_event_cb_t event) {
    mks_trace_start(__func__);
    mks_layout_status_container(parent);
    mks_layout_status_temp(event);
    mks_layout_status_position(event);
    mks_trace_end(__func__);
}

void  mks_layout_status_container(lv_obj_t * parent) {
    cont = lv_cont_create(parent, NULL);
    lv_obj_set_auto_realign(cont, true);
    lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_fit(cont, LV_FIT_PARENT);
    lv_cont_set_layout(cont, LV_LAYOUT_GRID);
    lv_obj_set_style_local_border_width(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);
}

void  mks_layout_status_temp(lv_event_cb_t event) {
    mks_trace_start(__func__);
    lv_obj_t * btn = lv_btn_create(cont, NULL);
    lv_obj_set_event_cb(btn, event);
    lv_btn_set_fit2(btn, LV_FIT_TIGHT, LV_FIT_TIGHT);

    lv_obj_set_style_local_radius(btn, LV_BTN_PART_MAIN, LV_BTN_STATE_RELEASED, 5);
    //lv_obj_set_style_local_bg_grad_color(btn, LV_BTN_PART_MAIN, LV_BTN_STATE_RELEASED, LV_COLOR_ORANGE);
    //lv_obj_set_style_local_bg_grad_dir(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    lv_obj_t * lTitle = lv_label_create(btn, NULL);
    lv_label_set_text(lTitle, LV_SYMBOL_CHARGE " HotEnd");
    lv_label_set_align(lTitle, LV_LABEL_ALIGN_CENTER);

    String value = "Temp: ";
    value.concat(String(mks_get_value(MKS_VALUE_TEMP_EXTRUDER,0),1));
    value.concat("ºC\nSet: ");
    value.concat(String(mks_get_value(MKS_VALUE_TARGET_EXTRUDER,0),0));
    value.concat("ºC\nMax: ");
    value.concat(String(mks_get_value(MKS_VALUE_MAX_EXTRUDER,0),0));
    value.concat("ºC");

    lv_obj_t * lValue = lv_label_create(btn, NULL);
    lv_label_set_text(lValue, value.c_str());
    lv_label_set_align(lValue, LV_LABEL_ALIGN_LEFT);

    mks_add_rotary_group(btn);
    mks_trace_end(__func__);
}

void  mks_layout_status_position(lv_event_cb_t event) {
    mks_trace_start(__func__);
    lv_obj_t * btn = lv_btn_create(cont, NULL);
    lv_obj_set_event_cb(btn, event);
    lv_btn_set_fit2(btn, LV_FIT_TIGHT, LV_FIT_TIGHT);

    lv_obj_set_style_local_radius(btn, LV_BTN_PART_MAIN, LV_BTN_STATE_RELEASED, 5);
    //lv_obj_set_style_local_bg_grad_color(btn, LV_BTN_PART_MAIN, LV_BTN_STATE_RELEASED, LV_COLOR_SILVER);
    //lv_obj_set_style_local_bg_grad_dir(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    lv_obj_t * lTitle = lv_label_create(btn, NULL);
    lv_label_set_text(lTitle, LV_SYMBOL_PLUS " Position");
    lv_label_set_align(lTitle, LV_LABEL_ALIGN_LEFT);

    String value = "X: ";
    //value.concat(String(mks_get_value(MKS_VALUE_X_POS,0),1));
    value.concat("\nY: ");
    //value.concat(String(mks_get_value(MKS_VALUE_Y_POS,0),0));
    value.concat("\nZ: ");
    //value.concat(String(mks_get_value(MKS_VALUE_Z_POS,0),0));
    
    lv_obj_t * lValue = lv_label_create(btn, NULL);
    lv_label_set_text(lValue, value.c_str());
    lv_label_set_align(lValue, LV_LABEL_ALIGN_LEFT);

    mks_add_rotary_group(btn);
    mks_trace_end(__func__);
}

#endif