#ifndef __LEGUINO_SINGLESENSOR_H
#define __LEGUINO_SINGLESENSOR_H


/**
 * A Leguino sensor that requires exactly one input jack (e.g. switches,
 * light barriers, distance sensors). You can use sub-classes of this class,
 * or use the single sensor directly to get raw values, e.g. for knobs or
 * probes. Remember to use pull-ups or pull-downs if your input may be open,
 * as Leguino inputs have high input resistance.
 *
 * @see Switch
 * @see LightBarrier
 * @see LightSensor
 * @see DistanceSensor
 */
class SingleSensor : public Sensor
{
	public:
		
		/**
		 * Creates a new single sensor.
		 * @param input The input the sensor is connected to.
		 * Use the constants IN_1 thru IN_6.
		 */
		SingleSensor(int8 input);

		/**
		 * Returns the current raw input voltage of the sensor, without any
		 * transformation to represent the part specifications.
		 * @return The raw input voltage, from 0 to 5000 milli-Volts.
		 */
		uint16 getMilliVolts();

		/**
		 * Returns the current raw input value of the sensor, without any
		 * transformation to represent the part specifications.
		 * @return The raw input value, from 0 (0 Volts) to 1023 (5 Volts).
		 */
		uint16 getRawValue();

		/**
		 * Internal Leguino method to update the sensor.
		 * Don't call this method from your program.
		 * @param msecs The number of milli-seconds since the last update.
		 */
		virtual void update(uint16 timeStep);

	protected:

		int8 analogPin;
		int8 pin;
		int16 valueCache;

		bool waitUntilRaw(char comparator, int16 value, uint16 timeout);
};


#endif
