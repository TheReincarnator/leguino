#ifndef __LEGUINO_PROGRAM_H
#define __LEGUINO_PROGRAM_H


#define MAX_THREADS 10


//#define DEBUG


#include "Arduino.h"
#include "LeguinoList.h"
#include "LeguinoIO.h"
#include "LeguinoTypes.h"


class Program;
class Thread;
class Step;
	class Emitter;
		class Start;
		class Sensor;
	class Actor;
	class TreadActor;
	class Pause;
	class Cond;
		class InputCond;
		class OutputCond;
		class VarCond;
	class Sync;
	class Math;


class Program
{
	friend class Thread;

	public:

		Program(Board * board);
		void addEmitter(Emitter * emitter);
		inline Board * getBoard();
		inline const ObjectList<Emitter *> & getEmitters();
		inline const ObjectList<Thread *> & getThreads();
		inline uint32 getTime();
		inline int16 getVar(int8 no);
		inline void setVar(int8 no, int16 value);
		void update();

	protected:

		Board * board;
		ObjectList<Emitter *> emitters;
		ObjectList<Thread *> threads;
		uint32 time;
		ValueList<int16> vars;
};

class Thread
{
	public:

		Thread(Emitter * emitter, Step * startStep);
		#ifdef DEBUG
			~Thread();
		#endif
		void forkToSuccessorsOfAndKill(Step * step);
		inline Emitter * getEmitter();
		inline Step * getStep();
		inline Program * getProgram();
		inline uint32 getStepStart();
		inline uint32 getThreadStart();
		void goTo(Step * step);
		inline bool isDying();
		void kill();

	protected:

		bool dying;
		Emitter * emitter;
		Step * step;
		uint32 stepStart;
		#ifdef DEBUG
			int threadNo;
			static int threadSequence;
		#endif
		uint32 threadStart;
};

class Step
{
	friend class Program;
	friend class Thread;

	public:

		Step();
		void attach(Step * successor);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline Program * getProgram();
		inline const ObjectList<Step *> & getSuccessors();
		inline void proceedToSuccessors(Thread * thread);
		void spawnThread(Emitter * emitter);

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);
		virtual void onEnter(Thread * thread);

		Program * program;
		#ifdef DEBUG
			int stepNo;
			static int stepSequence;
		#endif
		ObjectList<Step *> successors;
};

class Emitter : public Step
{
	friend class Program;
	friend class Thread;
	friend class Step;

	public:

		Emitter();
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif

	protected:

		inline bool isSuspended();
		inline void resume();
		inline void suspend();
		virtual void update(uint16 timeStep);

		bool suspended;
};

class Start : public Emitter
{
	public:

		Start(uint16 delay = 0, uint16 period = 0);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline uint16 getDelay();
		inline uint16 getPeriod();

	protected:

		virtual void update(uint16 timeStep);

		uint16 delay;
		uint32 nextTime;
		char state;
		uint16 period;

		static const char INITIAL;
		static const char ACTIVE;
		static const char ENDED;
};

class Sensor : public Emitter
{
	public:

		Sensor(int8 inputNo, int16 fromValue, int16 toValue);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline int16 getFromValue();
		inline int8 getInputNo();
		inline int16 getToValue();

	protected:

		virtual void update(uint16 timeStep);

		int16 fromValue;
		int8 inputNo;
		bool lastFiring;
		int16 toValue;
};

class Actor : public Step
{
	public:

		Actor(int8 outputNo, uint16 holdTime = 0);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline uint16 getHoldTime();
		inline int8 getOutputNo();
		inline Sequence * getSequence();
		inline void off();
		inline void on();
		inline void setHoldTime(uint16 holdTime);
		inline void setHoldTimeToSequence();
		inline void setSequence(Sequence * sequence);
		inline void setValue(int8 value);

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);

		uint16 holdTime;
		int8 outputNo;
		Sequence * sequence;
		int8 value;
};

class TreadActor : public Step
{
	public:

		TreadActor(int8 leftOutputNo, int8 rightOutputNo, uint16 holdTime = 0);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline int8 getDirection();
		inline int8 getLeftOutputNo();
		inline uint16 getHoldTime();
		inline int8 getRightOutputNo();
		inline int8 getThrust();
		inline void setDirection(int8 direction);
		inline void setHoldTime(uint16 holdTime);
		inline void setThrust(int8 thrust);
		inline void stop();
		inline void straight(int8 thrust);
		inline void turnAroundLeft(int8 thrust);
		inline void turnAroundRight(int8 thrust);
		inline void turnLeft(int8 thrust);
		inline void turnRight(int8 thrust);

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);

		int8 direction;
		int8 leftOutputNo;
		uint16 holdTime;
		int8 rightOutputNo;
		int8 thrust;
};

