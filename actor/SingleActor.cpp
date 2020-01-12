SingleActor::SingleActor(int8 output)
{
	switch (output)
	{
		case OUT_A: powerPin = 3; forwardPin = 2; backwardPin = 7; break;
		case OUT_B: powerPin = 5; forwardPin = 2; backwardPin = 9; break;
		case OUT_C: powerPin = 6; forwardPin = 2; backwardPin = 8; break;
		case OUT_D: powerPin = 10; forwardPin = -1; backwardPin = -1; break;
		case OUT_E: powerPin = 11; forwardPin = -1; backwardPin = -1; break;

		default: powerPin = -1; forwardPin = -1; backwardPin = -1;
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

uint16 SingleActor::getCurrentValue()
{
	return currentValue;
}

Sequence * SingleActor::getSequence()
{
	return sequence;
}

void SingleActor::off()
{
	setValue(0);
}

void SingleActor::on()
{
	setValue(100);
}

void SingleActor::on(uint16 msecs)
{
	on();
	leguino.delay(msecs);
	off();
}

void SingleActor::setSequence(Sequence * sequence)
{
	this->sequence = sequence;
	sequenceStep = -1;
	sequenceStepDuration = 0;
	sequenceStepRemaining = 0;
	sequenceStepStartValue = requestedValue;
	sequenceStepEndValue = requestedValue;
}

void SingleActor::setValue(int8 value)
{
	requestedValue = value;
	sequence = NULL;
}

void SingleActor::setValue(int8 value, uint16 msecs)
{
	setValue(value);
	leguino.delay(msecs);
	off();
}

void SingleActor::switchDirection(int8 value)
{
	int8 offValue = value > 0 ? 1 : 0;
	digitalWrite(2, offValue);
	digitalWrite(7, offValue);
	digitalWrite(9, offValue);
	digitalWrite(8, offValue);

	if (value != 0 && backwardPin >= 0)
		digitalWrite(backwardPin, !offValue);

	if (value > 0) direction = 1;
	if (value < 0) direction = -1;
}

void SingleActor::update(uint16 timeStep)
{
	updateSequence(timeStep);
	updateOutputPins(timeStep);
}

void SingleActor::updateSequence(uint16 timeStep)
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

void SingleActor::updateOutputPins(uint16 timeStep)
{
	if (leguino.switchingActor == this)
	{
		if (leguino.remainingSwitchTime <= timeStep)
		{
			switchDirection(0);
			leguino.switchingActor = NULL;
			leguino.remainingSwitchTime = 0;
		}
		else
		{
			leguino.remainingSwitchTime -= timeStep;
			if (leguino.remainingSwitchTime <= _SWITCHTIME_LOW)
				switchDirection(0);
		}
	}

	if (currentValue == requestedValue)
		return;

	if (forwardPin >= 0 && backwardPin >= 0
		&& (requestedValue > 0 && direction <= 0 || requestedValue < 0 && direction >= 0))
	{
		if (leguino.switchingActor != NULL)
		{
			digitalWrite(powerPin, 0);
			return;
		}

		switchDirection(requestedValue);
		leguino.switchingActor = this;
		leguino.remainingSwitchTime = _SWITCHTIME_LOW
			+ _SWITCHTIME_HIGH_READY + _SWITCHTIME_HIGH_NOTREADY;
	}

	if (leguino.switchingActor == this
		&& leguino.remainingSwitchTime > _SWITCHTIME_LOW + _SWITCHTIME_HIGH_READY)
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
