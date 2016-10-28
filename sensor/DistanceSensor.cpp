DistanceSensor::DistanceSensor(int8 input)
	: SingleSensor(input)
{
}

int16 DistanceSensor::getDistanceCm()
{
	return (getDistanceMm() + 5) / 10;
}

int16 DistanceSensor::getDistanceMm()
{
	uint16 rawValue = getRawValue();
	if (rawValue < 30)
		return 2000;
	else
		return (int16) (59334U / rawValue - 30U);
}

bool DistanceSensor::waitFartherCm(int16 cm, uint16 timeout)
{
	return waitUntilMm('>', cm * 10, timeout);
}

bool DistanceSensor::waitFartherMm(int16 mm, uint16 timeout)
{
	return waitUntilMm('>', mm, timeout);
}

bool DistanceSensor::waitNearerCm(int16 cm, uint16 timeout)
{
	return waitUntilMm('<', cm * 10, timeout);
}

bool DistanceSensor::waitNearerMm(int16 mm, uint16 timeout)
{
	return waitUntilMm('<', mm, timeout);
}

bool DistanceSensor::waitUntilMm(char comparator, int16 mm, uint16 timeout)
{
	uint32 start = millis();
	uint32 end = start + timeout;
	uint32 current = millis();
	while (timeout == 0 || current < end && current >= start)
	{
		leguino.delay(20);

		if (comparator == '>' && getDistanceMm() > mm
			|| comparator == '<' && getDistanceMm() < mm)
			return true;
		
		current = millis();
	}
	
	return false;
}
