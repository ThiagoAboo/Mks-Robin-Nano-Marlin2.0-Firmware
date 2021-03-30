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

#include "mks_layout_default.h"
#include "mks_layout_default_status.h"
#include "mks_layout_style.h"

static lv_obj_t * tv;
static lv_obj_t * t1;
//static lv_obj_t * t2;
static lv_obj_t * t3;
static lv_obj_t * t4;
//static lv_obj_t * kb;
static lv_task_t * task;

void mks_layout_init() {
    mks_trace_start(__func__);
    mks_layout_set_cb(mks_layout_callback);
    mks_trace_end(__func__);
}

void mks_layout_event(lv_obj_t * obj, lv_event_t event) { 
    mks_event_handler(obj, event);
    switch (event) {
    case LV_EVENT_VALUE_CHANGED:
        lv_task_reset(task);
        break;
    
    default:
        break;
    }
}

void mks_layout_callback(mks_layout_item_t item, lv_obj_t * parent) {

    switch (item) {
    case MKS_LAYOUT_MAIN_PANEL:
        mks_create_main_panel(parent);
        mks_layout_status(t1, mks_layout_event);
        break;
    case MKS_LAYOUT_REFRESH:
        break;
    default:
        break;
    }
}

void mks_create_main_panel(lv_obj_t * parent) {

    tv = lv_tabview_create(parent, NULL);
    lv_obj_set_event_cb(tv, mks_layout_event);

    #if LV_USE_THEME_MATERIAL
        //if(LV_THEME_DEFAULT_INIT == lv_theme_material_init) {
            LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_secondary(), mks_CfgItems.theme_dark,
                    lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());

            lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);
            if(disp_size >= LV_DISP_SIZE_MEDIUM) {
                lv_obj_set_style_local_pad_left(tv, LV_TABVIEW_PART_TAB_BG, LV_STATE_DEFAULT, LV_HOR_RES / 4);
                lv_obj_t * sw = lv_switch_create(lv_scr_act(), NULL);
                if(lv_theme_get_flags() & LV_THEME_MATERIAL_FLAG_DARK)
                    lv_switch_on(sw, LV_ANIM_OFF);
                lv_obj_set_event_cb(sw, mks_color_chg_event_cb);
                lv_obj_set_pos(sw, LV_DPX(10), LV_DPX(20));
                lv_obj_set_style_local_value_str(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, "Dark");
                lv_obj_set_style_local_value_align(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_ALIGN_OUT_RIGHT_MID);
                lv_obj_set_style_local_value_ofs_x(sw, LV_SWITCH_PART_BG, LV_STATE_DEFAULT, LV_DPI/35);
                
                mks_add_rotary_group(sw);
            }
        //}
    #endif

    lv_obj_set_style_local_text_font(tv, LV_TABVIEW_PART_TAB_BTN, LV_STATE_DEFAULT, &lv_font_montserrat_18);

    t1 = lv_tabview_add_tab(tv, LV_SYMBOL_HOME " Home");
    //t2 = lv_tabview_add_tab(tv, LV_SYMBOL_LIST " Tools");
    t3 = lv_tabview_add_tab(tv, LV_SYMBOL_SETTINGS " Config");
    t4 = lv_tabview_add_tab(tv, LV_SYMBOL_SD_CARD " SD");

    #if LV_USE_ANIMATION
        task = lv_task_create(tab_changer_task_cb, 30000, LV_TASK_PRIO_LOW, NULL);
    #endif
    
    mks_add_rotary_group(tv);
}

#if LV_USE_THEME_MATERIAL
    void mks_color_chg_event_cb(lv_obj_t * sw, lv_event_t e)
    {
        //if(LV_THEME_DEFAULT_INIT != lv_theme_material_init) return;
        if(e == LV_EVENT_VALUE_CHANGED) {
            uint32_t flag = LV_THEME_MATERIAL_FLAG_LIGHT;
            if(lv_switch_get_state(sw)) flag = LV_THEME_MATERIAL_FLAG_DARK;

            LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_secondary(), flag,
                    lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
            
            mks_CfgItems.theme_dark = flag;
            mks_update_spi_flash();
        }
    }
#endif

#if LV_USE_ANIMATION
    void tab_content_anim_create(lv_obj_t * parent)
    {
        lv_anim_t a;
        lv_obj_t * scrl = lv_page_get_scrl(parent);
        lv_coord_t y_start = lv_obj_get_style_pad_top(parent, LV_PAGE_PART_BG);
        lv_coord_t anim_h = lv_obj_get_height(scrl) - lv_obj_get_height_fit(parent);
        uint32_t anim_time = lv_anim_speed_to_time(LV_DPI, 0, anim_h);

        lv_anim_init(&a);
        lv_anim_set_var(&a, scrl);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&a, y_start, y_start - anim_h);
        lv_anim_set_time(&a, anim_time);
        lv_anim_set_playback_time(&a, anim_time);
        lv_anim_set_playback_delay(&a, 200);
        lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
        lv_anim_set_repeat_delay(&a, 200);
        lv_anim_start(&a);
    }
    void tab_changer_task_cb(lv_task_t * task)
    {
        //uint16_t act = lv_tabview_get_tab_act(tv);
        lv_tabview_set_tab_act(tv, 0, LV_ANIM_ON);
    }
#endif

#endif