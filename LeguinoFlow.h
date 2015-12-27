#ifndef __LEGUINO_FLOW_H
#define __LEGUINO_FLOW_H


#include "Arduino.h"
#include "LeguinoIO.h"


class Flow
{
	public:
		
		Flow(Board * board, void (*stepFunction)());
		void goTo(void (*stepFunction)());
		void update();
	
	protected:

		Board * board;
		void (*stepFunction)();
};


#endif
