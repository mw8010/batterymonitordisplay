/*******************************************************************************
 * Start of Arduino_GFX setting
 *
 * Arduino_GFX try to find the settings depends on selected board in Arduino IDE
 * Or you can define the display dev kit not in the board list
 * Defalult pin list for non display dev kit:
 * Arduino Nano, Micro and more: CS:  9, DC:  8, RST:  7, BL:  6, SCK: 13, MOSI: 11, MISO: 12
 * ESP32 various dev board     : CS:  5, DC: 27, RST: 33, BL: 22, SCK: 18, MOSI: 23, MISO: nil
 * ESP32-C3 various dev board  : CS:  7, DC:  2, RST:  1, BL:  3, SCK:  4, MOSI:  6, MISO: nil
 * ESP32-S2 various dev board  : CS: 34, DC: 38, RST: 33, BL: 21, SCK: 36, MOSI: 35, MISO: nil
 * ESP32-S3 various dev board  : CS: 40, DC: 41, RST: 42, BL: 48, SCK: 36, MOSI: 35, MISO: nil
 * ESP8266 various dev board   : CS: 15, DC:  4, RST:  2, BL:  5, SCK: 14, MOSI: 13, MISO: 12
 * Raspberry Pi Pico dev board : CS: 17, DC: 27, RST: 26, BL: 28, SCK: 18, MOSI: 19, MISO: 16
 * RTL8720 BW16 old patch core : CS: 18, DC: 17, RST:  2, BL: 23, SCK: 19, MOSI: 21, MISO: 20
 * RTL8720_BW16 Official core  : CS:  9, DC:  8, RST:  6, BL:  3, SCK: 10, MOSI: 12, MISO: 11
 * RTL8722 dev board           : CS: 18, DC: 17, RST: 22, BL: 23, SCK: 13, MOSI: 11, MISO: 12
 * RTL8722_mini dev board      : CS: 12, DC: 14, RST: 15, BL: 13, SCK: 11, MOSI:  9, MISO: 10
 * Seeeduino XIAO dev board    : CS:  3, DC:  2, RST:  1, BL:  0, SCK:  8, MOSI: 10, MISO:  9
 * Teensy 4.1 dev board        : CS: 39, DC: 41, RST: 40, BL: 22, SCK: 13, MOSI: 11, MISO: 12
 ******************************************************************************/
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/signalk/signalk_listener.h"
#include "sensesp/system/observable.h"
#include "sensesp/system/valueproducer.h"
#include "sensesp/ui/config_item.h"
#include "sensesp/ui/ui_controls.h"
#include "sensesp_app_builder.h"
#include "touch.h"
#include "lvgl.h"
#include "ui.h"
#include "ui_helpers.h"

using namespace sensesp;

// Setze Wifi-Netzwerkdaten
const char* hostname = "Batteriemonitor_Display";

// Definiere Variablen für die Batterienamen
String battery_names[4] = {"Versorger", "Motor 1", "Motor 2", "Bug"};
String battery_name_config_paths[4] = {"/config/battery_name1", "/config/battery_name2", "/config/battery_name3", "/config/battery_name4"};

//Erstelle die vollständigen SignalK Pfade durch Konketenation
String sk_path_current[4];
String sk_path_voltage[4];
String sk_path_temperature[4];
String sk_path_time_remaining[4];

void setupBatteries() {
  for (int i = 0; i < 4; i++) {
    auto battery_name_config = std::make_shared<StringConfig>(battery_names[i], battery_name_config_paths[i]);

    ConfigItem(battery_name_config)
      ->set_title("Battery Name " + String(i + 1))
      ->set_description("Name of the Battery from Signal K Path (e.g. electrical.batteries.house.voltage -> The Name of the Battery is house)") // Der Name der Batterie aus dem Signal K. Bsp: electrical.batteries.house.voltage -> 'house' ist der Name der Batterie
      ->set_sort_order(600 + i * 100);

    //Lade die Konfigurationswerte der Batterie
    battery_names[i] = battery_name_config->get_value();

    //Aktualisiere die SignalK-Pfade basierend auf den geladenen Konfigurationswerten
    sk_path_current[i] = "electrical.batteries." + battery_names[i] + ".current";
    sk_path_voltage[i] = "electrical.batteries." + battery_names[i] + ".voltage";
    sk_path_temperature[i] = "electrical.batteries." + battery_names[i] + ".temperature";
    sk_path_time_remaining[i] = "electrical.batteries." + battery_names[i] + ".time_remaining";
  }
}
// Display Backlight
unsigned long lastTouchTime = 0;
const unsigned long backlightTimeout = 30000; // 30 seconds


void voltage_callback(const String& path, float voltage) {
  static std::map<String, lv_obj_t*> voltageLabels = {
    {sk_path_voltage[0], ui_lblvoltagemain},
    {sk_path_voltage[1], ui_lblvoltagemotor1},
    {sk_path_voltage[2], ui_lblvoltagemotor2},
    {sk_path_voltage[3], ui_lblvoltagebug}
  };

  char voltageStr[10];
  dtostrf(voltage, 4, 2, voltageStr);

  if (voltageLabels.count(path) && voltageLabels[path] != nullptr) {
    lv_label_set_text(voltageLabels[path], voltageStr);
  }
 
}

// Anzeige Charge oder Discharge am Display
void state_callback(const String& path, float current) {
  if (current < 0) {
    lv_img_set_src(ui_imgcharge, &ui_img_charge_png);
    lv_img_set_src(ui_imgchargetrans, & ui_img_charge_trans_png);
  }
}

void current_callback(const String& path, float current){
  if (path == sk_path_current[0]) {
    lv_label_set_text(ui_labelAmp, String(current).c_str());
  }
}

