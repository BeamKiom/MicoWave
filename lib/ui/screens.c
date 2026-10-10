#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x9a9a9a), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wave_bt
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.wave_bt = obj;
            lv_obj_set_pos(obj, 113, 10);
            lv_obj_set_size(obj, 94, 59);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf32121), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "WaveFoot");
                }
            }
        }
        {
            // ice_bt
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.ice_bt = obj;
            lv_obj_set_pos(obj, 114, 82);
            lv_obj_set_size(obj, 94, 59);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x21a3f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Ice");
                }
            }
        }
        {
            // gill_bt
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.gill_bt = obj;
            lv_obj_set_pos(obj, 115, 160);
            lv_obj_set_size(obj, 94, 59);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf35f21), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "gill");
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_waveftpg() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.waveftpg = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // hr
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.hr = obj;
            lv_obj_set_pos(obj, 67, 18);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // min
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.min = obj;
            lv_obj_set_pos(obj, 67, 75);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // sec
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.sec = obj;
            lv_obj_set_pos(obj, 67, 135);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // plus_h
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_h = obj;
            lv_obj_set_pos(obj, 158, 26);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // plus_m
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_m = obj;
            lv_obj_set_pos(obj, 158, 82);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // plus_s
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_s = obj;
            lv_obj_set_pos(obj, 158, 143);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // depreciate_h
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_h = obj;
            lv_obj_set_pos(obj, 20, 27);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            // depreciate_m
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_m = obj;
            lv_obj_set_pos(obj, 19, 82);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            // depreciate_s
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_s = obj;
            lv_obj_set_pos(obj, 19, 143);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 76, -1);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Hour");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 68, 59);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "minute");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 67, 118);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "second");
        }
        {
            // go_main
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.go_main = obj;
            lv_obj_set_pos(obj, 0, 187);
            lv_obj_set_size(obj, 76, 30);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Main");
                }
            }
        }
        {
            // start_wavefoot
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.start_wavefoot = obj;
            lv_obj_set_pos(obj, 198, 188);
            lv_obj_set_size(obj, 73, 29);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x2df321), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Start");
                }
            }
        }
        {
            // stop_wavefoot
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.stop_wavefoot = obj;
            lv_obj_set_pos(obj, 97, 188);
            lv_obj_set_size(obj, 73, 29);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf32121), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Stop");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 234, 7);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Staus door");
        }
        {
            // door_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.door_3 = obj;
            lv_obj_set_pos(obj, 256, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "open");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 231, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Mode Wave");
        }
    }
    
    tick_screen_waveftpg();
}

void tick_screen_waveftpg() {
}

void create_screen_icepg() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.icepg = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // hr_1
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.hr_1 = obj;
            lv_obj_set_pos(obj, 48, 21);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // min_1
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.min_1 = obj;
            lv_obj_set_pos(obj, 52, 82);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // sec_1
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.sec_1 = obj;
            lv_obj_set_pos(obj, 48, 145);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // plus_h_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_h_1 = obj;
            lv_obj_set_pos(obj, 138, 25);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // plus_s_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_s_1 = obj;
            lv_obj_set_pos(obj, 138, 153);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // depreciate_h_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_h_1 = obj;
            lv_obj_set_pos(obj, 9, 29);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 54, 124);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "second");
        }
        {
            // go_main_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.go_main_1 = obj;
            lv_obj_set_pos(obj, 8, 192);
            lv_obj_set_size(obj, 76, 30);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Main");
                }
            }
        }
        {
            // plus_h_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_h_2 = obj;
            lv_obj_set_pos(obj, 138, 90);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // depreciate_h_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_h_2 = obj;
            lv_obj_set_pos(obj, 10, 90);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            // depreciate_h_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_h_3 = obj;
            lv_obj_set_pos(obj, 9, 153);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 53, 61);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "minute");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 52, 4);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Hour");
        }
        {
            // start_ice
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.start_ice = obj;
            lv_obj_set_pos(obj, 219, 193);
            lv_obj_set_size(obj, 73, 29);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x2df321), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Start");
                }
            }
        }
        {
            // stop_ice
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.stop_ice = obj;
            lv_obj_set_pos(obj, 107, 193);
            lv_obj_set_size(obj, 73, 29);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf32121), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Stop");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 233, 5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Staus door");
        }
        {
            // door_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.door_2 = obj;
            lv_obj_set_pos(obj, 255, 25);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "open");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 240, 54);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Mode ICE");
        }
    }
    
    tick_screen_icepg();
}

void tick_screen_icepg() {
}

void create_screen_gillpg() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gillpg = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // depreciate_h_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_h_gill = obj;
            lv_obj_set_pos(obj, 5, 23);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 50, 116);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "second");
        }
        {
            // go_main_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.go_main_2 = obj;
            lv_obj_set_pos(obj, 0, 187);
            lv_obj_set_size(obj, 76, 30);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Main");
                }
            }
        }
        {
            // plus_m_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_m_gill = obj;
            lv_obj_set_pos(obj, 137, 79);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // depreciate_m_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_m_gill = obj;
            lv_obj_set_pos(obj, 5, 79);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            // depreciate_s_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.depreciate_s_gill = obj;
            lv_obj_set_pos(obj, 5, 143);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "-");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 51, 59);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "minute");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 53, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Hour");
        }
        {
            // start_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.start_gill = obj;
            lv_obj_set_pos(obj, 222, 188);
            lv_obj_set_size(obj, 73, 29);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x2df321), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Start");
                }
            }
        }
        {
            // stop_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.stop_gill = obj;
            lv_obj_set_pos(obj, 114, 188);
            lv_obj_set_size(obj, 73, 29);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xf32121), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Stop");
                }
            }
        }
        {
            // sec_gill
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.sec_gill = obj;
            lv_obj_set_pos(obj, 42, 135);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // min_gill
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.min_gill = obj;
            lv_obj_set_pos(obj, 42, 76);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // hour_gill
            lv_obj_t *obj = lv_spinbox_create(parent_obj);
            objects.hour_gill = obj;
            lv_obj_set_pos(obj, 46, 19);
            lv_obj_set_size(obj, 80, 40);
            lv_spinbox_set_digit_format(obj, 2, 0);
            lv_spinbox_set_range(obj, 0, 300);
            lv_spinbox_set_rollover(obj, false);
            lv_spinbox_set_step(obj, 1);
            lv_spinbox_set_value(obj, 0);
        }
        {
            // plus_h_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_h_gill = obj;
            lv_obj_set_pos(obj, 137, 23);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            // plus_s_gill
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plus_s_gill = obj;
            lv_obj_set_pos(obj, 137, 143);
            lv_obj_set_size(obj, 32, 25);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "+");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 236, 7);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Staus door");
        }
        {
            // door_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.door_1 = obj;
            lv_obj_set_pos(obj, 258, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "open");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 239, 59);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Mode Gill");
        }
    }
    
    tick_screen_gillpg();
}

void tick_screen_gillpg() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_waveftpg,
    tick_screen_icepg,
    tick_screen_gillpg,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 4) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
    create_screen_waveftpg();
    create_screen_icepg();
    create_screen_gillpg();
}