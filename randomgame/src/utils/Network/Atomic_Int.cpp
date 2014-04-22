#include "Atomic_Int.h"

namespace Threads {

Atomic_Int::Atomic_Int (int inicial)
	: valor(new SDL_atomic_t())
{
	*this = inicial;
}

Atomic_Int::~Atomic_Int ()
{
	delete valor;
}

Atomic_Int::operator int ()
{
	return SDL_AtomicGet(valor);
}

void Atomic_Int::inc ()
{
	SDL_AtomicIncRef(valor);
}

void Atomic_Int::dec ()
{
	SDL_AtomicDecRef(valor);
}

Atomic_Int& Atomic_Int::operator= (int v)
{
	SDL_AtomicSet(valor, v);
	return *this;
}

Atomic_Int& Atomic_Int::set_if (int nuevo, int viejo)
{
	SDL_AtomicCAS(valor, viejo, nuevo);
	return *this;
}

} /* namespace Threads */
