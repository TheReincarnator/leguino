#include "LeguinoFlow.h"


Flow::Flow(Board * board, void (*stepFunction)())
{
	this->board = board;
	this->stepFunction = stepFunction;
}

void Flow::goTo(void (*stepFunction)())
{
	this->stepFunction = stepFunction;
}

void Flow::update()
{
	board->update();
	
	if (stepFunction != NULL)
		stepFunction();
}
