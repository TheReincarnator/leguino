#ifndef __LEGUINO_IO_H
#define __LEGUINO_IO_H


#include "Arduino.h"
#include "LeguinoList.h"
#include "LeguinoTypes.h"


//#define DEBUG


#define LEGUINOIO_PLAY 4
#define LEGUINOIO_IR 12
#define LEGUINOIO_LED 13

#define LEGUINOIO_SWITCHTIME_HIGH_NOTREADY 5
#define LEGUINOIO_SWITCHTIME_HIGH_READY 50
#define LEGUINOIO_SWITCHTIME_LOW 1


class Board;
class Input;
class Output;
class Sequence;


class Board
{
	friend class Input;
	friend class Output;

	public:

		Board(char type, bool waitForPlay = true);

		static const char TYPE_UNO;
		static const char TYPE_NANO;

		Input * getInput(int8 no);
		uint16 getInputValue(int8 no);
		Output * getOutput(int8 no);
		inline uint16 getOutputValue(int8 no);
		void delay(uint16 msecs);
		inline uint32 getTime();
		inline void off(int8 no);
		inline void off(int8 no, uint16 msecs);
		inline void off(int8 no, uint16 offMsecs, uint16 delayMsecs);
		inline void on(int8 no);
		inline void on(int8 no, uint16 msecs);
		inline void on(int8 no, uint16 onMsecs, uint16 delayMsecs);
		inline void reverse(int8 no);
		inline void reverse(int8 no, uint16 msecs);
		inline void setInputType(int8 no, char type);
		inline void setOutputValue(int8 no, int8 value);
		inline void setOutputSequence(int8 no, Sequence * sequence);
		void tread(int8 leftNo, int8 rightNo, int8 direction, int8 thrust);
		inline void treadLeft(int8 leftNo, int8 rightNo, int8 thrust);
		inline void treadLeft(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs);
		inline void treadRight(int8 leftNo, int8 rightNo, int8 thrust);
		inline void treadRight(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs);
		inline void treadStop(int8 leftNo, int8 rightNo);
		inline void treadStop(int8 leftNo, int8 rightNo, uint16 msecs);
		inline void treadStraight(int8 leftNo, int8 rightNo, int8 thrust);
		inline void treadStraight(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs);
		inline void treadTurnAroundLeft(int8 leftNo, int8 rightNo, int8 thrust);
		inline void treadTurnAroundLeft(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs);
		inline void treadTurnAroundRight(int8 leftNo, int8 rightNo, int8 thrust);
		inline void treadTurnAroundRight(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs);
		void update();
		inline bool waitEqual(int8 no, int16 value, uint16 timeout);
		inline bool waitGreater(int8 no, int16 value, uint16 timeout);
		inline bool waitGreaterEqual(int8 no, int16 value, uint16 timeout);
		inline bool waitLess(int8 no, int16 value, uint16 timeout);
		inline bool waitLessEqual(int8 no, int16 value, uint16 timeout);
		inline bool waitNotEqual(int8 no, int16 value, uint16 timeout);

	protected:

		ObjectList<Input *> inputs;
		ObjectList<Output *> outputs;
		uint32 time;
		class Output * switchingOutput;
		uint16 remainingSwitchTime;
};

class Input
{
	friend class Board;

	public:

		Input(Board * board, int8 pin);
		inline char getType();
		int16 getValue();
		inline void setType(char type);
		inline bool waitEqual(int16 value, uint16 timeout);
		inline bool waitGreater(int16 value, uint16 timeout);
		inline bool waitGreaterEqual(int16 value, uint16 timeout);
		inline bool waitLess(int16 value, uint16 timeout);
		inline bool waitLessEqual(int16 value, uint16 timeout);
		inline bool waitNotEqual(int16 value, uint16 timeout);
		void update(uint16 timeStep);
		
		static const int8 S1;
		static const int8 S2;
		static const int8 S3;
		static const int8 S4;
		static const int8 S5;
		static const int8 S6;

		static const char RAW;
		static const char DISTANCE;
		static const char SWITCH;

