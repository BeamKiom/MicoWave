#ifndef TFT_H
#define TFT_H

// ฟังก์ชันตั้งค่าเริ่มต้นสำหรับจอและ LVGL
void setupTFT();

// Task ของ FreeRTOS สำหรับรันการแสดงผล UI
void taskDisplay(void *pvParameters);

// ฟังก์ชันอัปเดตข้อมูลตัวเลขเวลาและสถานะประตูขึ้นหน้าจอ
void updateScreenData(); 

#endif