#ifndef MUTEX_H_
#define MUTEX_H_

class SDL_mutex;

class Mutex
{
friend class Condition;
public:
	Mutex ();
	~Mutex ();

	void lock ();
	void unlock ();

private:
	SDL_mutex* mutex;
	bool blocked;


};

#endif