class Pause : public Step
{
	public:

		Pause(uint16 delay);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline uint16 getDelay();
		inline void setDelay(uint16 delay);

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);

		uint16 delay;
};

class Cond : public Step
{
	public:

		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline char getOp();
		inline int16 getValue();
		inline bool isWait();

		static const char EQUAL;
		static const char NOT_EQUAL;
		static const char GREATER;
		static const char GREATER_EQUAL;
		static const char LESS;
		static const char LESS_EQUAL;

	protected:

		Cond(char op, int16 value, bool wait = false);
		void proceedToSuccessor(Thread * thread, int16 value);

		char op;
		int16 value;
		bool wait;
};

class InputCond : public Cond
{
	public:

		InputCond(int8 inputNo, char op, int16 value, bool wait = false);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline int8 getInputNo();

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);

		int8 inputNo;
};


class OutputCond : public Cond
{
	public:

		OutputCond(int8 outputNo, char op, int16 value, bool wait = false);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline int8 getOutputNo();

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);

		int8 outputNo;
};

class VarCond : public Cond
{
	public:

		VarCond(int8 varNo, char op, int16 value, bool wait = false);
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline int8 getVarNo();

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);

		int8 varNo;
};

class Sync : public Step
{
	public:

		#ifdef DEBUG
			virtual const char * getClassName();
		#endif

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);
};

class Math : public Step
{
	public:

		Math();
		#ifdef DEBUG
			virtual const char * getClassName();
		#endif
		inline char getOp();
		inline void setConstA(int16 value);
		inline void setConstB(int16 value);
		inline void setInA(int8 inputNo);
		inline void setInB(int8 inputNo);
		inline void setOp(char op);
		inline void setOutA(int8 outputNo);
		inline void setOutB(int8 outputNo);
		inline void setVarA(int8 varNo);
		inline void setVarB(int8 varNo);
		inline void setTargetVar(int8 varNo);

		static const uint8 A_VAR;
		static const uint8 A_INPUT;
		static const uint8 A_OUTPUT;
		static const uint8 A_CONST;
		static const uint8 B_VAR;
		static const uint8 B_INPUT;
		static const uint8 B_OUTPUT;
		static const uint8 B_CONST;

		static const char ADD;
		static const char SUBTRACT;
		static const char MULTIPLY;
		static const char DIVIDE;
		static const char MODULO;
		static const char COMPARE;

	protected:

		virtual void execute(Thread * thread, uint16 timeStep);

		uint8 flags;
		char op;
		int8 targetVarNo;
		int16 valueA;
		int16 valueB;

		static const uint8 A_MASK;
		static const uint8 B_MASK;
};


inline const ObjectList<Emitter *> & Program::getEmitters()
{
	return emitters;
}

inline const ObjectList<Thread *> & Program::getThreads()
{
	return threads;
}

inline uint32 Program::getTime()
{
	return time;
}

inline int16 Program::getVar(int8 no)
{
	return vars.get(no);
}

inline void Program::setVar(int8 no, int16 value)
{
	vars.set(no, value);
}

inline Emitter * Thread::getEmitter()
{
	return emitter;
}

inline Program * Thread::getProgram()
{
	return step->getProgram();
}

inline Step * Thread::getStep()
{
	return step;
}

inline uint32 Thread::getStepStart()
{
	return stepStart;
}

inline uint32 Thread::getThreadStart()
{
	return threadStart;
}

inline bool Thread::isDying()
{
	return dying;
}

inline Program * Step::getProgram()
{
	return program;
}

inline const ObjectList<Step *> & Step::getSuccessors()
{
	return successors;
}

inline void Step::proceedToSuccessors(Thread * thread)
{
	thread->forkToSuccessorsOfAndKill(this);
}

inline bool Emitter::isSuspended()
{
	return suspended;
}

inline void Emitter::resume()
{
	suspended = false;
}

inline void Emitter::suspend()
{
	suspended = true;
}

inline uint16 Start::getDelay()
{
	return delay;
}

inline uint16 Start::getPeriod()
{
	return period;
}

