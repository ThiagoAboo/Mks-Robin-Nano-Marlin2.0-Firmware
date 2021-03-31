
#ifndef MKS_LAYOUT_STYLE_H
#define MKS_LAYOUT_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

extern void mks_style_content_btn(lv_obj_t * obj, lv_color_t bg_color, lv_color_t grad_color);
extern void mks_style_content_btn_title(lv_obj_t * obj, lv_color_t font_color);

void mks_style_init();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*MKS_LAYOUT_STYLE_H*/