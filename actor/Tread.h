#ifndef __LEGUINO_TREAD_H
#define __LEGUINO_TREAD_H


/**
 * A double-motor tread connected to two Leguino outputs.
 * Note that one motor must be attached reverse to the other.
 *
 * @see Actor
 */
class Tread : public Actor
{
	public:

		/**
		 * Creates a new tread.
		 * @param leftOutput The output the left motor is connected to.
		 * Use the constants OUT_A thru OUT_E.
		 * @param rightOutput The output the right motor is connected to.
		 * Use the constants OUT_A thru OUT_E.
		 */
		Tread(int8 leftOutput, int8 rightOutput);

		/**
		 * Destroys the tread.
		 * Don't call this method from your program.
		 */
		virtual ~Tread();

		/**
		 * Returns the currently set value of the left motor, considering instant
		 * and sequence-controlled values.
		 * @return The current value from -100 (full reverse), over 0 (off),
		 * to 100 (full on).
		 */
		uint16 getCurrentLeftValue();

		/**
		 * Returns the currently set value of the right motor, considering instant
		 * and sequence-controlled values.
		 * @return The current value from -100 (full reverse), over 0 (off),
		 * to 100 (full on).
		 */
		uint16 getCurrentRightValue();

		/**
		 * Sets the values of both motors so that the tread it moving towards
		 * a given direction, using a given thrust.
		 * @param direction The direction of the tread, from -100 (turn around
		 * left at the spot), over -50 (left-turn), 0 (straight),
		 * 50 (right-turn), to 100 (turn around right at the spot), and any
		 * value in between.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 */
		void move(int8 direction, int8 thrust);

		/**
		 * Sets the values of both motors so that the tread it moving towards
		 * a given direction, using a given thrust. Then, after a given time,
		 * stops the tread.<br>
		 * <b>Note:</b> This method blocks until the delay is over.
		 * @param direction The direction of the tread, from -100 (turn around
		 * left at the spot), over -50 (left-turn), 0 (straight),
		 * 50 (right-turn), to 100 (turn around right at the spot), and any
		 * value in between.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 * @param msecs The number of milli-seconds to drive before stopping.
		 */
		void move(int8 direction, int8 thrust, uint16 msecs);

		/**
		 * Sets the values of both motors so that the tread it turning left
		 * (while still moving), using a given thrust.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 */
		void moveLeft(int8 thrust);

		/**
		 * Sets the values of both motors so that the tread it turning left
		 * (while still moving), using a given thrust.<br>
		 * <b>Note:</b> This method blocks until the delay is over.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 * @param msecs The number of milli-seconds to drive before stopping.
		 */
		void moveLeft(int8 thrust, uint16 msecs);

		/**
		 * Sets the values of both motors so that the tread it turning right
		 * (while still moving), using a given thrust.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 */
		void moveRight(int8 thrust);

		/**
		 * Sets the values of both motors so that the tread it turning right
		 * (while still moving), using a given thrust.<br>
		 * <b>Note:</b> This method blocks until the delay is over.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 * @param msecs The number of milli-seconds to drive before stopping.
		 */
		void moveRight(int8 thrust, uint16 msecs);

		/**
		 * Sets the values of both motors so that the tread it turning straight,
		 * using a given thrust.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 */
		void moveStraight(int8 thrust);

		/**
		 * Sets the values of both motors so that the tread it turning straight,
		 * using a given thrust.<br>
		 * <b>Note:</b> This method blocks until the delay is over.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 * @param msecs The number of milli-seconds to drive before stopping.
		 */
		void moveStraight(int8 thrust, uint16 msecs);

		/**
		 * Stops both motors of the tread.
		 */
		void stop();

		/**
		 * Sets the values of both motors so that the tread it turning around
		 * left at the spot, using a given thrust.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 */
		void turnAroundLeft(int8 thrust);

		/**
		 * Sets the values of both motors so that the tread it turning around
		 * left at the spot, using a given thrust.<br>
		 * <b>Note:</b> This method blocks until the delay is over.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 * @param msecs The number of milli-seconds to drive before stopping.
		 */
		void turnAroundLeft(int8 thrust, uint16 msecs);

		/**
		 * Sets the values of both motors so that the tread it turning around
		 * right at the spot, using a given thrust.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 */
		void turnAroundRight(int8 thrust);

		/**
		 * Sets the values of both motors so that the tread it turning around
		 * right at the spot, using a given thrust.<br>
		 * <b>Note:</b> This method blocks until the delay is over.
		 * @param thrust Any value from 0 (stop) to 100 (full thrust).
		 * @param msecs The number of milli-seconds to drive before stopping.
		 */
		void turnAroundRight(int8 thrust, uint16 msecs);

		/**
		 * Internal Leguino method to update the actor.
		 * Don't call this method from your program.
		 * @param msecs The number of milli-seconds since the last update.
		 */
		virtual void update(uint16 timeStep);

	protected:

		Motor * left;
		Motor * right;
};


#endif
