#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_WAVEFTPG = 2,
    SCREEN_ID_ICEPG = 3,
    SCREEN_ID_GILLPG = 4,
    _SCREEN_ID_LAST = 4
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *waveftpg;
    lv_obj_t *icepg;
    lv_obj_t *gillpg;
    lv_obj_t *wave_bt;
    lv_obj_t *ice_bt;
    lv_obj_t *gill_bt;
    lv_obj_t *hr;
    lv_obj_t *min;
    lv_obj_t *sec;
    lv_obj_t *plus_h;
    lv_obj_t *plus_m;
    lv_obj_t *plus_s;
    lv_obj_t *depreciate_h;
    lv_obj_t *depreciate_m;
    lv_obj_t *depreciate_s;
    lv_obj_t *go_main;
    lv_obj_t *start_wavefoot;
    lv_obj_t *stop_wavefoot;
    lv_obj_t *door_3;
    lv_obj_t *hr_1;
    lv_obj_t *min_1;
    lv_obj_t *sec_1;
    lv_obj_t *plus_h_1;
    lv_obj_t *plus_s_1;
    lv_obj_t *depreciate_h_1;
    lv_obj_t *go_main_1;
    lv_obj_t *plus_h_2;
    lv_obj_t *depreciate_h_2;
    lv_obj_t *depreciate_h_3;
    lv_obj_t *start_ice;
    lv_obj_t *stop_ice;
    lv_obj_t *door_2;
    lv_obj_t *depreciate_h_gill;
    lv_obj_t *go_main_2;
    lv_obj_t *plus_m_gill;
    lv_obj_t *depreciate_m_gill;
    lv_obj_t *depreciate_s_gill;
    lv_obj_t *start_gill;
    lv_obj_t *stop_gill;
    lv_obj_t *sec_gill;
    lv_obj_t *min_gill;
    lv_obj_t *hour_gill;
    lv_obj_t *plus_h_gill;
    lv_obj_t *plus_s_gill;
    lv_obj_t *door_1;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_waveftpg();
void tick_screen_waveftpg();

void create_screen_icepg();
void tick_screen_icepg();

void create_screen_gillpg();
void tick_screen_gillpg();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/