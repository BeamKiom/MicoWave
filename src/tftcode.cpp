#include "tft.h"
#include "ui.h"
#include "event.h"
#include <Arduino.h>

// ==========================================
// ตัวแปรสำหรับดักการกดปุ่ม (Edge Trigger)
// ป้องกันการกดค้างแล้วคำสั่งรันรัวๆ
// ==========================================
// ปุ่มเปลี่ยนหน้าจอ
static bool last_wave_bt = false;
static bool last_ice_bt = false;
static bool last_gill_bt = false; // เผื่อคุณทำปุ่มเข้าหน้า Grill ที่หน้า Main
static bool last_go_main = false, last_go_main1 = false, last_go_main2 = false;

// ปุ่ม Start / Stop
static bool last_start_wave = false, last_stop_wave = false;
static bool last_start_ice = false, last_stop_ice = false;
static bool last_start_gill = false, last_stop_gill = false;

// ปุ่มตั้งเวลา โหมด Wave
static bool last_plus_h = false, last_dep_h = false;
static bool last_plus_m = false, last_dep_m = false;
static bool last_plus_s = false, last_dep_s = false;

// ปุ่มตั้งเวลา โหมด Ice (อ้างอิงชื่อจากภาพ EEZ Studio)
static bool last_plus_h_1 = false, last_dep_h_1 = false;
static bool last_plus_s_1 = false, last_dep_h_2 = false; 
static bool last_plus_h_2 = false, last_dep_h_3 = false; 

// ปุ่มตั้งเวลา โหมด Grill (อ้างอิงชื่อจากภาพ EEZ Studio)
static bool last_plus_h_gill = false, last_dep_s_gill = false; 
static bool last_plus_m_gill = false, last_dep_m_gill = false;
static bool last_plus_s_gill = false, last_dep_h_gill = false; 

// ==========================================
// ฟังก์ชันเปลี่ยนสีและข้อความของ Label ประตู
// ==========================================
void updateDoorLabel(lv_obj_t *label) {
    if (label == NULL) return;
    if (isDoorOpen) {
        lv_label_set_text(label, "OPEN");
        lv_obj_set_style_text_color(label, lv_color_hex(0xFF0000), LV_PART_MAIN); // สีแดง
    } else {
        lv_label_set_text(label, "CLOSED");
        lv_obj_set_style_text_color(label, lv_color_hex(0x00FF00), LV_PART_MAIN); // สีเขียว
    }
}

