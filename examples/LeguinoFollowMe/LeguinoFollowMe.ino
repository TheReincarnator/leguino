#include <LeguinoIO.h>
#include <LeguinoFlow.h>


// Outputs:
//   Tread: A & B
//   Tail: C
//   Head lights: D
//   Back lights: E

// Inputs:
//   Distance sensor: S1


// -------------------
// ---  Variables  ---
// -------------------

Board * board;
Flow * flow;


// ------------------------
// ---  Main functions  ---
// ------------------------

void setup() {
  board = new Board(Board::TYPE_NANO, false);
  board->setInputType(Input::S1, Input::DISTANCE);

  flow = new Flow(board, &sleepState);
}

void loop() {
  flow->update();
}


// ---------------------
// ---  Flow states  ---
// ---------------------

void sleepState() {
  board->waitLess(Input::S1, 150);

  for (int i=0; i<2; i++)
    board->on(Output::D, 100, 500);
  board->on(Output::D);

  board->delay(1000);
  flow->goTo(&foundState);
}

void foundState() {
  board->on(Output::C, 1000);
  flow->goTo(&followState);
}

void followState() {
  uint16 distance = board->getInputValue(Input::S1);
  if (distance < 100) {
    board->on(Output::E);
    board->treadStraight(Output::A, Output::B, 100);
  } else {
    board->off(Output::E);
    if (distance < 200)
      board->treadStop(Output::A, Output::B);
    else if (distance < 450)
      board->treadStraight(Output::A, Output::B, -100);
    else
      flow->goTo(&seekState);
  }

  board->delay(250);
}

void seekState() {
  board->treadStop(Output::A, Output::B);
  if (board->waitLess(Input::S1, 500, 1000)) {
    flow->goTo(&foundState);
    return;
  }

  for (int i=0; i<2; i++)
    board->off(Output::D, 100, 250);
  board->delay(500);

  board->treadTurnAroundLeft(Output::A, Output::B, 100);
  if (waitOrDetectMaster(700))
    return;

  board->treadStop(Output::A, Output::B);
  if (waitOrDetectMaster(1500))
    return;

  board->treadTurnAroundRight(Output::A, Output::B, 100);
  if (waitOrDetectMaster(1400))
    return;

  board->treadStop(Output::A, Output::B);
  if (waitOrDetectMaster(1500))
    return;

  board->treadTurnAroundLeft(Output::A, Output::B, 100);
  if (waitOrDetectMaster(700))
    return;

  board->treadStop(Output::A, Output::B);
  board->delay(1000);

  for (int i=0; i<2; i++)
    board->off(Output::D, 100, 500);
  board->off(Output::D);

  board->delay(1000);
  flow->goTo(&sleepState);
}


// ------------------------
// ---  Helper functions  ---
// ------------------------

bool waitOrDetectMaster(uint16 timeout) {
  if (board->waitLess(Input::S1, 250, timeout)) {
    board->treadStop(Output::A, Output::B);
    for (int i=0; i<2; i++)
      board->off(Output::D, 100, 250);

    board->delay(500);
    flow->goTo(&foundState);

    return true;
  }

  return false;
}

