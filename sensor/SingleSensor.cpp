SingleSensor::SingleSensor(int8 input)
{
	switch (input)
	{
		case IN_1: pin = A2; analogPin = 2; break;
		case IN_2: pin = A3; analogPin = 3; break;
		case IN_3: pin = A4; analogPin = 4; break;
		case IN_4: pin = A5; analogPin = 5; break;
		case IN_5: pin = A6; analogPin = 6; break;
		case IN_6: pin = A7; analogPin = 7; break;
	
		default: pin = -1; analogPin = -1;
	}

	pinMode(pin, INPUT);
	digitalWrite(pin, 0);

	valueCache = -1;
}

uint16 SingleSensor::getRawValue()
{	
	if (valueCache < 0)
		valueCache = (int16) analogRead(analogPin);
	
	return valueCache;
}

void SingleSensor::update(uint16 timeStep)
{
	valueCache = -1;
}

bool SingleSensor::waitUntilRaw(char comparator, int16 value, uint16 timeout)
{
	uint32 start = millis();
	uint32 end = start + timeout;
	uint32 current = millis();
	while (timeout == 0 || current < end && current >= start)
	{
		leguino.delay(20);

		if (comparator == '=' && getRawValue() == value
			|| comparator == '>' && getRawValue() > value
			|| comparator == 'G' && getRawValue() >= value
			|| comparator == '<' && getRawValue() < value
			|| comparator == 'L' && getRawValue() <= value
			|| comparator == '!' && getRawValue() != value)
			return true;
		
		current = millis();
	}
	
	return false;
}
