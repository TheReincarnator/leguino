#include "LeguinoIO.h"


const char Board::TYPE_UNO = 'u';
const char Board::TYPE_NANO = 'n';

Board::Board(char type, bool waitForPlay)
{
	#ifdef DEBUG
		Serial.begin(9600);
	#endif

	Output * output;
	if ((output = new Output(this, 3, 2, 7)) == NULL)
		panic();
	outputs.append(output);
	if ((output = new Output(this, 5, 2, 9)) == NULL)
		panic();
	outputs.append(output);
	if ((output = new Output(this, 6, 2, 8)) == NULL)
		panic();
	outputs.append(output);
	if ((output = new Output(this, 10)) == NULL)
		panic();
	outputs.append(output);
	if ((output = new Output(this, 11)) == NULL)
		panic();
	outputs.append(output);

	Input * input;
	if ((input = new Input(this, type == TYPE_NANO ? 2 : 0)) == NULL)
		panic();
	inputs.append(input);
	if ((input = new Input(this, type == TYPE_NANO ? 3 : 1)) == NULL)
		panic();
	inputs.append(input);
	if ((input = new Input(this, type == TYPE_NANO ? 4 : 2)) == NULL)
		panic();
	inputs.append(input);
	if ((input = new Input(this, type == TYPE_NANO ? 5 : 3)) == NULL)
		panic();
	inputs.append(input);
	if ((input = new Input(this, type == TYPE_NANO ? 6 : 4)) == NULL)
		panic();
	inputs.append(input);
	if ((input = new Input(this, type == TYPE_NANO ? 7 : 5)) == NULL)
		panic();
	inputs.append(input);

	switchingOutput = NULL;
	remainingSwitchTime = 0;

	time = millis();
	
	pinMode(LEGUINOIO_PLAY, INPUT);
	pinMode(LEGUINOIO_LED, OUTPUT);
	digitalWrite(LEGUINOIO_PLAY, 1);

	delay(250);

	if (waitForPlay)
	{
		bool playPressed = false;
		while (!playPressed)
		{
			uint32 start = millis();
			digitalWrite(LEGUINOIO_LED, HIGH);
			while (millis() < start + 50)
				if (digitalRead(LEGUINOIO_PLAY) == LOW)
				{
					playPressed = true;
					break;
				}
	
			start = millis();
			digitalWrite(LEGUINOIO_LED, LOW);
			while (millis() < start + 950)
				if (digitalRead(LEGUINOIO_PLAY) == LOW)
				{
					playPressed = true;
					break;
				}
		}
		digitalWrite(LEGUINOIO_LED, LOW);
	
		while (digitalRead(LEGUINOIO_PLAY) == LOW);
		delay(1000);
	}
}

Input * Board::getInput(int8 no)
{
	return inputs.get(no);
}

Output * Board::getOutput(int8 no)
{
	return outputs.get(no);
}

void Board::delay(uint16 msecs)
{
	uint32 start = millis();
	uint32 end = start + msecs;
	uint32 current = millis();
	while (current < end && current >= start)
	{
		update();
		current = millis();
	}
}

void Board::tread(int8 leftNo, int8 rightNo, int8 direction, int8 thrust)
{
	Output * leftOutput = getOutput(leftNo);
	Output * rightOutput = getOutput(rightNo);

	if (direction > 0)
	{
		leftOutput->setValue(thrust);
		rightOutput->setValue((-thrust * (50 - direction) + 25) / 50);
	}
	else if (direction < 0)
	{
		leftOutput->setValue((thrust * (50 + direction) + 25) / 50);
		rightOutput->setValue(-thrust);
	}
	else
	{
		leftOutput->setValue(thrust);
		rightOutput->setValue(-thrust);
	}
}

void Board::update()
{
	uint32 currentTime = millis();
	if (currentTime < time)
		time = currentTime;

	uint16 timeStep = currentTime < time ? 0 : (uint16) (currentTime - time);
	time = currentTime;

	if (timeStep <= 0)
		return;

	for (int i=0; i<outputs.getCount(); i++)
		outputs.get(i)->update(timeStep);
	for (int i=0; i<inputs.getCount(); i++)
		inputs.get(i)->update(timeStep);
}


