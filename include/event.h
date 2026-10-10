#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

enum MicrowaveState { IDLE, RUNNING, PAUSED, FINISHED };
enum CookMode { MODE_WAVE, MODE_DEFROST, MODE_GRILL };

extern MicrowaveState currentState;
extern CookMode selectedMode;
extern unsigned long remainingTimeMs;
extern unsigned long totalTimeMs;
extern bool isDoorOpen;

void setupRelays();
void startMicrowave(CookMode mode, unsigned long time_sec);
void stopMicrowave();
void taskMicrowaveCore(void *pvParameters);

#endif