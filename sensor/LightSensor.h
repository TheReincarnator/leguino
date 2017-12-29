#ifndef __LEGUINO_LIGHTSENSOR_H
#define __LEGUINO_LIGHTSENSOR_H


/**
 * A light sensor (photo resistor or photo diode) connected to a Leguino input
 * and ground (-). Use a pull-up resistor of 10k between the input and VCC (+).
 *
 * @see Sensor
 * @see SingleSensor
 */
class LightSensor : public SingleSensor
{
	public:

		/**
		 * Creates a new light sensor.
		 * @param input The input the sensor is connected to.
		 * Use the constants IN_1 thru IN_6.
		 */
		LightSensor(int8 input);

		/**
		 * Returns the current brightness.
		 * @return The current brightness from 0 (dark) to 1023 (light).
		 */
		int16 getBrightness();

		/**
		 * Waits (blocks) until the light is brighter than a given value.
		 * @param value The threshold value.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitBrighter(int16 value, uint16 timeout = 0);

		/**
		 * Waits (blocks) until the light is darker than a given value.
		 * @param value The threshold value.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitDarker(int16 value, uint16 timeout = 0);
};


#endif
