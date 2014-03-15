#ifndef CONDITION_H_
#define CONDITION_H_

class SDL_cond;

namespace Threads {

class Mutex;

class Condition
{
public:
	Condition (Mutex& mutex);

	Condition (const Condition&) = delete;
	Condition (Condition&&) = default;
	Condition& operator= (const Condition&) = delete;
	Condition& operator= (Condition&&) = default;
	~Condition ();

	void wait ();
	void wait (int timeout_ms);
	void signal ();
	void broadcast ();

private:
	Mutex* mutex;
	SDL_cond* cond;
};

} /* namespace Threads */
#endif /* CONDITION_H_ */
