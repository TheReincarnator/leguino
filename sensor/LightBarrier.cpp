LightBarrier::LightBarrier(int8 input)
	: SingleSensor(input)
{
	hitThreshold = 600;
	clearThreshold = 300;
	
	hit = false;
}

bool LightBarrier::isClear()
{
	return !isHit();
}

bool LightBarrier::isHit()
{
	int16 rawValue = getRawValue();
	if (hit && rawValue <= clearThreshold) {
		hit = false;
	} else if (!hit && rawValue >= hitThreshold) {
		hit = true;
	}
	
	return hit;
}

void LightBarrier::setThresholds(int16 hitThreshold, int16 clearThreshold)
{
	this->hitThreshold = hitThreshold;
	this->clearThreshold = clearThreshold;
}

bool LightBarrier::waitClear(uint16 timeout)
{
	if (isClear())
		return true;
	
	bool success = waitUntilRaw('L', clearThreshold, timeout);
	if (success)
		hit = false;
	
	return success;
}

bool LightBarrier::waitHit(uint16 timeout)
{
	if (isHit())
		return true;
	
	bool success = waitUntilRaw('G', hitThreshold, timeout);
	if (success)
		hit = true;
	
	return success;
}
