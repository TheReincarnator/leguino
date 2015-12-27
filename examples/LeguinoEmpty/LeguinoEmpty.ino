#include <LeguinoIO.h>


// Outputs:
//   Example tread: A & B
//   Example motor: C
//   Example light: D

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
  board = new Board(Board::TYPE_NANO, false);
  board->setInputType(Input::S1, Input::DISTANCE);
}

void loop() {
  board->update();

  //board->on(Output::A);
}
