#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "Adafruit_Si7021.h"

Adafruit_Si7021 ths = Adafruit_Si7021();
Adafruit_TCS34725 ls = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

int relay[4]={D5,D6,D7,D8};
int soil=A0;
bool state=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (ths.begin()) {Serial.print("Temp Sensor Init Succeeded...");}
  else {Serial.print("Temp Sensor Init failed...");}
   
  if (ls.begin()) {Serial.print("Light Sensor Init Succeeded...");}
  else {Serial.print("Light Sensor Init failed...");}
  
  pinMode(relay[0], OUTPUT);
  pinMode(relay[1], OUTPUT);
  pinMode(relay[2], OUTPUT);
  pinMode(relay[3], OUTPUT);
  pinMode(soil, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (true){

    //light sensor
    uint16_t r, g, b, c, colorTemp, lux, tmp, hmd;
    uint8_t sMoist;
    ls.getRawData(&r, &g, &b, &c);
    colorTemp = ls.calculateColorTemperature_dn40(r, g, b, c);
    lux = ls.calculateLux(r, g, b);
    Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  
    //temp and humity sensor
    hmd=ths.readHumidity();
    tmp=ths.readTemperature();
    Serial.print("Humidity: ");Serial.print(hmd, DEC);Serial.print(" ");
    Serial.print("Temperature: ");Serial.print(tmp, DEC);Serial.print(" ");
  
    //read an0 soil moisture
    sMoist = analogRead(soil);
    //sMoist = (sMoist/255)*100;
    Serial.print("Soil Moisture: ");Serial.print(sMoist);
    
    Serial.println(" ");
  
    //write D5-D8 relay outputs
    state=!state;
    digitalWrite(relay[0], state); delay(100);
    digitalWrite(relay[1], state); delay(100);
    digitalWrite(relay[2], state); delay(100);
    digitalWrite(relay[3], state);
    delay(1000);
  }
}
