#ifndef __LEGUINO_SINGLEACTOR_H
#define __LEGUINO_SINGLEACTOR_H


class SingleActor : public Actor
{
	protected:

		int8 backwardPin;
		int8 currentValue;
		int8 direction;
		int8 forwardPin;
		int8 powerPin;
		int8 requestedValue;
		Sequence * sequence;
		int sequenceStep;
		uint16 sequenceStepDuration;
		uint16 sequenceStepRemaining;
		int8 sequenceStepStartValue;
		int8 sequenceStepEndValue;

		void switchDirection(int8 value);
		void updateOutputPins(uint16 timeStep);
		void updateSequence(uint16 timeStep);

	public:
	
		SingleActor(int8 output);
		uint16 getCurrentValue();
		Sequence * getSequence();
		void off();
		void on();
		void on(uint16 msecs);
		void setSequence(Sequence * sequence);
		void setValue(int8 value);
		void setValue(int8 value, uint16 msecs);
		virtual void update(uint16 timeStep);
};


#endif
