#include "Mutex.h"

#include "Log/Suceso.h"
#include <SDL2/SDL_thread.h>

namespace Threads {

Mutex::Mutex()
	: mutex(SDL_CreateMutex())
	, blocked(false)
{
	if (mutex == nullptr) {
		throw Log::Suceso(Log::ERROR, "No se pudo crear mutex.");
	}
}

Mutex::~Mutex()
{
	if (blocked == true) {
		Log::Suceso(Log::DEBUG, "Intento borrar mutex activo.");
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

void Mutex::ejecutarConLock (std::function<void()> fn)
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

} /* namespace Threads */
