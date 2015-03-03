#include "Wire.h"
#include "SPI.h"
#include "Servo.h"
#include "DroneLibs.h"

HardwareSerial *commSerial	= &Serial;
Storage<float> *storage	= eeStorage::getInstance();
CommManager		manager(commSerial, storage);
Settings		settings(storage);
uint32_t 		time;
Waypoint		loc;

//this needs some settings and eStop
uint32_t		walkInterval;

void setupSettings(){
	using namespace AirSettings;	
	settings.attach(INT_PERIOD	, 1000.f, callback<uint32_t, &walkInterval>);
	settings.attach(UNUSED_I	, 1234.f, NULL);
	settings.attach(UNUSED_H	, 2025.f, NULL);
	settings.attach(UNUSED_G	, 1337.f, NULL);
}
void setup(){
	setupSettings();
	Serial.begin(9600);
	delay(500);
	manager.requestResync();
	time = millis();
}

void loop(){
	manager.update();
	if(time <= millis()){
		time += walkInterval;

		loc = manager.getTargetWaypoint();
		manager.sendTelem(Protocol::telemetryType(LATITUDE) , loc.degLatitude());
		manager.sendTelem(Protocol::telemetryType(LONGITUDE), loc.degLongitude());
		
		//advance waypoint list
		if(manager.getTargetIndex() < manager.numWaypoints()-1){
			manager.advanceTargetIndex();
		}
		else if (manager.loopWaypoints()){
			manager.setTargetIndex(0);
		}
	}
}