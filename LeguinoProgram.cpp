#include "LeguinoProgram.h"


Program::Program(Board * board)
{
	this->board = board;
	time = board->getTime();
}

void Program::addEmitter(Emitter * emitter)
{
	emitter->program = this;
	emitters.append(emitter);
}

void Program::update()
{
	board->update();
	if (board->getTime() <= time)
		return;

	uint16 timeStep = board->getTime() - time;
	time += timeStep;

	for (int i=0; i<threads.getCount(); i++)
	{
		Thread * thread = threads.get(i);
		thread->getStep()->execute(thread, timeStep);
	}
	for (int i=0; i<emitters.getCount(); i++)
		emitters.get(i)->update(timeStep);

	for (int i=threads.getCount()-1; i>=0;)
		if (threads.get(i)->isDying())
		{
			threads.deleteAt(i);
			if (i >= threads.getCount())
				i--;
		}
		else
			i--;
}

#ifdef DEBUG
	int Thread::threadSequence = 1;
#endif

Thread::Thread(Emitter * emitter, Step * startStep)
{
	#ifdef DEBUG
		threadNo = threadSequence++;
		char buffer[32];
		sprintf(buffer, "[Thread %d] new\n", threadNo);
		Serial.print(buffer);
	#endif

	dying = false;
	this->emitter = emitter;
	threadStart = startStep->getProgram()->getTime();
	startStep->getProgram()->threads.append(this);
	goTo(startStep);
}

#ifdef DEBUG
	Thread::~Thread()
	{
		char buffer[32];
		sprintf(buffer, "[Thread %d] end\n", threadNo);
		Serial.print(buffer);
	}
#endif

void Thread::forkToSuccessorsOfAndKill(Step * step)
{
	if (step->getSuccessors().isEmpty())
		kill();
	else
	{
		goTo(step->getSuccessors().getFirst());
		for (int i=1; i<step->getSuccessors().getCount(); i++)
			step->getSuccessors().get(i)->spawnThread(emitter);
	}
}

void Thread::goTo(Step * step)
{
	#ifdef DEBUG
		char buffer[64];
		sprintf(buffer, "[Thread %d] %s %d\n", threadNo, step->getClassName(), step->stepNo);
		Serial.print(buffer);
	#endif

	this->step = step;
	stepStart = step->getProgram()->getTime();
	step->onEnter(this);
}

void Thread::kill()
{
	dying = true;

	int emitterThreads = 0;
	const ObjectList<Thread *> & threads = getProgram()->getThreads();
	for (int i=0; i<threads.getCount(); i++)
		if (threads.get(i)->getEmitter() == emitter)
			emitterThreads++;

	if (emitterThreads <= 1)
	{
		// This is the last running thread of the emitter, so reactivate it
		emitter->resume();
	}
}

#ifdef DEBUG
	int Step::stepSequence = 1;
#endif

Step::Step()
{
	program = NULL;
	#ifdef DEBUG
		stepNo = stepSequence++;
	#endif
}

void Step::attach(Step * successor)
{
	if (program == NULL)
		panic();
	
	successor->program = program;
	successors.append(successor);
}

void Step::execute(Thread * thread, uint16 timeStep)
{
	// By default, do nothing and proceed to successors
	proceedToSuccessors(thread);
}

void Step::onEnter(Thread * thread)
{
	// By default, do nothing
}

#ifdef DEBUG
	const char * Step::getClassName()
	{
		return "step";
	}
#endif

void Step::spawnThread(Emitter * emitter)
{
	if (program->getThreads().getCount() >= MAX_THREADS)
		return;

	Thread * thread;
	if ((thread = new Thread(emitter, this)) == NULL)
		panic();

	emitter->suspend();
}

Emitter::Emitter()
{
	suspended = false;
}

#ifdef DEBUG
	const char * Emitter::getClassName()
	{
		return "emitter";
	}
#endif

void Emitter::update(uint16 timeStep)
{
}


const char Start::INITIAL = 0;
const char Start::ACTIVE = 1;
const char Start::ENDED = 2;

Start::Start(uint16 delay, uint16 period)
{
	this->delay = delay;
	this->period = period;
	state = INITIAL;
	nextTime = 0;
}

