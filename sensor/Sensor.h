#ifndef __LEGUINO_SENSOR_H
#define __LEGUINO_SENSOR_H


/**
 * Constant to refer to input 1 (use this in the sensors' constructor.
 */
#define IN_1 1

/**
 * Constant to refer to input 2 (use this in the sensors' constructor.
 */
#define IN_2 2

/**
 * Constant to refer to input 3 (use this in the sensors' constructor.
 */
#define IN_3 3

/**
 * Constant to refer to input 4 (use this in the sensors' constructor.
 */
#define IN_4 4

/**
 * Constant to refer to input 5 (use this in the sensors' constructor.
 */
#define IN_5 5

/**
 * Constant to refer to input 6 (use this in the sensors' constructor.
 */
#define IN_6 6


/**
 * <p>
 * Sensors represent passive devices you attach to the Leguino board, like
 * switches, buttons, knobs, light sensors, distance sensors, etc. Sensors
 * usually require one input.
 * </p>
 *
 * <p>
 * Add sensors to your program in the setup function, after initializing
 * Leguino, using the following example pattern:<br>
 * <code>leguino.add(button = new Switch(IN_1));</code>
 * or<br>
 * <code>leguino.add(brightness = new LightSensor(IN_3));</code>
 * or<br>
 * <code>leguino.add(distance = new DistanceSensor(IN_5));</code>
 * where <code>button</code>, <code>brightness</code>, and
 * <code>distance</code> are global variables.
 * </p>
 *
 * <p>
 * In the main loop, after the regular update call to the Leguino platform,
 * use the sensor's methods to query the inputs, blockingly or non-blockingly.
 * </p>
 */
class Sensor
{
	public:

		/**
		 * Destroys the sensor.
		 * Don't call this method from your program.
		 */
		virtual ~Sensor();

		/**
		 * Internal Leguino method to update the sensor.
		 * Don't call this method from your program.
		 * @param msecs The number of milli-seconds since the last update.
		 */
		virtual void update(uint16 timeStep) = NULL;

	protected:

		Sensor();
};


#endif
