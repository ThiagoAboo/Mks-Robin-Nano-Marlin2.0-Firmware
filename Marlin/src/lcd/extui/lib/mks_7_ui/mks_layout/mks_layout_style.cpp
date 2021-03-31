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
#include "mks_layout_style.h"

#if HAS_TFT_LVGL_7_UI

#include "../mks_util.h"

static lv_style_t style_cont_btn;
static lv_style_t style_cont_btn_title;
static bool is_init;

void mks_style_init() {
    lv_style_init(&style_cont_btn);
    lv_style_init(&style_cont_btn_title);
    is_init = true;
}

void mks_style_content_btn(lv_obj_t * obj, lv_color_t bg_color, lv_color_t grad_color)
{
    if (!is_init) { mks_style_init(); }
    lv_obj_remove_style(obj, LV_BTN_PART_MAIN, &style_cont_btn);

    lv_btn_set_fit2(obj, LV_FIT_TIGHT, LV_FIT_TIGHT);

    lv_style_init(&style_cont_btn);
    //lv_style_set_transform_width(&style_cont_btn, LV_STATE_DEFAULT, LV_HOR_RES / 3);
    lv_style_set_transform_width(&style_cont_btn, LV_BTN_STATE_RELEASED, 0);
    lv_style_set_transform_width(&style_cont_btn, LV_STATE_FOCUSED, 2);
    lv_style_set_transform_width(&style_cont_btn, LV_STATE_PRESSED, 0);
    //lv_style_set_transform_height(&style_cont_btn, LV_STATE_PRESSED, -5);
    lv_style_set_transition_time(&style_cont_btn, LV_STATE_DEFAULT, 250);
    lv_style_set_transition_delay(&style_cont_btn, LV_STATE_DEFAULT, 100);
    lv_style_set_transition_prop_1(&style_cont_btn, LV_BTN_STATE_RELEASED, LV_STYLE_TRANSFORM_WIDTH);
    //lv_style_set_transition_prop_2(&style_cont_btn, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);

    lv_style_set_radius(&style_cont_btn, LV_STATE_DEFAULT, 10);
    lv_style_set_bg_opa(&style_cont_btn, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_border_width(&style_cont_btn, LV_STATE_DEFAULT, 2);
    lv_style_set_outline_width(&style_cont_btn, LV_STATE_FOCUSED, 2);

    lv_obj_set_style_local_outline_color(obj, LV_BTN_PART_MAIN, LV_STATE_FOCUSED, bg_color);
    lv_obj_set_style_local_outline_color(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, bg_color);
    lv_obj_set_style_local_outline_opa(obj, LV_BTN_PART_MAIN, LV_STATE_FOCUSED, LV_OPA_70);
    lv_obj_set_style_local_border_color(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, grad_color);
    lv_obj_set_style_local_border_color(obj, LV_BTN_PART_MAIN, LV_STATE_PRESSED, grad_color);
    lv_obj_set_style_local_border_color(obj, LV_BTN_PART_MAIN, LV_STATE_FOCUSED, grad_color);
    lv_obj_set_style_local_bg_color(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, bg_color);
    lv_obj_set_style_local_bg_color(obj, LV_BTN_PART_MAIN, LV_STATE_PRESSED, bg_color);
    lv_obj_set_style_local_bg_grad_color(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, grad_color);
    lv_obj_set_style_local_bg_grad_dir(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_obj_set_style_local_bg_main_stop(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 90);
    lv_obj_set_style_local_bg_grad_stop(obj, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 100);
    
    //lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(obj, LV_BTN_PART_MAIN, &style_cont_btn);
}

void mks_style_content_btn_title(lv_obj_t * obj, lv_color_t font_color)
{ 
    if (!is_init) { mks_style_init(); }
    lv_obj_remove_style(obj, LV_LABEL_PART_MAIN, &style_cont_btn_title);
    
    lv_label_set_align(obj, LV_LABEL_ALIGN_CENTER);
    //lv_style_set_text_color(&style_cont_btn_title, LV_STATE_DEFAULT, font_color);
    //lv_style_set_text_font(&style_cont_btn_title, LV_STATE_DEFAULT, &lv_font_montserrat_18);

    lv_obj_add_style(obj, LV_LABEL_PART_MAIN, &style_cont_btn_title);
}

#endif