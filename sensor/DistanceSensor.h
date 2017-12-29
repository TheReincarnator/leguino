#ifndef __LEGUINO_DISTANCESENSOR_H
#define __LEGUINO_DISTANCESENSOR_H


/**
 * A distance sensor (e.g. infra-red type Sharp GP2Y0A21YK).<br>
 * Connect the three pins to VCC (+), ground (-) and a Leguino input. The
 * GP2Y0A21YK does not need a pull-up resistor.
 *
 * @see Sensor
 * @see SingleSensor
 */
class DistanceSensor : public SingleSensor
{
	public:

		/**
		 * Creates a new distance sensor.
		 * @param input The input the sensor is connected to.
		 * Use the constants IN_1 thru IN_6.
		 */
		DistanceSensor(int8 input);

		/**
		 * The distance-sensor object is calibrates to match Sharp GP2Y0A21YK.
		 * Use this method to adapt to any other type of distance sensor.
		 * @param minimumRawValue The minimum reliable raw value of the sensor.
		 * All values below this threshold are considered that threshold.
		 * @param maximumRawValue The maximum reliable raw value of the sensor.
		 * All values above this threshold are considered that threshold.
		 * @param mmPerRawInverse The number of milli-meters per raw-value
		 * inverse. The large the value, the bigger the results.
		 * @param mmOffset The number of milli-meters to add to the conversion
		 * result. The large the value, the bigger the results.
		 */
		void calibrate(uint16 minimumRawValue, uint16 maximumRawValue,
			uint16 mmPerRawInverse, int16 mmOffset);

		/**
		 * Returns the distance of the nearest obstacle in front of the sensor.
		 * @return The distance in centi-meters.
		 */
		int16 getDistanceCm();

		/**
		 * Returns the distance of the nearest obstacle in front of the sensor.
		 * @return The distance in milli-meters.
		 */
		int16 getDistanceMm();

		/**
		 * Waits (blocks) until the nearest obstacle in front of the sensor is
		 * farther away than a given threshold.
		 * @param cm The threshold in centi-meters.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitFartherCm(int16 cm, uint16 timeout = 0);

		/**
		 * Waits (blocks) until the nearest obstacle in front of the sensor is
		 * farther away than a given threshold.
		 * @param cm The threshold in milli-meters.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitFartherMm(int16 mm, uint16 timeout = 0);

		/**
		 * Waits (blocks) until the nearest obstacle in front of the sensor is
		 * nearer than a given threshold.
		 * @param cm The threshold in centi-meters.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitNearerCm(int16 cm, uint16 timeout = 0);

		/**
		 * Waits (blocks) until the nearest obstacle in front of the sensor is
		 * nearer than a given threshold.
		 * @param cm The threshold in milli-meters.
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitNearerMm(int16 mm, uint16 timeout = 0);

	protected:

		uint16 maximumRawValue;
		uint16 minimumRawValue;
		int16 mmOffset;
		uint16 mmPerRawInverse;

		bool waitUntilMm(char comparator, int16 mm, uint16 timeout = 0);
};


#endif