void temperature_callback(const String& path, float temperature){
  static std::map<String, lv_obj_t*> temperatureLabels = {
    {sk_path_temperature[0], ui_lbltempmain},
    {sk_path_temperature[1], ui_lbltempmotor1},
    {sk_path_temperature[2], ui_lbltempmotor2},
    {sk_path_temperature[3], ui_lbltempbug}
  };

  char temperatureStr[10];
  dtostrf(temperature, 4, 2, temperatureStr);

  if (temperatureLabels.count(path) && temperatureLabels[path] != nullptr) {
    lv_label_set_text(temperatureLabels[path], temperatureStr);
  }
}

void timeremain_callback(const String& path, float timeremain){
  if (path == sk_path_time_remaining[0]) {
    lv_label_set_text(ui_lblrmainmain, String(timeremain).c_str());
  }
}

void time_callback(const String& path, const String& datetime){
  if (path == "navigation.datetime") {
    String time = datetime.substring(11, 16);
    lv_label_set_text(ui_lblTime, time.c_str());
  }
}


// Signal K Listener Klassen

class FloatValueListener : public sensesp::SKListener {
public:
  FloatValueListener(const String& sk_path, void (*callback)(const String&, float)) 
    : SKListener(sk_path, 1000), sk_path(sk_path), callback(callback) {}

  void parse_value(const JsonObject& json) override {
    if (json["value"].is<float>()) {
      float value = json["value"];
      callback(sk_path, value);
    } else {
      Serial.println("Fehler: Ungültiger Wert erhalten");
    }
  }

private:
  String sk_path;
  void (*callback)(const String&, float);
};

class TimeListener : public sensesp::SKListener {
  public:
    TimeListener(const String& sk_path) : SKListener(sk_path, 1000), sk_path(sk_path) {}
    void parse_value(const JsonObject& json) override {
      if (json["value"].is<const char*>()) {
      String datetime = json["value"].as<const char*>();
      time_callback(sk_path, datetime);
    } else {
      Serial.println("Fehler: Ungültiger Wert erhalten");
    }
  }
  private:
  String sk_path;
};




//Display initialisieren

#define GFX_BL 1
Arduino_DataBus *bus = new Arduino_ESP32QSPI(
    45 /* cs */, 47 /* sck */, 21 /* d0 */, 48 /* d1 */, 40 /* d2 */, 39 /* d3 */);
Arduino_GFX *g = new Arduino_NV3041A(bus, GFX_NOT_DEFINED /* RST */, 0 /* rotation */, true /* IPS */);
Arduino_GFX *gfx = new Arduino_Canvas(480 /* width */, 272 /* height */, g);
#define CANVAS

/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

/*******************************************************************************
 * Please config the touch panel in touch.h
 ******************************************************************************/

void touchWakeup() {
    lastTouchTime = millis();
    digitalWrite(GFX_BL, HIGH); // Turn on the backlight
};

/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
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

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;

      // Aktualisiere die letzte Berührungszeit 
      touchWakeup();
      //lastTouchTime = millis(); 
      //digitalWrite(GFX_BL, HIGH); // Turn on the backlight
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

void setup()
{
  Serial.begin(115200);
  Serial.println("Kassiopeia Batteriemonitor");


#ifdef GFX_EXTRA_PRE_INIT
  GFX_EXTRA_PRE_INIT();
#endif

  // Init Display
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif

  // Init touch device
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
  if (!disp_draw_buf)
  {
    // remove MALLOC_CAP_INTERNAL flag try again
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * bufSize, MALLOC_CAP_8BIT);
  }
#else
  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * bufSize);
#endif
  if (!disp_draw_buf)
  {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  }
  else
  {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, bufSize);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
#ifdef DIRECT_MODE
    disp_drv.direct_mode = true;
#endif
    lv_disp_drv_register(&disp_drv);

    /* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
  }

   SensESPAppBuilder builder;
    sensesp_app = (&builder)
                  //-> enable_uptime_sensor()
                  -> set_hostname(hostname)
                  -> get_app();

    if (sensesp_app == nullptr) {
        printf("Unable to create SensESPApp\n");
        return;
    }

//setup Batteries
setupBatteries();
//initialisiere die UI
ui_init();

// Signal K Listener abonnieren
for (int i = 0; i < 4; i++) {
  new FloatValueListener(sk_path_voltage[i], voltage_callback);
  new FloatValueListener(sk_path_current[i], state_callback);
  new FloatValueListener(sk_path_temperature[i], temperature_callback);
  new FloatValueListener(sk_path_time_remaining[i], timeremain_callback);
}

new TimeListener("navigation.datetime");

new FloatValueListener("electrical.batteries.main.time_remaining", timeremain_callback);

Serial.println("LVGL: Display initialized");

}

void loop()
{
  // LVGL Timer Handler
  unsigned long currentTime = millis();

  event_loop()->tick();
  
  //reconnectWiFi();
 // webSocketPoll();
  
  lv_timer_handler();

  

#ifdef DIRECT_MODE
#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(0, 0, (uint16_t *)disp_draw_buf, screenWidth, screenHeight);
#else
  gfx->draw16bitRGBBitmap(0, 0, (uint16_t *)disp_draw_buf, screenWidth, screenHeight);
#endif
#endif // #ifdef DIRECT_MODE

#ifdef CANVAS
  gfx->flush();
#endif

 delay(5);
  
   if (currentTime - lastTouchTime > backlightTimeout) {
    digitalWrite(GFX_BL, LOW);
  } else {
    digitalWrite(GFX_BL, HIGH);
  } 

  
}