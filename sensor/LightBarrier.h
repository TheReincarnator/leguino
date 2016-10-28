#ifndef __LEGUINO_LIGHTBARRIER_H
#define __LEGUINO_LIGHTBARRIER_H


class LightBarrier : public SingleSensor
{
	protected:
		
		int16 clearThreshold;
		bool hit;
		int16 hitThreshold;

	public:

		LightBarrier(int8 input);
		bool isClear();
		bool isHit();
		void setThresholds(int16 hitThreshold, int16 clearThreshold);
		bool waitClear(uint16 timeout = 0);
		bool waitHit(uint16 timeout = 0);
};


#endif
