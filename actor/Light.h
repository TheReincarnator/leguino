#ifndef __LEGUINO_LIGHT_H
#define __LEGUINO_LIGHT_H


/**
 * A Leguino single actor representing a LEGO<sup>&copy;</sup> Technic light.
 *
 * @see Actor
 * @see SingleActor
 */
class Light : public SingleActor
{
	public:

		/**
		 * Creates a new light.
		 * @param output The output the light is connected to.
		 * Use the constants OUT_A thru OUT_E.
		 */
		Light(int8 output);
};


#endif
