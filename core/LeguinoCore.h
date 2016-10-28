#ifndef __LEGUINO_CORE_H
#define __LEGUINO_CORE_H


#define NO_WAIT 0
#define WAIT_FOR_PLAY 1

#define _PIN_PLAY 4
#define _PIN_IR 12
#define _PIN_LED 13


extern LeguinoCore leguino;


class LeguinoCore
{
	friend SingleActor;

	protected:

		ObjectList<Actor *> actors;
		ObjectList<Sensor *> sensors;
		uint32 time;
		class Actor * switchingActor;
		uint16 remainingSwitchTime;

	public:

		LeguinoCore();
		void add(Actor * actor);
		void add(Sensor * sensor);
		void delay(uint16 msecs);
		uint32 getTime();
		void setup(bool waitForPlay);
		void update();
};


#endif
