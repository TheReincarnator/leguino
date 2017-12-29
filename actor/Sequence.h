#ifndef __LEGUINO_SEQUENCE_H
#define __LEGUINO_SEQUENCE_H


/**
 * <p>
 * A sequence of single-actor values (e.g. for motors, lights), which Leguino
 * will activate automatically and in background. Use this for e.g. for
 * flashing lights or any kind of temporary actor activation that requires
 * the main program to continue in the mean time.
 * </p>
 *
 * <p>
 * Use the following code to define and activate a sequence:
 * <code>Sequence * sequence = new Sequence();<br>
 * sequence->addStep(100, 500);<br>
 * sequence->addStep(0, 500);<br>
 * sequence->setRepeat(true);<br>
 * light->setSequence(sequence);</code>
 * </p>
 */
class Sequence
{
	public:

		/**
		 * Creates a new sequence. Use global variables or the new operator for
		 * sequences, to ensure the memory is not freed while active in actors.
		 */
		Sequence();

		/**
		 * Adds a step to the sequence.
		 * @param value The new value from -100 (full reverse), over 0 (off),
		 * to 100 (full on).
		 * @param msecs The number of milli-seconds to hold the value.
		 */
		void addStep(int8 value, uint16 msecs);

		/**
		 * Returns the duration of a given step.
		 * @param step The 0-indexed step number.
		 * @return The number of milli-seconds of the step.
		 */
		uint16 getDuration(int step);

		/**
		 * Returns the value of a given step.
		 * @param step The 0-indexed step number.
		 * @return The value of the step from -100 (full reverse), over 0 (off),
		 * to 100 (full on).
		 */
		int8 getValue(int step);

		/**
		 * Returns the number of steps added to this sequence so far.
		 * @return The number of steps.
		 */
		int getSteps();

		/**
		 * Returns the total duration of all steps.
		 * @return The total duration of all steps.
		 */
		uint16 getTotalDuration();

		/**
		 * Returns whether the transition of the value of one step to the next
		 * should be smooth.
		 * @return Whether the sequence transitions are smooth.
		 */
		bool isSmooth();

		/**
		 * Returns whether the sequence should repeat infinitely.
		 * @return Whether the sequence should repeat.
		 */
		bool isRepeat();

		/**
		 * Sets whether the transition of the value of one step to the next
		 * should be smooth.
		 * @param smooth Whether the sequence transitions are smooth.
		 */
		void setSmooth(bool smooth);

		/**
		 * Sets whether the sequence should repeat infinitely.
		 * Unset the sequence in the actor (or call stop) to stop the repetition.
		 * @param repeat Whether the sequence should repeat.
		 */
		void setRepeat(bool repeat);

	protected:

		ValueList<uint16> durations;
		bool repeat;
		bool smooth;
		ValueList<int8> values;
};


#endif
