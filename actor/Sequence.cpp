Sequence::Sequence()
{
	repeat = false;
	smooth = false;
}

void Sequence::addStep(int8 value, uint16 msecs)
{
	values.append(value);
	durations.append(msecs);
}

uint16 Sequence::getDuration(int step)
{
	return durations.get(step);
}

uint16 Sequence::getTotalDuration()
{
	uint16 totalDuration = 0;
	for (int i=0; i<durations.getCount(); i++)
		totalDuration += durations.get(i);
	return totalDuration;
}

int Sequence::getSteps()
{
	return values.getCount();
}

int8 Sequence::getValue(int step)
{
	return values.get(step);
}

bool Sequence::isSmooth()
{
	return smooth;
}

bool Sequence::isRepeat()
{
	return repeat;
}

void Sequence::setSmooth(bool smooth)
{
	this->smooth = smooth;
}

void Sequence::setRepeat(bool repeat)
{
	this->repeat = repeat;
}
