#include "Wire.h"
#include "SPI.h"
#include "MINDS-i-Drone.h"
/*
Altimeter, get a raw value and maybe a converted value to feet?
(through the Arduino Serial Terminal)
*/

MS5611 baro;

void setup(){
    Serial.begin(9600);

    baro.begin();
    delay(100);
    baro.calibrate();
}
void loop(){
    baro.update();

    float temp = baro.getCelsius();
    float bar  = baro.getMilliBar();
    float alt  = baro.getAltitude();

    Serial.print("temp: ");
    Serial.print(temp);
    Serial.print("\t");
    Serial.print("mbar: ");
    Serial.print(bar);
    Serial.print("\t");
    Serial.print("alt: ");
    Serial.print(alt);
    Serial.println();
}
