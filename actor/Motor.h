#ifndef __LEGUINO_MOTOR_H
#define __LEGUINO_MOTOR_H


class Motor : public SingleActor
{
	public:

		Motor(int8 output);
		void reverse();
		void reverse(uint16 msecs);
};


#endif
