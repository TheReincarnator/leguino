#include <LeguinoIO.h>


Board * board;


void setup()
{
  board = new Board(Board::TYPE_NANO, false);

  for (int i=0; i<5; i++)
  {
    Sequence * sequence = new Sequence();
    sequence->addStep(100, 500);
    sequence->addStep(0, 500);
    sequence->setRepeat(true);
    sequence->setSmooth(true);
    board->setOutputSequence(i, sequence);
    board->delay(200);
  }
}

void loop()
{    
  board->update();
}

