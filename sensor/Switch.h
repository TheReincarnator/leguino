#ifndef __LEGUINO_SWITCH_H
#define __LEGUINO_SWITCH_H


/**
 * A switch sensor (on-off switch, N/O button, N/C button, etc.) connected to
 * a Leguino input and ground (-). Use a pull-up resistor of 10k between the
 * input and VCC (+).
 *
 * @see Sensor
 * @see SingleSensor
 */
class Switch : public SingleSensor
{
	public:

		/**
		 * Creates a new single sensor.
		 * @param input The input the sensor is connected to.
		 * Use the constants IN_1 thru IN_6.
		 */
		Switch(int8 input);

		/**
		 * Returns whether the switch is currently in "off" position.
		 * @return Whether the switch is currently in "off" position.
		 */
		bool isOff();

		/**
		 * Returns whether the switch is currently in "on" position.
		 * @return Whether the switch is currently in "on" position.
		 */
		bool isOn();

		/**
		 * Waits (blocks) until the switch is in "off" position.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitOff(uint16 timeout = 0);

		/**
		 * Waits (blocks) until the switch is in "on" position.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitOn(uint16 timeout = 0);
};


#endif
