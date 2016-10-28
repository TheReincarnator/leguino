#ifndef __LEGUINO_SEQUENCE_H
#define __LEGUINO_SEQUENCE_H


class Sequence
{
	public:

		Sequence();
		void addStep(int8 value, uint16 msecs);

		uint16 getDuration(int step);
		int8 getValue(int step);
		int getSteps();
		uint16 getTotalDuration();
		bool isSmooth();
		bool isRepeat();
		void setSmooth(bool smooth);
		void setRepeat(bool repeat);

	protected:

		ValueList<uint16> durations;
		bool repeat;
		bool smooth;
		ValueList<int8> values;
};


#endif
