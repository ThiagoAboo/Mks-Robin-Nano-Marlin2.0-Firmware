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

#include "../../../../inc/MarlinConfig.h"
#include "mks_draw_layout.h"
#include "mks_layout/mks_layout_default.h"

static lv_obj_t * scr;
static lv_group_t * rotaryGroup;

static mks_layout_cb _mks_layout_cb;
static mks_layout_item_t mks_layout_item = MKS_LAYOUT_INIT;

void mks_add_rotary_group(lv_obj_t * obj) { 
    mks_trace_start(__func__);
    #if HAS_ROTARY_ENCODER
        lv_group_add_obj(rotaryGroup, obj);
        mks_trace("mks_add_rotary_group: Sucess.\n");
    #endif
    mks_trace_end(__func__);
}

void mks_clear_disp() {
    mks_trace_start(__func__);
    if (scr != nullptr) { lv_obj_del(scr); }
    scr = lv_scr_act();
    
    if (rotaryGroup != nullptr) { lv_group_del(rotaryGroup); }
    rotaryGroup = lv_group_create();

    #if HAS_ROTARY_ENCODER
        lv_indev_drv_t enc_drv;
        lv_indev_drv_init(&enc_drv);
        enc_drv.type = LV_INDEV_TYPE_ENCODER;
        enc_drv.read_cb = mks_mousewheel_read;
        lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
        lv_indev_set_group(enc_indev, rotaryGroup);
        mks_trace("Register rotary endev\n");
    #endif
    
    if (rotaryGroup==nullptr) { mks_trace("rotaryGroup:nullptr\n"); }
    else if (rotaryGroup==NULL) { mks_trace("rotaryGroup:null\n"); }
    else { mks_trace("rotaryGroup:create\n"); }

    mks_trace_end(__func__);
}

void mks_layout_set_cb(mks_layout_cb cb) {
    _mks_layout_cb = cb;
}

void mks_draw_layout_load() {
    mks_trace_start(__func__);
    if (mks_layout_item == MKS_LAYOUT_INIT) mks_layout_item = MKS_LAYOUT_MAIN_PANEL;
    mks_clear_disp();
    mks_layout_init();
    mks_trace_end(__func__);
}

void mks_draw_layout() {
    mks_trace_start(__func__);
    if(_mks_layout_cb) { _mks_layout_cb(mks_layout_item, scr); }
    lv_refr_now(_lv_refr_get_disp_refreshing());
    mks_trace_end(__func__);
}

void mks_event_handler(lv_obj_t * obj, lv_event_t event) {
    switch (event) {
    case LV_EVENT_CLICKED:
        mks_trace("Event Clicked\n");
        break;
    case LV_EVENT_VALUE_CHANGED:
        mks_trace("Event Value Changed\n");
        break;
    default:
        break;
    }
}

lv_obj_t * mks_draw_button(const char * name, uint16_t id, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
    lv_obj_t * label;

    lv_obj_t * btn = lv_btn_create(scr, NULL);
    lv_obj_set_event_cb(btn, mks_event_handler);
    lv_obj_align(btn, NULL, align, x_ofs, y_ofs);
    label = lv_label_create(btn, NULL);
    lv_label_set_text(label, name);
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

    lv_refr_now(_lv_refr_get_disp_refreshing());
    mks_add_rotary_group(btn);
    return btn;
}

lv_obj_t * mks_draw_label(const char * msg, uint16_t id, lv_align_t alignLabel, lv_align_t alignObj, lv_coord_t x_ofs, lv_coord_t y_ofs) {
    lv_obj_t * label = lv_label_create(scr, NULL);
    lv_obj_align(label, NULL, alignObj, x_ofs, y_ofs);
    lv_label_set_align(label, alignLabel);
    
    lv_refr_now(_lv_refr_get_disp_refreshing());
    return label;
}

void mks_change_label_text(lv_obj_t * obj, const char * msg, lv_align_t alignLabel) {
  lv_label_set_text(obj, msg);
  lv_obj_align(obj, nullptr, alignLabel, 0, 0);
}

#endif