const int8 Input::S1 = 0;
const int8 Input::S2 = 1;
const int8 Input::S3 = 2;
const int8 Input::S4 = 3;
const int8 Input::S5 = 4;
const int8 Input::S6 = 5;

const char Input::RAW = 0;
const char Input::DISTANCE = 'd';
const char Input::SWITCH = 's';

Input::Input(Board * board, int8 pin)
{
	this->board = board;
	this->pin = pin;
	type = RAW;
	valueCache = 0;
}

int16 Input::getValue()
{
	if (valueCache < 0)
	{
		switch (type)
		{
			case SWITCH: valueCache = analogRead(pin) >= 512; break;

			case DISTANCE:
			{
				uint16 rawValue = analogRead(pin);
				if (rawValue < 30)
					valueCache = 2000;
				else
					valueCache = (int16) (59334U / rawValue - 30U);
			}
			break;

			default: valueCache = (int16) analogRead(pin);
		}
	}

	return valueCache;
}


bool Input::waitFor(char comparator, int16 value, uint16 timeout = 0)
{
	uint32 start = millis();
	uint32 end = start + timeout;
	uint32 current = millis();
	while (timeout == 0 || current < end && current >= start)
	{
		board->delay(20);

		if (comparator == '=' && getValue() == value
			|| comparator == '>' && getValue() > value
			|| comparator == 'G' && getValue() >= value
			|| comparator == '<' && getValue() < value
			|| comparator == 'L' && getValue() <= value
			|| comparator == '!' && getValue() != value)
			return true;
		
		current = millis();
	}
	
	return false;
}

void Input::update(uint16 timeStep)
{
	valueCache = -1;
}


const int8 Output::A = 0;
const int8 Output::B = 1;
const int8 Output::C = 2;
const int8 Output::D = 3;
const int8 Output::E = 4;

Output::Output(Board * board, int8 powerPin, int8 forwardPin, int8 backwardPin)
{
	this->board = board;

	this->powerPin = powerPin;
	this->forwardPin = forwardPin;
	this->backwardPin = backwardPin;

	if (powerPin >= 0)
	{
		pinMode(powerPin, OUTPUT);
		digitalWrite(powerPin, 0);
	}

	if (forwardPin >= 0)
	{
		pinMode(forwardPin, OUTPUT);
		digitalWrite(forwardPin, 0);
	}

	if (backwardPin >= 0)
	{
		pinMode(backwardPin, OUTPUT);
		digitalWrite(backwardPin, 0);
	}

	currentValue = 0;
	direction = 0;
	requestedValue = 0;
	sequence = NULL;
	sequenceStep = -1;
	sequenceStepDuration = 0;
	sequenceStepRemaining = 0;
	sequenceStepStartValue = 0;
	sequenceStepEndValue = 0;
}

void Output::setSequence(Sequence * sequence)
{
	this->sequence = sequence;
	sequenceStep = -1;
	sequenceStepDuration = 0;
	sequenceStepRemaining = 0;
	sequenceStepStartValue = requestedValue;
	sequenceStepEndValue = requestedValue;
}

void Output::switchDirection(int8 value)
{
	int8 offValue = value > 0 ? 1 : 0;
	for (int i=0; i<board->outputs.getCount(); i++)
	{
		Output * otherOutput = board->outputs.get(i);
		int8 otherForwardPin = otherOutput->forwardPin;
		int8 otherBackwardPin = otherOutput->backwardPin;
		if (otherForwardPin >= 0 && otherBackwardPin >= 0)
		{
			digitalWrite(otherForwardPin, offValue);
			digitalWrite(otherBackwardPin, offValue);
		}
	}

	if (value != 0 && backwardPin >= 0)
		digitalWrite(backwardPin, !offValue);

	if (value > 0) direction = 1;
	if (value < 0) direction = -1;
}

void Output::update(uint16 timeStep)
{
	updateSequence(timeStep);
	updateOutputPins(timeStep);
}


Sequence::Sequence()
{
	repeat = false;
	smooth = false;
}

void Sequence::addStep(int8 value, uint16 duration)
{
	values.append(value);
	durations.append(duration);
}

uint16 Sequence::getTotalDuration()
{
	uint16 totalDuration = 0;
	for (int i=0; i<durations.getCount(); i++)
		totalDuration += durations.get(i);
	return totalDuration;
}
