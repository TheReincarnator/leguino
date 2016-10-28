#ifndef __LEGUINO_DISTANCESENSOR_H
#define __LEGUINO_DISTANCESENSOR_H


class DistanceSensor : public SingleSensor
{
	protected:
		
		bool waitUntilMm(char comparator, int16 mm, uint16 timeout = 0);

	public:

		DistanceSensor(int8 input);
		int16 getDistanceCm();
		int16 getDistanceMm();
		bool waitFartherCm(int16 cm, uint16 timeout = 0);
		bool waitFartherMm(int16 mm, uint16 timeout = 0);
		bool waitNearerCm(int16 cm, uint16 timeout = 0);
		bool waitNearerMm(int16 mm, uint16 timeout = 0);
};


#endif
