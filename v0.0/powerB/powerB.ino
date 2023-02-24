#include <FastLED.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "powerB.h"

const char* ssid = "";
const char* password = "";

const int LED_PIN=15;
const int NUM_LEDS=216;
const int shape[2]={24,9};

Display display(LED_PIN,NUM_LEDS,shape,0,255);
CRGB leds[NUM_LEDS];

WebServer server(80);

int dpad[]={16,17,5,18,19};//     center,right,left,up,down
int lb=2;
int rb=4;
void hTestIp() {
  server.send(200, "text/plain", "Left:"+String(digitalRead(lb))+" Right:"+String(digitalRead(rb))+"\n dpad\n L "+String(digitalRead(dpad[0]))+" R "+String(digitalRead(dpad[1]))+" U "+String(digitalRead(dpad[2]))+" D "+String(digitalRead(dpad[3])));
}
void wifiH(){
   WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    display.solidC(20,0,0,0,1);
    display.solidC(20,0,0,8,1);
    display.frameShow();
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else
        // SPIFFS.end();
        type = "filesystem";

      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      display.solidCr(10,int(progress / (total / 100)),10,0,display.center[1]+1,int(progress / (total / display.shape[0])),display.center[1]-1);
      display.frameShow();
    })
    .onError([](ota_error_t error) {
      display.solidC(10,0,0);
      display.frameM[0][0]=CRGB(30,5,0);
      display.frameM[1][0]=CRGB(30,5,0);
      display.frameM[2][0]=CRGB(30,5,0);
      display.frameM[3][0]=CRGB(30,5,0);
      display.frameShow();
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
  }
void setup() {
    Serial.begin(115200);
    FastLED.addLeds<WS2812,LED_PIN, GRB>(display.frameA, display.length);
    wifiH();
    pinMode(lb,INPUT_PULLUP);
    pinMode(rb,INPUT_PULLUP);
    pinMode(dpad[0],INPUT_PULLUP);
    pinMode(dpad[1],INPUT_PULLUP);
    pinMode(dpad[2],INPUT_PULLUP);
    pinMode(dpad[3],INPUT_PULLUP);
    pinMode(dpad[4],INPUT_PULLUP);
    server.on("/", hTestIp);  server.begin();
    display.solidC(0,0,0);
}

void loop() {
  ArduinoOTA.handle();server.handleClient();
   if(digitalRead(lb)==1){
    display.solidC(0,100,0,23,0);
    }else{display.solidC(0,0,0,23,0);}
      if(digitalRead(rb)==1){
    display.solidC(0,100,0,0,0);
    }
    else{display.solidC(0,0,0,0,0);}
    if(digitalRead(dpad[4])==0){
    display.frameM[display.center[0]][display.center[1]+1]=CRGB(0,100,0);
    }else{    display.frameM[display.center[0]][display.center[1]+1]=CRGB(0,0,0);}
    if(digitalRead(dpad[3])==0){
    display.frameM[display.center[0]][display.center[1]-1]=CRGB(0,100,0);
    }else{    display.frameM[display.center[0]][display.center[1]-1]=CRGB(0,0,0);}
    if(digitalRead(dpad[0])==0){
    display.frameM[display.center[0]][display.center[1]]=CRGB(0,100,0);
    }else{    display.frameM[display.center[0]][display.center[1]]=CRGB(0,0,0);}
    if(digitalRead(dpad[1])==0){
    display.frameM[display.center[0]+1][display.center[1]]=CRGB(0,100,0);
    }else{    display.frameM[display.center[0]+1][display.center[1]]=CRGB(0,0,0);
    }
    if(digitalRead(dpad[2])==0){
    display.frameM[display.center[0]-1][display.center[1]]=CRGB(0,100,0);
    }else{    display.frameM[display.center[0]-1][display.center[1]]=CRGB(0,0,0);
    }
    display.frameShow();
}
