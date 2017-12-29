#include <Leguino.h>


// ==================
// ===  Sensoren  ===
// ==================

// Deklariere hier alle Sensoren (Anschluesse 1 bis 6)

// Zum Beispiel wie folgt:
//Switch * tasteRot;
//Switch * tasteGelb;
//LightSensor * helligkeit;
//LightBarrier * muenzEinwurf;
//DistanceSensor * entfernung;
//SingleSensor * spannungsMessung;


// =================
// ===  Aktoren  ===
// =================

// Deklariere hier alle Aktoren (LEGO-Technik-Anschluesse A bis E)

// Zum Beispiel wie folgt:
//Light * frontlicht;
//Light * ruecklicht;
//Tread * antrieb;
//Motor * winde;


// =======================
// ===  Hauptprogramm  ===
// =======================

void setup() {
	// Leguino starten (entweder mit WAIT_FOR_PLAY oder NO_WAIT).
	// Diese Zeile muss immer als erstes in dem setup stehen.
	leguino.setup(WAIT_FOR_PLAY);
	
	// -------------------------------------------------------------------------
	// Initialisierungen. Hier das Programmieren, was nur einmal passieren soll.
	// -------------------------------------------------------------------------
	
	// Sensoren anlegen und mit Anschluessen verbinden
	//leguino.add(tasteRot = new Switch(IN_1));
	//leguino.add(tasteGelb = new Switch(IN_2));
	//leguino.add(helligkeit = new LightSensor(IN_3));
	//leguino.add(muenzEinwurf = new LightBarrier(IN_4));
	//leguino.add(entfernung = new DistanceSensor(IN_5));
	//leguino.add(spannungsMessung = new SingleSensor(IN_6));

	// Aktoren anlegen und mit Anschluessen verbinden
	// Achtung: Motoren und Antriebe funktionieren nur an A, B und C
	//leguino.add(antrieb = new Tread(OUT_A, OUT_B));
	//leguino.add(winde = new Motor(OUT_C));
	//leguino.add(frontlicht = new Light(OUT_D));
	//leguino.add(ruecklicht = new Light(OUT_E));

	// Sensoren ggf. einstellen und Aktoren voreinstellen
	//muenzEinwurf->setThresholds(300, 600);
	//frontlicht->on();
	//ruecklicht->on();
}

void loop() {
	// Leguino aktualisieren. Diese Zeile muss immer als erstes in der loop stehen.
	leguino.update();

	// ----------------------------------------------------------
	// Endlosschleife. Hier Sensoren abfragen und Aktoren setzen.
	// ----------------------------------------------------------
	
	// Beispiel für Switch (Abfrage)
	//if (tasteRot->isOn())
	//{
	//...
	//tasteRot->waitOff();
	//}
	
	// Beispiel für Switch (Warten auf Einschalten)
	//tasteRot->waitOn();
	//...
	//tasteRot->waitOff();

	// Beispiel für LightSensor (Abfrage, Werte sind 0 bis 1023)
	//if (helligkeit->getBrightness() < 300)
	//frontlicht->on();
	//else
	//frontlicht->off();

	// Beispiel für LightSensor (Warten auf heller als 500, max. 2 Sekunden)
	//helligkeit->waitBrighter(500, 2000);
	//...

	// Beispiel für LightBarrier (Abfrage)
	//if (muenzEinwurf->isHit())
	//{
	//...
	//muenzEinwurf->waitClear();
	//}
	
	// Beispiel für LightBarrier (Warten auf Unterbrechung)
	//muenzEinwurf->waitHit();
	//...
	//muenzEinwurf->waitClear();

	// Beispiel für DistanceSensor (Abfrage in cm oder mm, Werte 5cm bis 200cm bzw. 50mm bis 2000mm)
	//if (entfernung->getDistanceCm() < 30)
	//{
	//...
	//}
	
	// Beispiel für DistanceSensor (Warten auf nahen Gegenstand <95mm, max. 5 Sekunden)
	//entfernung->waitNearerMm(95, 5000);
	//...

	// Beispiel für einen beliebigen Sensor wie Poti oder Messpunkt (Raw-Werte)
	// Hinweis: Raw-Werte und Spannungen funktionieren bei jedem Sensor
	//uint16 spannung = spannungsMessung->getMilliVolts();

	// Raw-Value bei einem beliebigen Sensor auf dem Monitor ausgeben
	//Serial.print("Wert der Lichtschranke: ");
	//Serial.print(muenzEinwurf->getRawValue());
	//Serial.println();

	// Einfache Beispiele für Light (Werte 0 bis 100)
	//frontlicht->on();
	//frontlicht->off();
	//frontlicht->setValue(50);
	
	// Light nur für bestimmte Zeit einschalten (msecs)
	//frontlicht->on(1000);

	// Hinweis: Serial.print oder Serial.println kann man auch für Status-Meldungen nutzen
	//Serial.println("Licht wird eingeschaltet");
	//frontlicht->on();
	
	// Beispiele für Motor (Werte -100 bis 100)
	//winde->on();
	//winde->on(1000);
	//winde->off();
	//winde->reverse();
	//winde->reverse(1000);
	//winde->setValue(50);
	//winde->setValue(50, 1000);
	//winde->setValue(-50);
	//winde->setValue(-50, 1000);
	
	// Einfache Beispiele für Tread (mit Schub von 0 bis 100 Prozent)
	//antrieb->moveStraight(100);
	//antrieb->moveLeft(80);
	//antrieb->moveRight(80);
	//antrieb->stop();
	//antrieb->turnAroundLeft(100);
	//antrieb->turnAroundRight(100);
	
	// Beliebige Richtungen von -100 (Drehung links), ueber 0 (geradeaus), bis 100 (Drehung rechts)
	//antrieb->move(-50, 100);

	// Alle zusaetzlich auch noch mit Dauer, wenn gewuenscht
	//antrieb->moveLeft(100, 1000);

	// Verwende die Leguino-Delay-Funktion, Wenn du einfach nur mal warten
	// möchtest, damit Hintergrund-Aufgabe wie Sequenzen weiterlaufen.
	//leguino.delay(1000);
}
