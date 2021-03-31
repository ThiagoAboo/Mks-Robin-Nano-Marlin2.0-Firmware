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

void mks_task_handler() {
    mks_layout_item = MKS_LAYOUT_REFRESH;
    if(_mks_layout_cb) { _mks_layout_cb(mks_layout_item, scr); }
}

void mks_add_rotary_group(lv_obj_t * obj) { 
    MSK_TRACE_START(__func__);
    #if HAS_ROTARY_ENCODER
        lv_group_add_obj(rotaryGroup, obj);
        MKS_TRACE("mks_add_rotary_group: Sucess.");
    #endif
    MSK_TRACE_END(__func__);
}

void mks_register_rotary_group() {
    MSK_TRACE_START(__func__);

    if (rotaryGroup != nullptr) { lv_group_del(rotaryGroup); }
    rotaryGroup = lv_group_create();

    #if HAS_ROTARY_ENCODER
        lv_indev_drv_t enc_drv;
        lv_indev_drv_init(&enc_drv);
        enc_drv.type = LV_INDEV_TYPE_ENCODER;
        enc_drv.read_cb = mks_mousewheel_read;
        lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
        lv_indev_set_group(enc_indev, rotaryGroup);
        MKS_TRACE("Register rotary endev");
    #endif
    
    MSK_TRACE_END(__func__);
}

void mks_clear_disp() {
    MSK_TRACE_START(__func__);
    if (scr != nullptr) { 
        lv_obj_clean(scr); 
    }
    else { 
        scr = lv_obj_create(nullptr, nullptr);
        lv_scr_load(scr);
    }
    MSK_TRACE_END(__func__);
}

void mks_layout_set_cb(mks_layout_cb cb) {
    _mks_layout_cb = cb;
}

void mks_draw_layout_load() {
    MSK_TRACE_START(__func__);
    if (mks_layout_item == MKS_LAYOUT_NONE) mks_layout_item = MKS_LAYOUT_INIT;
    mks_clear_disp();
    MSK_TRACE_END(__func__);
}

void mks_draw_layout() {
    MSK_TRACE_START(__func__);
    if (mks_layout_item == MKS_LAYOUT_INIT) {
        mks_clear_disp(); 
        mks_layout_init();
        mks_layout_item = MKS_LAYOUT_MAIN_PANEL; 
    }
    if(_mks_layout_cb) { _mks_layout_cb(mks_layout_item, scr); }
    lv_refr_now(_lv_refr_get_disp_refreshing());
    MSK_TRACE_END(__func__);
}

void mks_event_handler(lv_obj_t * obj, lv_event_t event) {
    
    uint8_t id = obj->user_data;

    switch (event) {
    case LV_EVENT_CLICKED:
        MKS_TRACE("Event Clicked");
        mks_layout_item = id;
        SERIAL_ECHOLNPAIR("mks_layout_item:", mks_layout_item);
        mks_draw_layout();
        break;
    case LV_EVENT_VALUE_CHANGED:
        MKS_TRACE("Event Value Changed");
        break;
    default:
        break;
    }
}

lv_obj_t * mks_draw_button(const char * name, mks_layout_item_t id, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
    lv_obj_t * btn = lv_btn_create(scr, NULL);
    lv_obj_set_event_cb(btn, mks_event_handler);
    btn->user_data = id;

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, name);
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

    lv_btn_set_fit2(btn, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_obj_align(btn, NULL, align, x_ofs, y_ofs);

    mks_add_rotary_group(btn);
    lv_refr_now(_lv_refr_get_disp_refreshing());
    return btn;
}

lv_obj_t * mks_draw_label(const char * msg, lv_align_t alignLabel, lv_align_t alignObj, lv_coord_t x_ofs, lv_coord_t y_ofs) {
    lv_obj_t * label = lv_label_create(scr, NULL);
    lv_label_set_text(label, msg);
    lv_obj_align(label, NULL, alignObj, x_ofs, y_ofs);
    lv_label_set_align(label, alignLabel);
    lv_refr_now(_lv_refr_get_disp_refreshing());
    return label;
}

void mks_change_label_text(lv_obj_t * obj, const char * msg, lv_align_t alignLabel) {
     MSK_TRACE_START(__func__);
    lv_label_set_text(obj, msg);
    lv_obj_realign(obj);
    lv_refr_now(_lv_refr_get_disp_refreshing());
    MSK_TRACE_END(__func__);
}

#endif