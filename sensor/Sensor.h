#ifndef __LEGUINO_SENSOR_H
#define __LEGUINO_SENSOR_H


#define IN_1 1
#define IN_2 2
#define IN_3 3
#define IN_4 4
#define IN_5 5
#define IN_6 6


class Sensor
{
	protected:

		Sensor();

	public:

		virtual ~Sensor();
		virtual void update(uint16 timeStep) = NULL;
};


#endif
