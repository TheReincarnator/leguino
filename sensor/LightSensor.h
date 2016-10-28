#ifndef __LEGUINO_LIGHTSENSOR_H
#define __LEGUINO_LIGHTSENSOR_H


class LightSensor : public SingleSensor
{
	public:

		LightSensor(int8 input);
		int16 getBrightness();
		bool waitBrighter(int16 value, uint16 timeout = 0);
		bool waitDarker(int16 value, uint16 timeout = 0);
};


#endif