	protected:

		Board * board;
		int8 pin;
		char type;
		int16 valueCache;

		bool waitFor(char comparator, int16 value, uint16 timeout);
};

class Output
{
	friend class Board;

	public:

		Output(Board * board, int8 powerPin, int8 forwardPin = -1, int8 backwardPin = -1);

		static const int8 A;
		static const int8 B;
		static const int8 C;
		static const int8 D;
		static const int8 E;

		inline int8 getBackwardPin();
		inline int8 getCurrentValue();
		inline int8 getForwardPin();
		inline int8 getPowerPin();
		inline Sequence * getSequence();
		inline void off();
		inline void on();
		inline void reverse();
		void setSequence(Sequence * sequence);
		inline void setValue(int8 value);
		void update(uint16 timeStep);
		inline void updateSequence(uint16 timeStep);
		inline void updateOutputPins(uint16 timeStep);

	protected:

		Board * board;

		int8 backwardPin;
		int8 forwardPin;
		int8 powerPin;

		int8 currentValue;
		int8 direction;
		int8 requestedValue;

		Sequence * sequence;
		int sequenceStep;
		uint16 sequenceStepDuration;
		uint16 sequenceStepRemaining;
		int8 sequenceStepStartValue;
		int8 sequenceStepEndValue;

		void switchDirection(int8 value);
};

class Sequence
{
	public:

		Sequence();
		void addStep(int8 value, uint16 duration);

		inline uint16 getDuration(int step);
		inline int8 getValue(int step);
		inline int getSteps();
		uint16 getTotalDuration();
		inline bool isSmooth();
		inline bool isRepeat();
		inline void setSmooth(bool smooth);
		inline void setRepeat(bool repeat);

	protected:

		ValueList<uint16> durations;
		ValueList<int8> values;

		bool smooth;
		bool repeat;
};


inline uint16 Board::getInputValue(int8 no)
{
	Input * input = getInput(no);
	return input != NULL ? input->getValue() : 0;
}

inline uint16 Board::getOutputValue(int8 no)
{
	Output * output = getOutput(no);
	return output != NULL ? output->getCurrentValue() : 0;
}

inline uint32 Board::getTime()
{
	return time;
}

inline void Board::off(int8 no)
{
	Output * output = getOutput(no);
	if (output != NULL)
		output->off();
}

inline void Board::off(int8 no, uint16 msecs)
{
	off(no);
	delay(msecs);
	on(no);
}

inline void Board::off(int8 no, uint16 offMsecs, uint16 delayMsecs)
{
	off(no);
	delay(offMsecs);
	on(no);
	delay(delayMsecs);
}

inline void Board::on(int8 no)
{
	Output * output = getOutput(no);
	if (output != NULL)
		output->on();
}

inline void Board::on(int8 no, uint16 msecs)
{
	on(no);
	delay(msecs);
	off(no);
}

inline void Board::on(int8 no, uint16 onMsecs, uint16 delayMsecs)
{
	on(no);
	delay(onMsecs);
	off(no);
	delay(delayMsecs);
}

inline void Board::reverse(int8 no)
{
	Output * output = getOutput(no);
	if (output != NULL)
		output->reverse();
}

inline void Board::reverse(int8 no, uint16 msecs)
{
	reverse(no);
	delay(msecs);
	off(no);
}

inline void Board::setInputType(int8 no, char type)
{
	Input * input = getInput(no);
	if (input != NULL)
		input->setType(type);
}

inline void Board::setOutputValue(int8 no, int8 value)
{
	Output * output = getOutput(no);
	if (output != NULL)
		output->setValue(value);
}

inline void Board::setOutputSequence(int8 no, Sequence * sequence)
{
	Output * output = getOutput(no);
	if (output != NULL)
		output->setSequence(sequence);
}

inline void Board::treadLeft(int8 leftNo, int8 rightNo, int8 thrust = 100)
{
	tread(leftNo, rightNo, -500, thrust);
}

inline void Board::treadLeft(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs)
{
	treadLeft(leftNo, rightNo, thrust);
	delay(msecs);
	treadStop(leftNo, rightNo);
}

