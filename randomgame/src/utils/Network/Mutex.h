#ifndef MUTEX_H_
#define MUTEX_H_

#include <functional>
class SDL_mutex;

class Mutex
{
friend class Condition;
public:
	Mutex ();
	~Mutex ();

	void lock ();
	void unlock ();

	template <class T> T saferun (std::function<T()> fn);
	void saferun (std::function<void()> fn);

private:
	SDL_mutex* mutex;
	bool blocked;


};


// implementacion de template

template <class T>
T Mutex::saferun (std::function<T()> fn)
{
	T retval;
	saferun([&] {
		retval = fn();
	});
	return retval;
}

#endif
