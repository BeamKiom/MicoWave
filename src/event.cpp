#include "event.h"

// กำหนดขารีเลย์และเซนเซอร์
const int RELAY_MAIN = 25;   // พัดลม, ไฟ, จานหมุน
const int RELAY_MAG = 26;    // แมกนีตรอน (คลื่นไมโครเวฟ)
const int RELAY_GRILL = 13;  // ขดลวดย่าง (ถ้าขา 13 มีปัญหาให้เปลี่ยนเป็น 32 หรือ 33)
const int DOOR_SWITCH = 34;  // สวิตช์ประตู (PULLUP: ลอยสาย = เปิด, ลง GND = ปิด)

MicrowaveState currentState = IDLE;
CookMode selectedMode = MODE_WAVE;
unsigned long remainingTimeMs = 0;
unsigned long totalTimeMs = 0;
bool isDoorOpen = false;

// ==========================================
// การตั้งค่า Duty Cycle
// ==========================================
// โหมด Wave (สัดส่วน 70:30 รอบละ 10 วินาที)
const unsigned long WAVE_ON_TIME = 7000;    // จ่ายความร้อน 7 วิ
const unsigned long WAVE_OFF_TIME = 3000;   // พัก 3 วิ

// โหมด Defrost / Ice (สัดส่วน 20:80 รอบละ 10 วินาที)
const unsigned long DEFROST_ON_TIME = 2000;  // จ่ายความร้อน 2 วิ
const unsigned long DEFROST_OFF_TIME = 8000; // พัก 8 วิ

// โหมด Grill (จ่ายความร้อน 6 นาที พัก 2 นาที ถนอมรีเลย์)
const unsigned long GRILL_ON_TIME = 360000;  // 6 นาที (6 * 60 * 1000 ms)
const unsigned long GRILL_OFF_TIME = 120000; // 2 นาที (2 * 60 * 1000 ms)

void setupRelays() {
  pinMode(RELAY_MAIN, OUTPUT);
  pinMode(RELAY_MAG, OUTPUT);
  pinMode(RELAY_GRILL, OUTPUT);
  pinMode(DOOR_SWITCH, INPUT_PULLUP); 
  
  digitalWrite(RELAY_MAIN, LOW);
  digitalWrite(RELAY_MAG, LOW);
  digitalWrite(RELAY_GRILL, LOW);
}

void startMicrowave(CookMode mode, unsigned long time_sec) {
  if (time_sec == 0 || isDoorOpen) return;
  
  selectedMode = mode;
  totalTimeMs = time_sec * 1000;
  remainingTimeMs = totalTimeMs;
  currentState = RUNNING;
}

void stopMicrowave() {
  currentState = IDLE;
  remainingTimeMs = 0;
  digitalWrite(RELAY_MAIN, LOW);
  digitalWrite(RELAY_MAG, LOW);
  digitalWrite(RELAY_GRILL, LOW);
}

void taskMicrowaveCore(void *pvParameters) {
  unsigned long lastTick = millis();
  
  for (;;) {
    unsigned long currentMillis = millis();
    unsigned long dt = currentMillis - lastTick; 
    lastTick = currentMillis;

    // 1. อ่านสถานะประตู
    isDoorOpen = (digitalRead(DOOR_SWITCH) == HIGH); 
    
    // --- ระบบหยุด/ทำงานต่อ อัตโนมัติ (Auto-resume) ---
    if (isDoorOpen) {
      digitalWrite(RELAY_MAIN, LOW);
      digitalWrite(RELAY_MAG, LOW);
      digitalWrite(RELAY_GRILL, LOW);
      if (currentState == RUNNING) currentState = PAUSED; 
    } else {
      if (currentState == PAUSED) currentState = RUNNING; 
    }

    // 2. ควบคุมเวลาและ Duty Cycle
    if (currentState == RUNNING && !isDoorOpen) {
      if (remainingTimeMs > dt) {
        remainingTimeMs -= dt;
      } else {
        remainingTimeMs = 0;
        stopMicrowave();      
        currentState = FINISHED; 
      }

      if (currentState == RUNNING) {
        digitalWrite(RELAY_MAIN, HIGH); // พัดลม/จานหมุน ติดตลอด

        // ดึงค่าเวลา On/Off ตามโหมดที่เลือก
        unsigned long onTime, offTime;
        if (selectedMode == MODE_WAVE) {
            onTime = WAVE_ON_TIME; 
            offTime = WAVE_OFF_TIME;
        } else if (selectedMode == MODE_DEFROST) {
            onTime = DEFROST_ON_TIME; 
            offTime = DEFROST_OFF_TIME;
        } else { // MODE_GRILL
            onTime = GRILL_ON_TIME; 
            offTime = GRILL_OFF_TIME;
        }

        // คำนวณจังหวะการติดดับ (Duty Cycle)
        unsigned long cyclePeriod = onTime + offTime;
        unsigned long elapsed = totalTimeMs - remainingTimeMs;
        unsigned long cyclePosition = elapsed % cyclePeriod;
        bool shouldTurnOn = (cyclePosition < onTime);

        // สั่งงานรีเลย์
        if (selectedMode == MODE_GRILL) {
            digitalWrite(RELAY_MAG, LOW); // แมกนีตรอนดับ
            digitalWrite(RELAY_GRILL, shouldTurnOn ? HIGH : LOW); // ย่างติดสลับดับ
        } else {
            digitalWrite(RELAY_GRILL, LOW); // ย่างดับ
            digitalWrite(RELAY_MAG, shouldTurnOn ? HIGH : LOW); // แมกนีตรอนติดสลับดับ
        }
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); 
  }
}