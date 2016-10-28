LightSensor::LightSensor(int8 input)
	: SingleSensor(input)
{
}

int16 LightSensor::getBrightness()
{
	return 1023 - getRawValue();
}

bool LightSensor::waitBrighter(int16 value, uint16 timeout)
{
	return waitUntilRaw('<', 1023 - value, timeout);
}

bool LightSensor::waitDarker(int16 value, uint16 timeout)
{
	return waitUntilRaw('>', 1023 - value, timeout);
}
