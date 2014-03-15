#ifndef ATOMIC_INT_H_
#define ATOMIC_INT_H_

#include <SDL2/SDL_atomic.h>

namespace Threads {

class Atomic_Int
{
public:
	explicit Atomic_Int (int inicial = 0);

	Atomic_Int (const Atomic_Int&) = delete;
	Atomic_Int& operator= (const Atomic_Int&) = delete;
	~Atomic_Int ();

	operator int ();
	void inc ();
	void dec ();
	Atomic_Int& operator= (int v);
	Atomic_Int& set_if (int nuevo, int viejo);

private:
	SDL_atomic_t *valor;
};

} /* namespace Threads */
#endif /* ATOMIC_INT_H_ */
