#ifndef MUTEX_H_
#define MUTEX_H_

#include "Threads/Atomic_Int.h"
#include <functional>

class SDL_mutex;

namespace Threads {

class Condition;

class Mutex
{
public:
	Mutex ();
	~Mutex ();

	Mutex (const Mutex&) = delete;
	Mutex (Mutex&&) = default;
	Mutex& operator= (const Mutex&) = delete;
	Mutex& operator= (Mutex&&) = default;

	void lock ();
	void unlock ();

	template <class T> T ejecutarConLock (std::function<T()> fn);
	void ejecutarConLock (std::function<void()> fn);

private:
	SDL_mutex* mutex;
	bool blocked;

	friend class Condition;
};


// implementacion de template

template <class T>
T Mutex::ejecutarConLock (std::function<T()> fn)
{
	T retval;
	ejecutarConLock([&] {
		retval = fn();
	});
	return retval;
}

} /* namespace Threads */
#endif /* MUTEX_H_ */
