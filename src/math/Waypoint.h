#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "SpatialMath.h"
#ifndef STAND_ALONE_MATH
	#include "comms/Protocol.h"
#else
	#include <stdint.h>
#endif

class Waypoint{
public:
	float lat, lng; //these are stored in degrees
	uint16_t extra; //8.8 fixed value used for altitude (air) or speed (ground)
	Waypoint():
			lat(0), lng(0), extra(0) {}
	Waypoint(float latitude, float longitude): //entry in degrees
			lat(latitude), lng(longitude), extra(0) {}
	Waypoint(float latitude, float longitude, bool rad):
			lat(latitude), lng(longitude), extra(0) {
		if(rad){
			lat = toDeg(latitude);
			lng = toDeg(longitude);
		} //if not set to radians, they will stay initialized to degrees
	}
	Waypoint(float latitude, float longitude, uint16_t ex):
			lat(latitude), lng(longitude), extra(ex) {}
	void update(float latitude, float longitude){
		lat = latitude;
		lng = longitude;
	}
	void update(float latitude, float longitude, bool rad){
		if(rad){
			lat = toDeg(latitude);
			lng = toDeg(longitude);
		} else {
			lat = latitude;
			lng = longitude;
		}
	}
	float radLatitude(){
		return toRad(lat);
	}
	float radLongitude(){
		return toRad(lng);
	}
	float degLatitude(){
		return lat;
	}
	float degLongitude(){
		return lng;
	}
#ifndef STAND_ALONE_MATH
	float getAltitude(){
		return ((double)extra)/((double)Protocol::U16_FIXED_FACTOR);
	}
	float getApproachSpeed(){
		return ((double)extra)/((double)Protocol::U16_FIXED_FACTOR);
	}
#endif
	void setExtra(uint16_t alt){
		extra = alt;
	}
	uint16_t getExtra(){
		return extra;
	}
};

#endif