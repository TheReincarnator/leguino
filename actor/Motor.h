#ifndef __LEGUINO_MOTOR_H
#define __LEGUINO_MOTOR_H


/**
 * A Leguino single actor representing a LEGO<sup>&copy;</sup> Technic motor.
 *
 * @see Actor
 * @see SingleActor
 */
class Motor : public SingleActor
{
	public:

		/**
		 * Creates a new motor.
		 * @param output The output the motor is connected to.
		 * Use the constants OUT_A thru OUT_E.
		 */
		Motor(int8 output);

		/**
		 * Turns on this actor (motor) in reverse, setting its output to -100,
		 * and disabling any sequence.
		 * @see on()
		 * @see off()
		 */
		void reverse();

		/**
		 * Turns on this actor (motor) in reverse, setting its output to -100,
		 * and disabling any sequence. Waits a given number of milli-seconds,
		 * then turns it off.<br>
		 * <b>Note:</b> This method blocks until the delay is over. For
		 * background value control, use sequences instead.
		 * @param msecs The number of milli-seconds to wait before turning off
		 * the motor.
		 * @see on()
		 * @see off()
		 * @see Sequence
		 */
		void reverse(uint16 msecs);
};


#endif