// ==========================================
// ฟังก์ชันหลักที่จอจะเรียกใช้ตลอดเวลา
// ==========================================
void updateScreenData() {
    // --------------------------------------------------
    // 1. อัปเดตแจ้งเตือนสถานะประตู ในทุกหน้า
    // --------------------------------------------------
    updateDoorLabel(objects.door_3); // หน้า wave
    updateDoorLabel(objects.door_2); // หน้า ice
    updateDoorLabel(objects.door_1); // หน้า gill

    // --------------------------------------------------
    // 2. อัปเดตตัวเลขเวลานับถอยหลัง (ขณะทำงาน)
    // --------------------------------------------------
    if (currentState == RUNNING || currentState == PAUSED) {
        int totalSec = remainingTimeMs / 1000;
        int h = totalSec / 3600;
        int m = (totalSec % 3600) / 60;
        int s = totalSec % 60;

        if (selectedMode == MODE_WAVE) {
            if (objects.hr) lv_spinbox_set_value(objects.hr, h);
            if (objects.min) lv_spinbox_set_value(objects.min, m);
            if (objects.sec) lv_spinbox_set_value(objects.sec, s);
        } else if (selectedMode == MODE_DEFROST) {
            if (objects.hr_1) lv_spinbox_set_value(objects.hr_1, h);
            if (objects.min_1) lv_spinbox_set_value(objects.min_1, m);
            if (objects.sec_1) lv_spinbox_set_value(objects.sec_1, s);
        } else if (selectedMode == MODE_GRILL) {
            if (objects.hour_gill) lv_spinbox_set_value(objects.hour_gill, h);
            if (objects.min_gill) lv_spinbox_set_value(objects.min_gill, m);
            if (objects.sec_gill) lv_spinbox_set_value(objects.sec_gill, s);
        }
    }

    // --------------------------------------------------
    // 3. ตรวจสอบการกดปุ่มเปลี่ยนหน้าจอ
    // --------------------------------------------------
   if (objects.wave_bt) {
        bool pressed = lv_obj_has_state(objects.wave_bt, LV_STATE_PRESSED);
        if (pressed && !last_wave_bt) lv_scr_load(objects.waveftpg);
        last_wave_bt = pressed;
    }
    if (objects.ice_bt) {
        bool pressed = lv_obj_has_state(objects.ice_bt, LV_STATE_PRESSED);
        if (pressed && !last_ice_bt) lv_scr_load(objects.icepg);
        last_ice_bt = pressed;
    }
    
    // ---- เพิ่มบล็อกนี้เข้าไปเพื่อเปลี่ยนไปหน้า Grill ----
    if (objects.gill_bt) {
        bool pressed = lv_obj_has_state(objects.gill_bt, LV_STATE_PRESSED);
        if (pressed && !last_gill_bt) lv_scr_load(objects.gillpg);
        last_gill_bt = pressed;
    }
    
    // ปุ่มกลับหน้า Main จากหน้าต่างๆ
    if (objects.go_main) {
        bool pressed = lv_obj_has_state(objects.go_main, LV_STATE_PRESSED);
        if (pressed && !last_go_main) lv_scr_load(objects.main);
        last_go_main = pressed;
    }
    if (objects.go_main_1) {
        bool pressed = lv_obj_has_state(objects.go_main_1, LV_STATE_PRESSED);
        if (pressed && !last_go_main1) lv_scr_load(objects.main);
        last_go_main1 = pressed;
    }
    if (objects.go_main_2) {
        bool pressed = lv_obj_has_state(objects.go_main_2, LV_STATE_PRESSED);
        if (pressed && !last_go_main2) lv_scr_load(objects.main);
        last_go_main2 = pressed;
    }

    // --------------------------------------------------
    // 4. ตรวจสอบปุ่มตั้งเวลา และ Start/Stop (โหมด WAVE)
    // --------------------------------------------------
    // Hour
    if (objects.plus_h) {
        bool pressed = lv_obj_has_state(objects.plus_h, LV_STATE_PRESSED);
        if (pressed && !last_plus_h) lv_spinbox_increment(objects.hr);
        last_plus_h = pressed;
    }
    if (objects.depreciate_h) {
        bool pressed = lv_obj_has_state(objects.depreciate_h, LV_STATE_PRESSED);
        if (pressed && !last_dep_h) lv_spinbox_decrement(objects.hr);
        last_dep_h = pressed;
    }
    // Minute
    if (objects.plus_m) {
        bool pressed = lv_obj_has_state(objects.plus_m, LV_STATE_PRESSED);
        if (pressed && !last_plus_m) lv_spinbox_increment(objects.min);
        last_plus_m = pressed;
    }
    if (objects.depreciate_m) {
        bool pressed = lv_obj_has_state(objects.depreciate_m, LV_STATE_PRESSED);
        if (pressed && !last_dep_m) lv_spinbox_decrement(objects.min);
        last_dep_m = pressed;
    }
    // Second
    if (objects.plus_s) {
        bool pressed = lv_obj_has_state(objects.plus_s, LV_STATE_PRESSED);
        if (pressed && !last_plus_s) lv_spinbox_increment(objects.sec);
        last_plus_s = pressed;
    }
    if (objects.depreciate_s) {
        bool pressed = lv_obj_has_state(objects.depreciate_s, LV_STATE_PRESSED);
        if (pressed && !last_dep_s) lv_spinbox_decrement(objects.sec);
        last_dep_s = pressed;
    }
    // Start / Stop Wave
    if (objects.start_wavefoot) {
        bool pressed = lv_obj_has_state(objects.start_wavefoot, LV_STATE_PRESSED);
        if (pressed && !last_start_wave && !isDoorOpen) {
            int h = lv_spinbox_get_value(objects.hr);
            int m = lv_spinbox_get_value(objects.min);
            int s = lv_spinbox_get_value(objects.sec);
            startMicrowave(MODE_WAVE, (h * 3600) + (m * 60) + s);
        }
        last_start_wave = pressed;
    }
    if (objects.stop_wavefoot) {
        bool pressed = lv_obj_has_state(objects.stop_wavefoot, LV_STATE_PRESSED);
        if (pressed && !last_stop_wave) {
            stopMicrowave();
            if(objects.hr) lv_spinbox_set_value(objects.hr, 0); 
            if(objects.min) lv_spinbox_set_value(objects.min, 0); 
            if(objects.sec) lv_spinbox_set_value(objects.sec, 0);
        }
        last_stop_wave = pressed;
    }

// --------------------------------------------------
    // 5. ตรวจสอบปุ่มตั้งเวลา และ Start/Stop (โหมด ICE / DEFROST)
    // --------------------------------------------------
    // Hour
    if (objects.plus_h_1) {
        bool pressed = lv_obj_has_state(objects.plus_h_1, LV_STATE_PRESSED);
        if (pressed && !last_plus_h_1) lv_spinbox_increment(objects.hr_1);
        last_plus_h_1 = pressed;
    }
    if (objects.depreciate_h_1) {
        bool pressed = lv_obj_has_state(objects.depreciate_h_1, LV_STATE_PRESSED);
        if (pressed && !last_dep_h_1) lv_spinbox_decrement(objects.hr_1);
        last_dep_h_1 = pressed;
    }

    // Minute (ใช้ plus_h_2 และ depreciate_h_2)
    if (objects.plus_h_2) {
        bool pressed = lv_obj_has_state(objects.plus_h_2, LV_STATE_PRESSED);
        if (pressed && !last_plus_h_2) lv_spinbox_increment(objects.min_1);
        last_plus_h_2 = pressed;
    }
    if (objects.depreciate_h_2) {
        bool pressed = lv_obj_has_state(objects.depreciate_h_2, LV_STATE_PRESSED);
        if (pressed && !last_dep_h_2) lv_spinbox_decrement(objects.min_1);
        last_dep_h_2 = pressed;
    }

    // Second (ใช้ plus_s_1 และ depreciate_h_3)
    if (objects.plus_s_1) {
        bool pressed = lv_obj_has_state(objects.plus_s_1, LV_STATE_PRESSED);
        if (pressed && !last_plus_s_1) lv_spinbox_increment(objects.sec_1);
        last_plus_s_1 = pressed;
    }
    if (objects.depreciate_h_3) {
        bool pressed = lv_obj_has_state(objects.depreciate_h_3, LV_STATE_PRESSED);
        if (pressed && !last_dep_h_3) lv_spinbox_decrement(objects.sec_1);
        last_dep_h_3 = pressed;
    }

    // Start / Stop Ice
    if (objects.start_ice) {
        bool pressed = lv_obj_has_state(objects.start_ice, LV_STATE_PRESSED);
        if (pressed && !last_start_ice && !isDoorOpen) {
            int h = lv_spinbox_get_value(objects.hr_1);
            int m = lv_spinbox_get_value(objects.min_1);
            int s = lv_spinbox_get_value(objects.sec_1);
            startMicrowave(MODE_DEFROST, (h * 3600) + (m * 60) + s);
        }
        last_start_ice = pressed;
    }
    if (objects.stop_ice) {
        bool pressed = lv_obj_has_state(objects.stop_ice, LV_STATE_PRESSED);
        if (pressed && !last_stop_ice) {
            stopMicrowave();
            if(objects.hr_1) lv_spinbox_set_value(objects.hr_1, 0); 
            if(objects.min_1) lv_spinbox_set_value(objects.min_1, 0); 
            if(objects.sec_1) lv_spinbox_set_value(objects.sec_1, 0);
        }
        last_stop_ice = pressed;
    }
// --------------------------------------------------
    // 6. ตรวจสอบปุ่มตั้งเวลา และ Start/Stop (โหมด GRILL)
    // --------------------------------------------------
    // Hour
    if (objects.plus_h_gill) {
        bool pressed = lv_obj_has_state(objects.plus_h_gill, LV_STATE_PRESSED);
        if (pressed && !last_plus_h_gill) lv_spinbox_increment(objects.hour_gill);
        last_plus_h_gill = pressed;
    }
    if (objects.depreciate_h_gill) { // แก้ให้ตรงกับ Hour
        bool pressed = lv_obj_has_state(objects.depreciate_h_gill, LV_STATE_PRESSED);
        if (pressed && !last_dep_h_gill) lv_spinbox_decrement(objects.hour_gill);
        last_dep_h_gill = pressed;
    }
    // Minute
    if (objects.plus_m_gill) {
        bool pressed = lv_obj_has_state(objects.plus_m_gill, LV_STATE_PRESSED);
        if (pressed && !last_plus_m_gill) lv_spinbox_increment(objects.min_gill);
        last_plus_m_gill = pressed;
    }
    if (objects.depreciate_m_gill) {
        bool pressed = lv_obj_has_state(objects.depreciate_m_gill, LV_STATE_PRESSED);
        if (pressed && !last_dep_m_gill) lv_spinbox_decrement(objects.min_gill);
        last_dep_m_gill = pressed;
    }
    // Second
    if (objects.plus_s_gill) {
        bool pressed = lv_obj_has_state(objects.plus_s_gill, LV_STATE_PRESSED);
        if (pressed && !last_plus_s_gill) lv_spinbox_increment(objects.sec_gill);
        last_plus_s_gill = pressed;
    }
    if (objects.depreciate_s_gill) { // แก้ให้ตรงกับ Second
        bool pressed = lv_obj_has_state(objects.depreciate_s_gill, LV_STATE_PRESSED);
        if (pressed && !last_dep_s_gill) lv_spinbox_decrement(objects.sec_gill);
        last_dep_s_gill = pressed;
    }
    
    // Start / Stop Grill
    if (objects.start_gill) {
        bool pressed = lv_obj_has_state(objects.start_gill, LV_STATE_PRESSED);
        if (pressed && !last_start_gill && !isDoorOpen) {
            int h = lv_spinbox_get_value(objects.hour_gill);
            int m = lv_spinbox_get_value(objects.min_gill);
            int s = lv_spinbox_get_value(objects.sec_gill);
            startMicrowave(MODE_GRILL, (h * 3600) + (m * 60) + s);
        }
        last_start_gill = pressed;
    }
    if (objects.stop_gill) {
        bool pressed = lv_obj_has_state(objects.stop_gill, LV_STATE_PRESSED);
        if (pressed && !last_stop_gill) {
            stopMicrowave();
            if(objects.hour_gill) lv_spinbox_set_value(objects.hour_gill, 0); 
            if(objects.min_gill) lv_spinbox_set_value(objects.min_gill, 0); 
            if(objects.sec_gill) lv_spinbox_set_value(objects.sec_gill, 0);
        }
        last_stop_gill = pressed;
    }
}