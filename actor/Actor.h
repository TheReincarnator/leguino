#ifndef __LEGUINO_ACTOR_H
#define __LEGUINO_ACTOR_H


#define OUT_A 'A'
#define OUT_B 'B'
#define OUT_C 'C'
#define OUT_D 'D'
#define OUT_E 'E'

#define _SWITCHTIME_HIGH_NOTREADY 5
#define _SWITCHTIME_HIGH_READY 50
#define _SWITCHTIME_LOW 1


class Actor
{
	friend SingleActor;

	protected:

		Actor();

	public:

		virtual ~Actor();
		virtual void update(uint16 timeStep) = NULL;
};


#endif