#ifdef DEBUG
	const char * Start::getClassName()
	{
		return "start";
	}
#endif

void Start::update(uint16 timeStep)
{
	if (state == INITIAL)
		nextTime = program->getTime() + delay;

	if (!suspended && state != ENDED && nextTime <= program->getTime())
	{
		spawnThread(this);

		if (period > 0)
			nextTime = program->getTime() + period;
		else
			nextTime = ENDED;
	}
}

Sensor::Sensor(int8 inputNo, int16 fromValue, int16 toValue)
{
	this->inputNo = inputNo;
	this->fromValue = fromValue;
	this->toValue = toValue;
	lastFiring = false;
}

#ifdef DEBUG
	const char * Sensor::getClassName()
	{
		return "sensor";
	}
#endif

void Sensor::update(uint16 timeStep)
{
	int16 value = program->getBoard()->getInput(inputNo)->getValue();
	bool firing = value >= fromValue && value <= toValue;

	if (!suspended && firing && !lastFiring)
		spawnThread(this);

	lastFiring = firing;
}

Actor::Actor(int8 outputNo, uint16 holdTime)
{
	this->outputNo = outputNo;
	this->holdTime = holdTime;
	sequence = NULL;
	value = 100;
}

void Actor::execute(Thread * thread, uint16 timeStep)
{
	Output * output = program->getBoard()->getOutput(outputNo);

	if (sequence != NULL)
		output->setSequence(sequence);
	else
		output->setValue(value);

	if (holdTime == 0)
		proceedToSuccessors(thread);
	else if (thread->getProgram()->getTime() >= thread->getStepStart() + holdTime)
	{
		output->setValue(0);
		proceedToSuccessors(thread);
	}
}

#ifdef DEBUG
	const char * Actor::getClassName()
	{
		return "single actor";
	}
#endif

TreadActor::TreadActor(int8 leftOutputNo, int8 rightOutputNo, uint16 holdTime)
{
	this->leftOutputNo = leftOutputNo;
	this->rightOutputNo = rightOutputNo;
	this->holdTime = holdTime;
	direction = 0;
	thrust = 100;
}

void TreadActor::execute(Thread * thread, uint16 timeStep)
{
	program->getBoard()->tread(leftOutputNo, rightOutputNo, direction, thrust);

	if (holdTime == 0)
		proceedToSuccessors(thread);
	else if (thread->getProgram()->getTime() >= thread->getStepStart() + holdTime)
	{
		program->getBoard()->treadStop(leftOutputNo, rightOutputNo);
		proceedToSuccessors(thread);
	}
}

#ifdef DEBUG
	const char * TreadActor::getClassName()
	{
		return "tread actor";
	}
#endif

Pause::Pause(uint16 delay)
{
	this->delay = delay;
}

void Pause::execute(Thread * thread, uint16 timeStep)
{
	#ifdef DEBUG
		Serial.print("Pausing\n");
	#endif

	if (thread->getProgram()->getTime() >= thread->getStepStart() + delay)
	{
		#ifdef DEBUG
			Serial.print("Pause done\n");
		#endif

		proceedToSuccessors(thread);
	}
}

#ifdef DEBUG
	const char * Pause::getClassName()
	{
		return "pause";
	}
#endif

const char Cond::EQUAL = '=';
const char Cond::NOT_EQUAL = '!';
const char Cond::GREATER = '>';
const char Cond::GREATER_EQUAL = 'G';
const char Cond::LESS = '<';
const char Cond::LESS_EQUAL = 'L';

Cond::Cond(char op, int16 value, bool wait)
{
	this->op = op;
	this->value = value;
	this->wait = wait;
}

#ifdef DEBUG
	const char * Cond::getClassName()
	{
		return "condition";
	}
#endif

