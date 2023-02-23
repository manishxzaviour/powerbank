 #include <FastLED.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "";
const char* password = "";

#define LED_PIN     15
#define NUM_LEDS    216

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
//    
//  for(int i=0;i<NUM_LEDS;i++){
//    leds[i] = CRGB(255, 255, 255);
//    }
//        FastLED.show();
//  for(int i=NUM_LEDS;i>0;i--){
//  leds[i] = CRGB(0, 0, 0);
////  delay(50);
//    }
// FastLED.show();
//      
//  for(int i=0;i<NUM_LEDS;i++){
//  leds[i] = CRGB(255, 0, 0);
//  FastLED.show();
//  delay(50);
//    }
//      
//  for(int i=0;i<NUM_LEDS;i++){
//  leds[i] = CRGB(0, 255, 0);
//  FastLED.show();
//  delay(50);
//    }
//    
//  for(int i=0;i<NUM_LEDS;i++){
//  leds[i] = CRGB(0, 0, 255);
//  FastLED.show();
//  delay(50);
//    }
}

void loop() {
  ArduinoOTA.handle();
}
