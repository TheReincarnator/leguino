LeguinoCore leguino;

LeguinoCore::LeguinoCore()
{
	switchingActor = NULL;
	remainingSwitchTime = 0;
	time = 0;
}

void LeguinoCore::add(Actor * actor)
{
	actors.append(actor);
}

void LeguinoCore::add(Sensor * sensor)
{
	sensors.append(sensor);
}

void LeguinoCore::delay(uint16 msecs)
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

uint32 LeguinoCore::getTime()
{
	return time;
}

void LeguinoCore::setup(bool waitForPlay)
{
	Serial.begin(9600);

	time = millis();
	
	pinMode(_PIN_PLAY, INPUT);
	pinMode(_PIN_LED, OUTPUT);
	digitalWrite(_PIN_PLAY, 1);
	
	int8 pin;
	pin = 3; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 5; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 6; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 10; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 11; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 2; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 7; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 9; pinMode(pin, OUTPUT); digitalWrite(pin, 0);
	pin = 8; pinMode(pin, OUTPUT); digitalWrite(pin, 0);

	::delay(250);
	
	if (!waitForPlay)
		return;
	
	bool playPressed = false;
	while (!playPressed)
	{
		uint32 start = millis();
		digitalWrite(_PIN_LED, HIGH);
		while (millis() < start + 50)
			if (digitalRead(_PIN_PLAY) == LOW)
			{
				playPressed = true;
				break;
			}

		start = millis();
		digitalWrite(_PIN_LED, LOW);
		while (millis() < start + 950)
			if (digitalRead(_PIN_PLAY) == LOW)
			{
				playPressed = true;
				break;
			}
	}
	digitalWrite(_PIN_LED, LOW);

	while (digitalRead(_PIN_PLAY) == LOW);
	::delay(1000);
}

void LeguinoCore::update()
{
	uint32 currentTime = millis();
	if (currentTime < time)
		time = currentTime;

	uint16 timeStep = currentTime < time ? 0 : (uint16) (currentTime - time);
	time = currentTime;

	if (timeStep <= 0)
		return;

	for (int i=0; i<actors.getCount(); i++)
		actors.get(i)->update(timeStep);
	for (int i=0; i<sensors.getCount(); i++)
		sensors.get(i)->update(timeStep);
}
