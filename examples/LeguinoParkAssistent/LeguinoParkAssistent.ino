#include <LeguinoIO.h>


// Outputs:
//   Light: A

// Inputs:
//   Distance sensor: S1


// -------------------
// ---  Variables  ---
// -------------------

Board * board;


// ------------------------
// ---  Main functions  ---
// ------------------------

void setup() {
  board = new Board(Board::TYPE_NANO);
  board->setInputType(Input::S1, Input::DISTANCE);
}

void loop() {
  board->update();

  uint16 distance = board->getInputValue(Input::S1);
  if (distance < 500) {
    board->on(Output::A, distance);
    board->reverse(Output::A, distance);
  }
}

