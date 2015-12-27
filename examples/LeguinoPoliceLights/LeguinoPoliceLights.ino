#include <LeguinoIO.h>


Board * board;


void setup()
{
  board = new Board(Board::TYPE_NANO, false);

  // US police lights: ----X-XXXX-X----X-X-X-X-X----
  Sequence * sequence = new Sequence();
  sequence->addStep(0, 400);
  sequence->addStep(-100, 40);
  sequence->addStep(0, 40);
  sequence->addStep(-100, 500);
  sequence->addStep(0, 40);
  sequence->addStep(-100, 40);
  sequence->addStep(0, 400);
  for (int i=0; i<4; i++) {
    sequence->addStep(-100, 40);
    sequence->addStep(0, 40);
  }
  sequence->setRepeat(true);

  // Put on A and B directly
  board->setOutputSequence(Output::A, sequence);
  board->setOutputSequence(Output::B, sequence);

  // Put on D and E with a delay
  board->delay(200);
  board->setOutputSequence(Output::D, sequence);
  board->setOutputSequence(Output::E, sequence);
}

void loop()
{    
  board->update();
}

