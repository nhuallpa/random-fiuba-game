#include "Thread.h"
#include "Mutex.h"



Thread::Thread ()
	: retval(0)
	, thread_exc()
{
}

Thread::Thread (std::string nombre,  int (*fn)(void*) )
{
	this->myThread = SDL_CreateThread(fn, nombre.c_str(), (void *)NULL);
}

Thread::Thread (std::string nombre,  int (*fn)(void*), void* data )
{
	this->myThread = SDL_CreateThread(fn, nombre.c_str(), data);
}


int Thread::wait ()
{
	SDL_WaitThread(this->myThread, &this->retval);
	return this->retval;
}


