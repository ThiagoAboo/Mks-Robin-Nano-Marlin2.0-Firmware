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
static lv_obj_t * value_temp[3];
static float time_task = 0;

void mks_layout_status_update() {
    if (time_task < (millis() - 2000)) {
        lv_label_set_text(value_temp[0], mks_layout_status_temp_value(MKS_HOTEND_0, 0));
        lv_obj_align(value_temp[0], NULL, LV_LABEL_ALIGN_LEFT, 0, 0);
        #if DISABLED(SINGLENOZZLE) && HAS_MULTI_EXTRUDER
            lv_label_set_text(value_temp[1], mks_layout_status_temp_value(MKS_HOTEND_1, 1));
            lv_obj_align(value_temp[1], NULL, LV_LABEL_ALIGN_LEFT, 0, 0);
        #endif
        #if HAS_HEATED_BED
            lv_label_set_text(value_temp[2], mks_layout_status_temp_value(MKS_BED, 2));
            lv_obj_align(value_temp[2], NULL, LV_LABEL_ALIGN_LEFT, 0, 0);
        #endif
        time_task = millis();
    }
}

void mks_layout_status(lv_obj_t * parent, lv_event_cb_t event) {
    mks_trace_start(__func__);
    mks_layout_status_container(parent);
    mks_layout_status_temp(event, MKS_HOTEND_0);
    #if DISABLED(SINGLENOZZLE) && HAS_MULTI_EXTRUDER
        mks_layout_status_temp(event, MKS_HOTEND_1);
    #endif
    #if HAS_HEATED_BED
        mks_layout_status_temp(event, MKS_BED);
    #endif
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

const char * mks_layout_status_temp_value(mks_layout_item_t item, uint8_t index) {
    mks_trace_start(__func__);
    mks_printer_value_t item_value;
    String value = "Temp: ";
    
    item_value = (item == MKS_BED ? MKS_VALUE_TEMP_BED : MKS_VALUE_TEMP_EXTRUDER);
    value.concat(String(mks_get_value(item_value,index),1));
    value.concat("\nSet: ");
    
    item_value = (item == MKS_BED ? MKS_VALUE_TARGET_BED : MKS_VALUE_TARGET_EXTRUDER);
    value.concat(String(mks_get_value(item_value,index),0));
    value.concat("\nMax: ");
    
    item_value = (item == MKS_BED ? MKS_VALUE_MAX_BED : MKS_VALUE_MAX_EXTRUDER);
    value.concat(String(mks_get_value(item_value,index),0));

    mks_trace_end(__func__);
    return value.c_str();
}

void  mks_layout_status_temp(lv_event_cb_t event, mks_layout_item_t item) {
    mks_trace_start(__func__);
    
    uint8_t index = (item == MKS_BED ? 2 : (item == MKS_HOTEND_0 ? 0 : 1));
    String title = LV_SYMBOL_CHARGE;
    title.concat((item == MKS_BED ? " Bed" : (item == MKS_HOTEND_0 ? " Hotend 1" : " Hotend 2")));

    lv_obj_t * btn = lv_btn_create(cont, NULL);
    lv_obj_set_event_cb(btn, event);
    mks_style_content_btn(btn, LV_COLOR_MAKE(0xFF,0x33,0x00), LV_COLOR_MAKE(0xFF,0x99,0x00));

    lv_obj_t * lTitle = lv_label_create(btn, NULL);
    lv_label_set_text(lTitle, title.c_str());
    mks_style_content_btn_title(lTitle, LV_COLOR_MAKE(0xFF,0xFF,0xFF));

    value_temp[index] = lv_label_create(btn, NULL);
    lv_label_set_text(value_temp[index], mks_layout_status_temp_value(item, index));
    lv_label_set_align(value_temp[index], LV_LABEL_ALIGN_LEFT);
    lv_obj_align(value_temp[index], NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    mks_add_rotary_group(btn);
    mks_trace_end(__func__);
}

void  mks_layout_status_position(lv_event_cb_t event) {
    mks_trace_start(__func__);
    lv_obj_t * btn = lv_btn_create(cont, NULL);
    lv_obj_set_event_cb(btn, event);

    mks_style_content_btn(btn, LV_COLOR_MAKE(0x66,0x99,0xFF), LV_COLOR_MAKE(0xAE,0xE4,0xFF));

    lv_obj_t * lTitle = lv_label_create(btn, NULL);
    lv_label_set_text(lTitle, LV_SYMBOL_PLUS " Position");
    mks_style_content_btn_title(lTitle, LV_COLOR_MAKE(0xFF,0xFF,0xFF));

    String value = "X: ";
    value.concat("000");
    value.concat("mm\nY: ");
    value.concat("000");
    value.concat("mm\nZ: ");
    value.concat("000");
    value.concat("mm");
    
    lv_obj_t * lValue = lv_label_create(btn, NULL);
    lv_label_set_text(lValue, value.c_str());
    lv_label_set_align(lValue, LV_LABEL_ALIGN_LEFT);

    mks_add_rotary_group(btn);
    mks_trace_end(__func__);
}

#endif