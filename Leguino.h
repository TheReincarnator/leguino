#ifndef __LEGUINO_H
#define __LEGUINO_H


class Actor;
	class SingleActor;
		class Light;
		class Motor;
	class Tread;

class LeguinoCore;

class Sensor;
	class SingleSensor;
		class Switch;
		class DistanceSensor;
		class LightSensor;
		class LightBarrier;

class Sequence;


#include "Arduino.h"

#include "core/LeguinoList.h"
#include "core/LeguinoPanic.h"
#include "core/LeguinoTypes.h"

#include "core/LeguinoCore.h"

#include "sensor/Sensor.h"
#include "sensor/SingleSensor.h"
#include "sensor/Switch.h"
#include "sensor/DistanceSensor.h"
#include "sensor/LightSensor.h"
#include "sensor/LightBarrier.h"

#include "actor/Sequence.h"

#include "actor/Actor.h"
#include "actor/SingleActor.h"
#include "actor/Light.h"
#include "actor/Motor.h"
#include "actor/Tread.h"


#endif
