#include <Arduino.h>
#include "event.h"
#include "tft.h" 

void setup() {
  Serial.begin(115200);
  
  setupRelays();
  setupTFT(); 

  // Core 1 สำหรับคุมฮาร์ดแวร์ไมโครเวฟและจับเวลา
  xTaskCreatePinnedToCore(taskMicrowaveCore, "Microwave_Task", 4096, NULL, 2, NULL, 1);
  
  // Core 0 สำหรับแสดงผลจอ UI (ลดอาการจอกระตุกเมื่อดึงทรัพยากร)
  xTaskCreatePinnedToCore(taskDisplay, "Display_Task", 8192, NULL, 1, NULL, 0); 
}

void loop() {
  vTaskDelete(NULL); 
}