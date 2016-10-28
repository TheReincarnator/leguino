Motor::Motor(int8 output)
	: SingleActor(output)
{
}

void Motor::reverse()
{
	setValue(-100);
}

void Motor::reverse(uint16 msecs)
{
	reverse();
	leguino.delay(msecs);
	off();
}