inline int16 Sensor::getFromValue()
{
	return fromValue;
}

inline int8 Sensor::getInputNo()
{
	return inputNo;
}

inline int16 Sensor::getToValue()
{
	return toValue;
}

inline uint16 Actor::getHoldTime()
{
	return holdTime;
}

inline int8 Actor::getOutputNo()
{
	return outputNo;
}

inline Sequence * Actor::getSequence()
{
	return sequence;
}

inline void Actor::off()
{
	setValue(0);
}

inline void Actor::on()
{
	setValue(100);
}

inline void Actor::setHoldTime(uint16 holdTime)
{
	this->holdTime = holdTime;
}

inline void Actor::setHoldTimeToSequence()
{
	holdTime = 0;
	if (sequence == NULL)
		return;
	for (int i=0; i<sequence->getSteps(); i++)
		holdTime += sequence->getDuration(i);
}

inline void Actor::setSequence(Sequence * sequence)
{
	this->sequence = sequence;
}

inline void Actor::setValue(int8 value)
{
	this->value = value;
	sequence = NULL;
}

inline uint16 TreadActor::getHoldTime()
{
	return holdTime;
}

inline int8 TreadActor::getLeftOutputNo()
{
	return leftOutputNo;
}

inline int8 TreadActor::getRightOutputNo()
{
	return rightOutputNo;
}

inline int8 TreadActor::getThrust()
{
	return thrust;
}

inline void TreadActor::setDirection(int8 direction)
{
	this->direction = direction;
}

inline void TreadActor::setHoldTime(uint16 holdTime)
{
	this->holdTime = holdTime;
}

inline void TreadActor::setThrust(int8 thrust)
{
	this->thrust = thrust;
}

inline void TreadActor::stop()
{
	direction = 0;
	thrust = 0;
}

inline void TreadActor::straight(int8 thrust)
{
	direction = 0;
	this->thrust = thrust;
}

inline void TreadActor::turnAroundLeft(int8 thrust)
{
	direction = -100;
	this->thrust = thrust;
}

inline void TreadActor::turnAroundRight(int8 thrust)
{
	direction = 100;
	this->thrust = thrust;
}

inline void TreadActor::turnLeft(int8 thrust)
{
	direction = -50;
	this->thrust = thrust;
}

inline void TreadActor::turnRight(int8 thrust)
{
	direction = 50;
	this->thrust = thrust;
}

inline char Cond::getOp()
{
	return op;
}

inline int16 Cond::getValue()
{
	return value;
}

inline bool Cond::isWait()
{
	return wait;
}

inline int8 InputCond::getInputNo()
{
	return inputNo;
}

inline int8 OutputCond::getOutputNo()
{
	return outputNo;
}

inline int8 VarCond::getVarNo()
{
	return varNo;
}

inline uint16 Pause::getDelay()
{
	return delay;
}

inline void Pause::setDelay(uint16 delay)
{
	this->delay = delay;
}

inline Board * Program::getBoard()
{
	return board;
}

inline char Math::getOp()
{
	return op;
}

inline void Math::setConstA(int16 value)
{
	valueA = value;
	flags = (flags & ~A_MASK) | A_CONST;
}

inline void Math::setConstB(int16 value)
{
	valueB = value;
	flags = (flags & ~B_MASK) | B_CONST;
}

inline void Math::setInA(int8 inputNo)
{
	valueA = inputNo;
	flags = (flags & ~A_MASK) | A_INPUT;
}

inline void Math::setInB(int8 inputNo)
{
	valueB = inputNo;
	flags = (flags & ~B_MASK) | B_INPUT;
}

inline void Math::setOp(char op)
{
	this->op = op;
}

inline void Math::setOutA(int8 outputNo)
{
	valueA = outputNo;
	flags = (flags & ~A_MASK) | A_OUTPUT;
}

inline void Math::setOutB(int8 outputNo)
{
	valueB = outputNo;
	flags = (flags & ~B_MASK) | B_OUTPUT;
}

inline void Math::setVarA(int8 varNo)
{
	valueA = varNo;
	flags = (flags & ~A_MASK) | A_VAR;
}

inline void Math::setVarB(int8 varNo)
{
	valueB = varNo;
	flags = (flags & ~B_MASK) | B_VAR;
}

inline void Math::setTargetVar(int8 varNo)
{
	targetVarNo = varNo;
}


#endif
