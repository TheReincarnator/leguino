#ifndef __LEGUINO_SINGLEACTOR_H
#define __LEGUINO_SINGLEACTOR_H


#define _SWITCHTIME_HIGH_NOTREADY 5
#define _SWITCHTIME_HIGH_READY 50
#define _SWITCHTIME_LOW 1


/**
 * A Leguino actor that requires exactly one output jack (e.g. lights,
 * simple motors).
 *
 * @see Actor
 * @see Light
 * @see Motor
 */
class SingleActor : public Actor
{
	public:

		/**
		 * Creates a new single actor.
		 * @param output The output the actor is connected to.
		 * Use the constants OUT_A thru OUT_E.
		 */
		SingleActor(int8 output);

		/**
		 * Returns the currently set value of the actor, considering instant and
		 * sequence-controlled values.
		 * @return The current value from -100 (full reverse), over 0 (off),
		 * to 100 (full on).
		 */
		uint16 getCurrentValue();

		/**
		 * Returns the currently active sequence of this actor, if any.<br>
		 * See Sequence for more details.
		 * @return The currently active sequence, or NULL, if no sequence is
		 * active (which is usually the case, e.g. for instant values).
		 * @see Sequence
		 */
		Sequence * getSequence();

		/**
		 * Turns off this actor, setting its output to 0, and disabling any
		 * sequence.
		 */
		void off();

		/**
		 * Turns on this actor, setting its output to 100, and disabling any
		 * sequence.
		 */
		void on();

		/**
		 * Turns on this actor for a given period of time, then turns it off.
		 * Also, disables any active sequence.<br>
		 * <b>Note:</b> This method blocks until the delay is over. For
		 * background value control, use sequences instead.
		 * @param msecs The number of milli-seconds before turning off.
		 * @see Sequence
		 */
		void on(uint16 msecs);

		/**
		 * Starts a sequence on this actor. Any previous sequence is
		 * automatically disabled.<br>
		 * See Sequence for more details.
		 * @param sequence The new sequence to set.
		 * @see Sequence
		 */
		void setSequence(Sequence * sequence);

		/**
		 * Sets this actor to a given value and disables any active sequence.
		 * @param value The new value from -100 (full reverse), over 0 (off),
		 * to 100 (full on).
		 */
		void setValue(int8 value);

		/**
		 * Sets this actor to a given value, for a given period of time, then
		 * turns it off. Also, disables any active sequence.<br>
		 * <b>Note:</b> This method blocks until the delay is over. For
		 * background value control, use sequences instead.
		 * @param value The new value from -100 (full reverse), over 0 (off),
		 * to 100 (full on).
		 * @param msecs The number of milli-seconds to hold the new value.
		 * @see Sequence
		 */
		void setValue(int8 value, uint16 msecs);

		/**
		 * Internal Leguino method to update the actor.
		 * Don't call this method from your program.
		 * @param msecs The number of milli-seconds since the last update.
		 */
		virtual void update(uint16 timeStep);

	protected:

		int8 backwardPin;
		int8 currentValue;
		int8 direction;
		int8 forwardPin;
		int8 powerPin;
		int8 requestedValue;
		Sequence * sequence;
		int sequenceStep;
		uint16 sequenceStepDuration;
		uint16 sequenceStepRemaining;
		int8 sequenceStepStartValue;
		int8 sequenceStepEndValue;

		void switchDirection(int8 value);
		void updateOutputPins(uint16 timeStep);
		void updateSequence(uint16 timeStep);
};


#endif