inline void Board::treadRight(int8 leftNo, int8 rightNo, int8 thrust = 100)
{
	tread(leftNo, rightNo, 50, thrust);
}

inline void Board::treadRight(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs)
{
	treadRight(leftNo, rightNo, thrust);
	delay(msecs);
	treadStop(leftNo, rightNo);
}

inline void Board::treadStop(int8 leftNo, int8 rightNo)
{
	tread(leftNo, rightNo, 0, 0);
}

inline void Board::treadStraight(int8 leftNo, int8 rightNo, int8 thrust = 100)
{
	tread(leftNo, rightNo, 0, thrust);
}

inline void Board::treadStraight(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs)
{
	treadStraight(leftNo, rightNo, thrust);
	delay(msecs);
	treadStop(leftNo, rightNo);
}

inline void Board::treadTurnAroundLeft(int8 leftNo, int8 rightNo, int8 thrust = 100)
{
	tread(leftNo, rightNo, -100, thrust);
}

inline void Board::treadTurnAroundLeft(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs)
{
	treadTurnAroundLeft(leftNo, rightNo, thrust);
	delay(msecs);
	treadStop(leftNo, rightNo);
}

inline void Board::treadTurnAroundRight(int8 leftNo, int8 rightNo, int8 thrust = 100)
{
	tread(leftNo, rightNo, 100, thrust);
}

inline void Board::treadTurnAroundRight(int8 leftNo, int8 rightNo, int8 thrust, uint16 msecs)
{
	treadTurnAroundRight(leftNo, rightNo, thrust);
	delay(msecs);
	treadStop(leftNo, rightNo);
}

inline bool Board::waitEqual(int8 no, int16 value, uint16 timeout = 0)
{
	return getInput(no)->waitEqual(value, timeout);
}

inline bool Board::waitGreater(int8 no, int16 value, uint16 timeout = 0)
{
	return getInput(no)->waitGreater(value, timeout);
}

inline bool Board::waitGreaterEqual(int8 no, int16 value, uint16 timeout = 0)
{
	return getInput(no)->waitGreaterEqual(value, timeout);
}

inline bool Board::waitLess(int8 no, int16 value, uint16 timeout = 0)
{
	return getInput(no)->waitLess(value, timeout);
}

inline bool Board::waitLessEqual(int8 no, int16 value, uint16 timeout = 0)
{
	return getInput(no)->waitLessEqual(value, timeout);
}

inline bool Board::waitNotEqual(int8 no, int16 value, uint16 timeout = 0)
{
	return getInput(no)->waitNotEqual(value, timeout);
}


inline char Input::getType()
{
	return type;
}

inline void Input::setType(char type)
{
	this->type = type;
}

inline bool Input::waitEqual(int16 value, uint16 timeout = 0)
{
	return waitFor('=', value, timeout);
}

inline bool Input::waitGreater(int16 value, uint16 timeout = 0)
{
	return waitFor('>', value, timeout);
}

inline bool Input::waitGreaterEqual(int16 value, uint16 timeout = 0)
{
	return waitFor('G', value, timeout);
}

inline bool Input::waitLess(int16 value, uint16 timeout = 0)
{
	return waitFor('<', value, timeout);
}

inline bool Input::waitLessEqual(int16 value, uint16 timeout = 0)
{
	return waitFor('L', value, timeout);
}

inline bool Input::waitNotEqual(int16 value, uint16 timeout = 0)
{
	return waitFor('!', value, timeout);
}


inline int8 Output::getBackwardPin()
{
	return backwardPin;
}

inline int8 Output::getCurrentValue()
{
	return currentValue;
}

inline int8 Output::getForwardPin()
{
	return forwardPin;
}

inline int8 Output::getPowerPin()
{
	return powerPin;
}

inline Sequence * Output::getSequence()
{
	return sequence;
}

inline void Output::off()
{
	setValue(0);
}

inline void Output::on()
{
	setValue(100);
}

inline void Output::reverse()
{
	setValue(-100);
}