void Cond::proceedToSuccessor(Thread * thread, int16 value)
{
	bool result = false;
	switch (op)
	{
		case EQUAL: result = value == this->value; break;
		case NOT_EQUAL: result = value != this->value; break;
		case GREATER: result = value > this->value; break;
		case GREATER_EQUAL: result = value >= this->value; break;
		case LESS: result = value < this->value; break;
		case LESS_EQUAL: result = value <= this->value; break;
	}

	if (result)
	{
		if (successors.getCount() >= 1)
			thread->goTo(successors.getFirst());
		else
			thread->kill();
	}
	else if (!wait)
	{
		if (successors.getCount() >= 2)
			thread->goTo(successors.get(1));
		else
			thread->kill();
	}
}

InputCond::InputCond(int8 inputNo, char op, int16 value, bool wait)
	: Cond(op, value, wait)
{
	this->inputNo = inputNo;
}

void InputCond::execute(Thread * thread, uint16 timeStep)
{
	proceedToSuccessor(thread, program->getBoard()->getInput(inputNo)->getValue());
}

#ifdef DEBUG
	const char * InputCond::getClassName()
	{
		return "input condition";
	}
#endif

OutputCond::OutputCond(int8 outputNo, char op, int16 value, bool wait)
	: Cond(op, value, wait)
{
	this->outputNo = outputNo;
}

void OutputCond::execute(Thread * thread, uint16 timeStep)
{
	proceedToSuccessor(thread, program->getBoard()->getOutput(outputNo)->getCurrentValue());
}

#ifdef DEBUG
	const char * OutputCond::getClassName()
	{
		return "output condition";
	}
#endif

VarCond::VarCond(int8 varNo, char op, int16 value, bool wait)
	: Cond(op, value, wait)
{
	this->varNo = varNo;
}

void VarCond::execute(Thread * thread, uint16 timeStep)
{
	proceedToSuccessor(thread, program->getVar(varNo));
}

#ifdef DEBUG
	const char * VarCond::getClassName()
	{
		return "var condition";
	}
#endif


void Sync::execute(Thread * thread, uint16 timeStep)
{
	// TODO
	Step::execute(thread, timeStep);
}

#ifdef DEBUG
	const char * Sync::getClassName()
	{
		return "sync";
	}
#endif

const uint8 Math::A_CONST = 0x00;
const uint8 Math::A_INPUT = 0x01;
const uint8 Math::A_OUTPUT = 0x02;
const uint8 Math::A_VAR = 0x03;
const uint8 Math::B_CONST = 0x00;
const uint8 Math::B_INPUT = 0x10;
const uint8 Math::B_OUTPUT = 0x20;
const uint8 Math::B_VAR = 0x30;

const char Math::ADD = '+';
const char Math::SUBTRACT = '-';
const char Math::MULTIPLY = '*';
const char Math::DIVIDE = '/';
const char Math::MODULO = '%';
const char Math::COMPARE = '=';

Math::Math()
{
	flags = 0;
	op = ADD;
	targetVarNo = 0;
	setConstA(0);
	setConstB(0);
}

void Math::execute(Thread * thread, uint16 timeStep)
{
	int16 currentA;
	switch (flags & A_MASK)
	{
		case A_INPUT: currentA = program->getBoard()->getInput(valueA)->getValue(); break;
		case A_OUTPUT: currentA = program->getBoard()->getOutput(valueA)->getCurrentValue(); break;
		case A_VAR: currentA = program->getVar(valueA); break;
		default: currentA = valueA;
	}

	int16 currentB;
	switch (flags & B_MASK)
	{
		case B_INPUT: currentB = program->getBoard()->getInput(valueB)->getValue(); break;
		case B_OUTPUT: currentB = program->getBoard()->getOutput(valueB)->getCurrentValue(); break;
		case B_VAR: currentB = program->getVar(valueB); break;
		default: currentB = valueB;
	}

	int16 result;
	switch (op)
	{
		case ADD: result = currentA + currentB; break;
		case SUBTRACT: result = currentA - currentB; break;
		case MULTIPLY: result = currentA * currentB; break;
		case DIVIDE: result = currentA / currentB; break;
		case MODULO: result = currentA % currentB; break;
		case COMPARE: result = currentA > currentB ? 1 : (currentA < currentB) ? -1 : 0; break;
		default: result = 0;
	}

	program->setVar(targetVarNo, result);
}

#ifdef DEBUG
	const char * Math::getClassName()
	{
		return "math";
	}
#endif
