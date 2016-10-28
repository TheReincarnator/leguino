Tread::Tread(int8 leftOutput, int8 rightOutput)
{
	left = new Motor(leftOutput);
	right = new Motor(rightOutput);
}

Tread::~Tread()
{
	delete left;
	delete right;
}

uint16 Tread::getCurrentLeftValue()
{
	return left->getCurrentValue();
}

uint16 Tread::getCurrentRightValue()
{
	return right->getCurrentValue();
}

void Tread::move(int8 direction, int8 thrust)
{
	if (direction > 0)
	{
		left->setValue(thrust);
		right->setValue((-thrust * (50 - direction) + 25) / 50);
	}
	else if (direction < 0)
	{
		left->setValue((thrust * (50 + direction) + 25) / 50);
		right->setValue(-thrust);
	}
	else
	{
		left->setValue(thrust);
		right->setValue(-thrust);
	}
}

void Tread::move(int8 direction, int8 thrust, uint16 msecs)
{
	move(direction, thrust);
	leguino.delay(msecs);
	stop();
}

void Tread::moveLeft(int8 thrust)
{
	move(-50, thrust);
}

void Tread::moveLeft(int8 thrust, uint16 msecs)
{
	move(-50, thrust);
	leguino.delay(msecs);
	stop();
}

void Tread::moveRight(int8 thrust)
{
	move(50, thrust);
}

void Tread::moveRight(int8 thrust, uint16 msecs)
{
	move(50, thrust);
	leguino.delay(msecs);
	stop();
}

void Tread::moveStraight(int8 thrust)
{
	move(0, thrust);
}

void Tread::moveStraight(int8 thrust, uint16 msecs)
{
	move(0, thrust);
	leguino.delay(msecs);
	stop();
}

void Tread::stop()
{
	left->off();
	right->off();
}

void Tread::turnAroundLeft(int8 thrust)
{
	move(-100, thrust);
}

void Tread::turnAroundLeft(int8 thrust, uint16 msecs)
{
	move(-100, thrust);
	leguino.delay(msecs);
	stop();
}

void Tread::turnAroundRight(int8 thrust)
{
	move(100, thrust);
}

void Tread::turnAroundRight(int8 thrust, uint16 msecs)
{
	move(100, thrust);
	leguino.delay(msecs);
	stop();
}

void Tread::update(uint16 timeStep)
{
	left->update(timeStep);
	right->update(timeStep);
}
