#include "tft.h"
#include "ui.h"
  #include <Arduino_GFX_Library.h>

#define GFX_BL DF_GFX_BL
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *gfx = create_default_Arduino_GFX();
#else /* !defined(DISPLAY_DEV_KIT) */

#define GFX_BL 32
Arduino_DataBus *bus = new Arduino_ESP32SPI(2, 15, 18, 23, GFX_NOT_DEFINED);
Arduino_GFX *gfx = new Arduino_ILI9341(bus, 4, 1 /* rotation */, false /* IPS */);
#define CANVAS

#endif /* !defined(DISPLAY_DEV_KIT) */

#include "touch.hpp"
#include "event.h"

/* Change to your screen resolution */
static uint32_t screenWidth = 320;
static uint32_t screenHeight = 240;
static uint32_t bufSize;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
#ifndef DIRECT_MODE
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif
#endif // #ifndef DIRECT_MODE

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

// -------------------------------------------------------------------
// เปลี่ยนจาก setup() เป็น setupTFT()
// -------------------------------------------------------------------
void setupTFT()
{
  // pinMode(LED1, OUTPUT); // ปิดไว้ก่อน เผื่อ LED1 ไม่ได้ถูกประกาศไว้
  Serial.println("Init TFT & LVGL...");

#ifdef GFX_EXTRA_PRE_INIT
  GFX_EXTRA_PRE_INIT();
#endif

  if (!gfx->begin()) {
    Serial.println("gfx->begin() failed!");
  }
  gfx->setRotation(1); // แนวนอน
  gfx->fillScreen(RGB565_BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif

  touch_init(gfx->width(), gfx->height(), gfx->getRotation());
  lv_init();

  screenWidth = gfx->width();
  screenHeight = gfx->height();

#ifdef DIRECT_MODE
  bufSize = screenWidth * screenHeight;
#else
  bufSize = screenWidth * 40;
#endif

#ifdef ESP32
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * bufSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  if (!disp_draw_buf) {
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * bufSize, MALLOC_CAP_8BIT);
  }
#else
  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * bufSize);
#endif

  if (!disp_draw_buf) {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  }
  else {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, bufSize);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
#ifdef DIRECT_MODE
    disp_drv.direct_mode = true;
#endif
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    ui_init(); // เรียกหน้าจอจาก EEZ Studio ขึ้นมาโชว์
    Serial.println("TFT Setup done");
  }
}

void taskDisplay(void *pvParameters)
{
  for (;;) 
  {
    updateScreenData(); // 1. อัปเดตข้อมูลเซนเซอร์ก่อน
    
    lv_timer_handler(); // 2. สั่งให้จอวาดภาพตามข้อมูลใหม่

    // ... (โค้ด flush จอส่วนที่เหลือ) ...
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}