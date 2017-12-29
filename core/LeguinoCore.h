#ifndef __LEGUINO_CORE_H
#define __LEGUINO_CORE_H


#define NO_WAIT 0
#define WAIT_FOR_PLAY 1

#define _PIN_PLAY 4
#define _PIN_IR 12
#define _PIN_LED 13


extern LeguinoCore leguino;


/**
 * <p>
 * Main Leguino management class. Available as global 'leguino' object.
 * </p>
 *
 * <p>
 * Use this object to initialize Leguino in the program's setup function, and
 * then to add actors or sensors like this:<br>
 * <code>leguino.setup(WAIT_FOR_PLAY);<br>
 * <code>leguino.add(drive = new Motor(OUT_A));<br>
 * leguino.add(frontLight = new Light(OUT_C));</code><br>
 * where <code>drive</code> and <code>frontLight</code> are global variables.
 * </p>
 */
class LeguinoCore
{
	friend SingleActor;

	public:

		/**
		 * Creates the Leguino core.
		 * Don't call this method from your program.
		 */
		LeguinoCore();

		/**
		 * Adds a new actor to Leguino. Call this method in your program's setup
		 * function after calling #setup(). Store the actor in a global variable.
		 */
		void add(Actor * actor);

		/**
		 * Adds a new sensor to Leguino. Call this method in your program's setup
		 * function after calling #setup(). Store the actor in a global variable.
		 */
		void add(Sensor * sensor);

		/**
		 * Pauses the main program for a given time, while still updating
		 * sequences and other time-controlled functions.
		 * @param msecs The number of milli-seconds to pause.
		 */
		void delay(uint16 msecs);

		/**
		 * Returns the number of milli-seconds since starting Leguino.
		 * @return The number of milli-seconds since starting Leguino.
		 */
		uint32 getTime();

		/**
		 * Initializes Leguino. Call this method prior to any other Leguino
		 * method call, in your setup function.
		 * @param waitForPlay Whether the main program loop should wait for the
		 * user pressing the play button. Otherwise, the program starts
		 * instantly. Use WAIT_FOR_PLAY or NO_WAIT.
		 */
		void setup(bool waitForPlay);

		/**
		 * Updates Leguino. Call this method regularly (as first line of your
		 * program's loop function).
		 */
		void update();

	protected:

		ObjectList<Actor *> actors;
		ObjectList<Sensor *> sensors;
		uint32 time;
		class Actor * switchingActor;
		uint16 remainingSwitchTime;
};


#endif
