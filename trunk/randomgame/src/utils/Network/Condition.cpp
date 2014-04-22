#include "Condition.h"
#include "Mutex.h"
#include <SDL_mutex.h>


Condition::Condition (Mutex& mutex)
	: mutex(&mutex)
	, cond(SDL_CreateCond())
{
}

Condition::~Condition ()
{
	SDL_DestroyCond(cond);
}

void Condition::wait ()
{
	SDL_CondWait(cond, mutex->mutex);
}

void Condition::wait (int timeout_ms)
{
	SDL_CondWaitTimeout(cond, mutex->mutex, timeout_ms);
}

void Condition::signal ()
{
	SDL_CondSignal(cond);
}

void Condition::broadcast ()
{
	SDL_CondBroadcast(cond);
}
