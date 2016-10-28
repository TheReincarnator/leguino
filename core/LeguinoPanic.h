#ifndef __LIGHT_PANIC_H
#define __LIGHT_PANIC_H


inline void panic()
{
	// Don't use any variables, we don't have any RAM anymore

	digitalWrite(2, 0);
	digitalWrite(3, 0);
	digitalWrite(4, 0);
	digitalWrite(5, 0);
	digitalWrite(6, 0);
	digitalWrite(7, 0);
	digitalWrite(8, 0);
	digitalWrite(9, 0);
	digitalWrite(10, 0);
	digitalWrite(11, 0);
	digitalWrite(12, 0);

	pinMode(13, OUTPUT);
	while (true)
	{
		digitalWrite(13, 1); delay(200); digitalWrite(13, 0); delay(200);
		digitalWrite(13, 1); delay(200); digitalWrite(13, 0); delay(200);
		digitalWrite(13, 1); delay(200); digitalWrite(13, 0); delay(200);

		delay(800);
	}
}


#endif
