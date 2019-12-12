#include <Leguino.h>


// =================
// ===  Sensors  ===
// =================

// Declare all sensors here (jacks 1 to 6)

// For example:
//Switch * buttonRed;
//Switch * buttonYellow;
//LightSensor * brightness;
//LightBarrier * coinSlot;
//DistanceSensor * distance;
//SingleSensor * voltageProbe;


// ================
// ===  Aktors  ===
// ================

// Declare all actors here (jacks A to E)

// For example:
//Light * frontLight;
//Light * backLight;
//Tread * drive;
//Motor * winch;


// ======================
// ===  Main program  ===
// ======================

void setup() {
	// Start Leguino (either use WAIT_FOR_PLAY or NO_WAIT).
	// This line must always be the first in the setup function.
	leguino.setup(WAIT_FOR_PLAY);
	
	// -----------------------------------------------------------------------
	// Initializations. Add code here for things that should happen once only.
	// -----------------------------------------------------------------------
	
	// Sensoren anlegen und mit Anschluessen verbinden
	//leguino.add(buttonRed = new Switch(IN_1));
	//leguino.add(buttonYellow = new Switch(IN_2));
	//leguino.add(brightness = new LightSensor(IN_3));
	//leguino.add(coinSlot = new LightBarrier(IN_4));
	//leguino.add(distance = new DistanceSensor(IN_5));
	//leguino.add(voltageProbe = new SingleSensor(IN_6));

	// Aktoren anlegen und mit Anschluessen verbinden
	// Achtung: Motoren und Antriebe funktionieren nur an A, B und C
	//leguino.add(drive = new Tread(OUT_A, OUT_B));
	//leguino.add(winch = new Motor(OUT_C));
	//leguino.add(frontLight = new Light(OUT_D));
	//leguino.add(backLight = new Light(OUT_E));

	// Sensoren ggf. einstellen und Aktoren voreinstellen
	//coinSlot->setThresholds(300, 600);
	//frontLight->on();
	//backLight->on();
}

void loop() {
	// Update Leguino.
	// This line must always be the first in the loop function.
	leguino.update();

	// -------------------------------------------
	// Endless loop. Query sensors and set actors.
	// -------------------------------------------
	
	// Example for a switch (query)
	//if (buttonRed->isOn())
	//{
	//...
	//buttonRed->waitOff();
	//}
	
	// Example for a switch (for until turned on)
	//buttonRed->waitOn();
	//...
	//buttonRed->waitOff();

	// Example for a light sensor (query, values are 0 to 1023)
	//if (brightness->getBrightness() < 300)
	//frontLight->on();
	//else
	//frontLight->off();

	// Example for a light sensor (wait until brighter than 500, max. 2 seconds)
	//brightness->waitBrighter(500, 2000);
	//...

	// Example for a light barrier (query)
	//if (coinSlot->isHit())
	//{
	//...
	//coinSlot->waitClear();
	//}
	
	// Example for a light barrier (wait until hit)
	//coinSlot->waitHit();
	//...
	//coinSlot->waitClear();

	// Example for a distance sensor (query cm or mm, values are 20 cm to 200 cm
	// resp. 200 mm to 2000 mm)
	//if (distance->getDistanceCm() < 30)
	//{
	//...
	//}
	
	// Example for a distance sensor (wait for an obstacle to get closer than
	// 95 mm, max. 5 seconds)
	//distance->waitNearerMm(95, 5000);
	//...

	// Example for an arbitrary sensor like pots and probes (raw values)
	// Note: Raw values and voltages work with any sensor
	//uint16 voltage = voltageProbe->getVoltage();

	// Output raw value of an arbitrary sensor on the monitor
	//Serial.print("Value of the light barrier: ");
	//Serial.print(coinSlot->getRawValue());
	//Serial.println();

	// Simple example for light (value 0 to 100)
	//frontLight->on();
	//frontLight->off();
	//frontLight->setValue(50);
	
	// Turn on light for a given time (msecs)
	//frontLight->on(1000);

	// Note: You can use Serial.print or Serial.println for status messages
	//Serial.println("Light gets turned on");
	//frontLight->on();
	
	// Example for motors (values -100 to 100)
	//winch->on();
	//winch->on(1000);
	//winch->off();
	//winch->reverse();
	//winch->reverse(1000);
	//winch->setValue(50);
	//winch->setValue(50, 1000);
	//winch->setValue(-50);
	//winch->setValue(-50, 1000);
	
	// Simple tread examples (thrust from 0 to 100 percent)
	//drive->moveStraight(100);
	//drive->moveLeft(80);
	//drive->moveRight(80);
	//drive->stop();
	//drive->turnAroundLeft(100);
	//drive->turnAroundRight(100);
	
	// Arbitrary tread directions from -100 (turn around left on the spot),
	// over 0 (straight), to 100 (turn around right on the spot).
	//drive->move(-50, 100);

	// Add a duration to the tread move, if desired
	//drive->moveLeft(100, 1000);

	// To simply wait, use Leguino's delay function (keeps background tasks
	// like sequences active).
	//leguino.delay(1000);
}
