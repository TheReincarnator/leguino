#ifndef __LEGUINO_ACTOR_H
#define __LEGUINO_ACTOR_H


/**
 * Constant to refer to output A (use this in the actors' constructor.
 */
#define OUT_A 'A'

/**
 * Constant to refer to output B (use this in the actors' constructor.
 */
#define OUT_B 'B'

/**
 * Constant to refer to output C (use this in the actors' constructor.
 */
#define OUT_C 'C'

/**
 * Constant to refer to output D (use this in the actors' constructor.
 */
#define OUT_D 'D'

/**
 * Constant to refer to output E (use this in the actors' constructor.
 */
#define OUT_E 'E'

#define _SWITCHTIME_HIGH_NOTREADY 5
#define _SWITCHTIME_HIGH_READY 50
#define _SWITCHTIME_LOW 1


/**
 * <p>
 * Actors represent active devices you attach to the Leguino board, like
 * LEGO<sup>&copy;</sup> motors and lights. One actor usually requires one
 * output, but some actors may also represent a combination of outputs, like
 * the treads (two motors).
 * </p>
 *
 * <p>
 * Add actors to your program in the setup function, after initializing Leguino,
 * using the following example pattern:<br>
 * <code>leguino.add(drive = new Motor(OUT_A));</code><br>
 * or<br>
 * <code>leguino.add(drive = new Tread(OUT_A, OUT_B));</code><br>
 * or<br>
 * <code>leguino.add(frontLight = new Light(OUT_C));</code><br>
 * where <code>drive</code> and <code>frontLight</code> are global variables.
 * </p>
 *
 * <p>
 * In the main loop, after the regular update call to the Leguino platform,
 * use the actor's methods to control the outputs, spontaneously or
 * time-controlled.
 * </p>
 */
class Actor
{
	friend SingleActor;

	public:

		/**
		 * Destroys the actor.
		 * Don't call this method from your program.
		 */
		virtual ~Actor();

		/**
		 * Internal Leguino method to update the actor.
		 * Don't call this method from your program.
		 * @param msecs The number of milli-seconds since the last update.
		 */
		virtual void update(uint16 timeStep) = NULL;

	protected:

		Actor();
};


#endif
