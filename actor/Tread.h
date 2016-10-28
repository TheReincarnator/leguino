#ifndef __LEGUINO_TREAD_H
#define __LEGUINO_TREAD_H


class Tread : public Actor
{
	protected:

		Motor * left;
		Motor * right;

	public:

		Tread(int8 leftOutput, int8 rightOutput);
		virtual ~Tread();
		uint16 getCurrentLeftValue();
		uint16 getCurrentRightValue();
		void move(int8 direction, int8 thrust);
		void move(int8 direction, int8 thrust, uint16 msecs);
		void moveLeft(int8 thrust);
		void moveLeft(int8 thrust, uint16 msecs);
		void moveRight(int8 thrust);
		void moveRight(int8 thrust, uint16 msecs);
		void moveStraight(int8 thrust);
		void moveStraight(int8 thrust, uint16 msecs);
		void stop();
		void turnAroundLeft(int8 thrust);
		void turnAroundLeft(int8 thrust, uint16 msecs);
		void turnAroundRight(int8 thrust);
		void turnAroundRight(int8 thrust, uint16 msecs);
		virtual void update(uint16 timeStep);
};


#endif
