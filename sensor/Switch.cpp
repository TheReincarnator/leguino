Switch::Switch(int8 input)
	: SingleSensor(input)
{
	digitalWrite(pin, 1);
}

bool Switch::isOff()
{
	return getRawValue() >= 512;
}

bool Switch::isOn()
{
	return getRawValue() < 512;
}

bool Switch::waitOff(uint16 timeout)
{
	return waitUntilRaw('G', 512, timeout);
}

bool Switch::waitOn(uint16 timeout)
{
	return waitUntilRaw('<', 512, timeout);
}
