#ifndef SENSOR_VIRTUAL_H
#define SENSOR_VIRTUAL_H

/*
-Abstract base class for sensors that will be managed by an Inertial Manager
	Instance
-Inheritors of InertialSensor will
	A: handle all hardware communication code
	B: Convert outputs to standard units
	C: Do preliminary sensor filtering based on a sensor's native properties
		eg: low pass filter on gyro to eliminate drift
	D: Pass data into corresponding interface of InerialManager when updated
*/

//forward declare InertialManager
class InertialManager;

class InertialSensor{
protected:
public:
	virtual ~InertialSensor() {};
	virtual void init() = 0;
	virtual void stop() = 0;
	virtual bool status() = 0;
	virtual void calibrate() = 0;
	virtual void update(InertialManager& man) = 0;
};

#endif
