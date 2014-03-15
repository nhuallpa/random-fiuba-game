#ifndef THREAD_H_
#define THREAD_H_

#include <functional>
#include <string>

namespace Threads {

class Thread
{
public:
	Thread ();
	Thread (std::string nombre, std::function<int()> fn);

	Thread (const Thread&) = delete;
	Thread (Thread&&) noexcept;
	Thread& operator= (const Thread&) = delete;
	Thread& operator= (Thread&&) noexcept;
	~Thread ();

	bool termino (); // Indica si el thread ya retorno o lanzo excepcion.
	int esperar ();  // Bloquea hasta que el thread termine, y luego pasa el retorno/excepcion del thread.

private:
	int retorno;
	std::exception_ptr excepcion;
	class Impl;
	Impl *impl; // Oculto por ser propiedad del thread creado.
};

} /* namespace Threads */
#endif /* THREAD_H_ */
