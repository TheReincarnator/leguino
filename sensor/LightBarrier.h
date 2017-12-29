#ifndef __LEGUINO_LIGHTBARRIER_H
#define __LEGUINO_LIGHTBARRIER_H


/**
 * A light barrier (IR LED and photo resistor resp. photo diode).<br>
 * Connect the IR LED (protected by a resistor) to VCC (+) and ground (-).
 * Connect the photo resistor or photo diode to a Leguino input and ground (-),
 * and use a pull-up resistor of 10k between the input and VCC (+).
 *
 * @see Sensor
 * @see SingleSensor
 */
class LightBarrier : public SingleSensor
{
	public:

		/**
		 * Creates a new light barrier.
		 * @param input The input the sensor is connected to.
		 * Use the constants IN_1 thru IN_6.
		 */
		LightBarrier(int8 input);

		/**
		 * Returns whether the barrier is currently clear (no obstacle is in
		 * between).
		 * @return Whether the barrier is currently clear.
		 */
		bool isClear();

		/**
		 * Returns whether the barrier is currently hit (an obstacle is in
		 * between).
		 * @return Whether the barrier is currently hit.
		 */
		bool isHit();

		/**
		 * Sets the brightnesses that indicate a hit and a clearing.
		 * Use a hit threshold bigger than the clear threshold. The bigger the
		 * gap, the more stable the barrier switching (the sensor behaves as a
		 * Schmitt trigger hysteresis). Defaults are 600 and 300.
		 * @param hitThreshold The hit threshold. Brightness at the receiver
		 * below this value is considered a hit.
		 * @param clearThreshold The clear threshold. Brightness at the receiver
		 * above this value is considered a clearing.
		 */
		void setThresholds(int16 hitThreshold, int16 clearThreshold);

		/**
		 * Waits until the barrier is clear (no obstacle is in between).
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitClear(uint16 timeout = 0);

		/**
		 * Waits until the barrier is hit (an obstacle is in between).
		 * @param msecs The number of milli-seconds to wait before giving up,
		 * or 0 (the default) to wait forever.
		 * @return Whether the event actually happened. false indicates a
		 * timeout.
		 */
		bool waitHit(uint16 timeout = 0);

	protected:

		int16 clearThreshold;
		bool hit;
		int16 hitThreshold;
};


#endif
