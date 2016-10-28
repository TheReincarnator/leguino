#ifndef __LEGUINO_SWITCH_H
#define __LEGUINO_SWITCH_H


class Switch : public SingleSensor
{
	public:

		Switch(int8 input);
		bool isOff();
		bool isOn();
		bool waitOff(uint16 timeout = 0);
		bool waitOn(uint16 timeout = 0);
};


#endif
