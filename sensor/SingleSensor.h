#ifndef __LEGUINO_SINGLESENSOR_H
#define __LEGUINO_SINGLESENSOR_H


class SingleSensor : public Sensor
{
	protected:
	
		int8 analogPin;
		int8 pin;
		int16 valueCache;

		bool waitUntilRaw(char comparator, int16 value, uint16 timeout);

	public:
		
		SingleSensor(int8 input);
		uint16 getRawValue();
		virtual void update(uint16 timeStep);
};


#endif