inline void Output::setValue(int8 value)
{
	requestedValue = value;
	sequence = NULL;

	#ifdef DEBUG
		char buffer[64];
		sprintf(buffer, "Setting output (%d,%d,%d) to %d\n", powerPin, forwardPin, backwardPin, value);
		Serial.print(buffer);
	#endif
}

inline void Output::updateSequence(uint16 timeStep)
{
	if (sequence == NULL)
		return;

	while (true)
	{
		if (sequenceStepRemaining <= timeStep)
		{

			timeStep -= sequenceStepRemaining;
			sequenceStepStartValue = sequenceStep < 0 ? requestedValue : sequence->getValue(sequenceStep);
			sequenceStep++;

			if (sequenceStep >= sequence->getSteps())
			{
				if (sequence->isRepeat() && sequence->getSteps() > 0)
				{
					sequenceStep = 0;
				}
				else
				{
					sequence = NULL;
					break;
				}
			}

			sequenceStepEndValue = sequence->getValue(sequenceStep);
			if (!sequence->isSmooth())
				requestedValue = sequenceStepEndValue;
			sequenceStepDuration = sequence->getDuration(sequenceStep);
			sequenceStepRemaining = sequenceStepDuration;
		}
		else
		{
			sequenceStepRemaining -= timeStep;
			break;
		}
	}

	if (sequence == NULL)
		return;

	if (sequence->isSmooth() && sequenceStepDuration > 0)
	{
		requestedValue = (int8)
			(
				((long) sequenceStepEndValue)
				-
				(
					((long) sequenceStepEndValue - sequenceStepStartValue)
					* sequenceStepRemaining
					+ (sequenceStepDuration / 2)
				)
				/ sequenceStepDuration
			);
	}
}

inline void Output::updateOutputPins(uint16 timeStep)
{
	if (board->switchingOutput == this)
	{
		if (board->remainingSwitchTime <= timeStep)
		{
			switchDirection(0);
			board->switchingOutput = NULL;
			board->remainingSwitchTime = 0;
		}
		else
		{
			board->remainingSwitchTime -= timeStep;
			if (board->remainingSwitchTime <= LEGUINOIO_SWITCHTIME_LOW)
				switchDirection(0);
		}
	}

	if (currentValue == requestedValue)
		return;

	if (forwardPin >= 0 && backwardPin >= 0
		&& (requestedValue > 0 && direction <= 0 || requestedValue < 0 && direction >= 0))
	{
		if (board->switchingOutput != NULL)
		{
			digitalWrite(powerPin, 0);
			return;
		}

		switchDirection(requestedValue);
		board->switchingOutput = this;
		board->remainingSwitchTime = LEGUINOIO_SWITCHTIME_LOW
			+ LEGUINOIO_SWITCHTIME_HIGH_READY + LEGUINOIO_SWITCHTIME_HIGH_NOTREADY;
	}

	if (board->switchingOutput == this
		&& board->remainingSwitchTime > LEGUINOIO_SWITCHTIME_LOW + LEGUINOIO_SWITCHTIME_HIGH_READY)
		return;

	currentValue = requestedValue;

	if (powerPin >= 0)
	{
		int8 absoluteValue = currentValue < 0 ? -currentValue : currentValue;

		if (absoluteValue <= 0)
			digitalWrite(powerPin, 0);
		else if (absoluteValue >= 100)
			digitalWrite(powerPin, 1);
		else
			analogWrite(powerPin, (absoluteValue * 255 + 128) / 100);
	}
}


inline uint16 Sequence::getDuration(int step)
{
	return durations.get(step);
}

inline int8 Sequence::getValue(int step)
{
	return values.get(step);
}

inline int Sequence::getSteps()
{
	return values.getCount();
}

inline bool Sequence::isSmooth()
{
	return smooth;
}

inline bool Sequence::isRepeat()
{
	return repeat;
}

inline void Sequence::setSmooth(bool smooth)
{
	this->smooth = smooth;
}

inline void Sequence::setRepeat(bool repeat)
{
	this->repeat = repeat;
}


#endif
