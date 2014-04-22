#include "Mutex.h"
#include <SDL_thread.h>

Mutex::Mutex()
	: mutex(SDL_CreateMutex())
	, blocked(false)
{
	if (mutex == nullptr) {
		//Log::e("Couldn't create MUTEX");
	}
}

Mutex::~Mutex()
{
	if (blocked == true) {
		//Log::e("MUTEX ACTIVO - Eliminacion no permitida");
	}
	SDL_DestroyMutex(mutex);
}

void Mutex::lock ()
{
	SDL_LockMutex(mutex);
	blocked = true;
}

void Mutex::unlock ()
{
	blocked = false;
	SDL_UnlockMutex(mutex);
}

void Mutex::saferun (std::function<void()> fn)
{
	lock();
	try {
		fn();
	} catch (...) {
		unlock();
		throw std::current_exception();
	}
	unlock();
}
