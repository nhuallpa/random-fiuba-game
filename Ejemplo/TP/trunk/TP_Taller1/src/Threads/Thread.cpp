#include "Thread.h"

#include "Log/Suceso.h"
#include "Threads/Mutex.h"
#include <SDL2/SDL_thread.h>
#include <functional>

namespace Threads {

// El codigo de Thread corre en el thread creador, Impl en el thread creado

struct Thread::Impl
{
	Impl (std::function<int()> fn);
	Impl (const Impl&) = delete;
	Impl& operator= (const Impl&) = delete;
	~Impl() = default;

	SDL_ThreadFunction thread_main();

	std::function<int()> fn;
	SDL_Thread *thread;

	Threads::Mutex editandoControles;
	bool huerfano;
	bool retornoInmediato;
	std::exception_ptr excepcionLanzada;
};

Thread::Impl::Impl (std::function<int()> fn)
	: fn(fn)
	, thread(nullptr)
	, editandoControles()
	, huerfano(false)
	, retornoInmediato(false)
	, excepcionLanzada()
{
}

SDL_ThreadFunction Thread::Impl::thread_main ()
{
	// lambda sin capturas convierte a puntero a funcion
	return [] (void *implCasteado) -> int {
		Thread::Impl *impl = static_cast<Thread::Impl*>(implCasteado);

		int retval = 0;
		bool borrar = false;
		try {
			retval = impl->fn();

			impl->editandoControles.ejecutarConLock([&] () {
				impl->retornoInmediato = true;
				borrar = impl->huerfano;
			});
			if (borrar && retval != 0) {
				auto msg = std::string("Thread huerfano '")
					+ SDL_GetThreadName(impl->thread) + "' retorna "
					+ std::to_string(retval);
				Log::Suceso(Log::DEBUG, msg);
			}
		} catch (std::exception& e) {
			impl->editandoControles.ejecutarConLock([&] () {
				impl->excepcionLanzada = std::current_exception();
				borrar = impl->huerfano;
			});
			if (borrar) {
				auto msg = std::string("Excepcion lanzada de thread huerfano '")
					+ SDL_GetThreadName(impl->thread) + "': " + e.what();
				Log::Suceso(Log::FATAL, msg);
			}
		}

		if (borrar) {
			delete impl;
		}
		return retval;
	};
}




Thread::Thread ()
	: retorno(0)
	, excepcion()
	, impl(nullptr)
{
}

Thread::Thread (std::string nombre, std::function<int()> fn)
	: retorno(0)
	, excepcion()
	, impl(new Thread::Impl(fn))
{
	impl->thread = SDL_CreateThread(impl->thread_main()
	                               , nombre.c_str()
	                               , static_cast<void*>(impl));
}

Thread::Thread (Thread&& original) noexcept
	: retorno(original.retorno)
	, excepcion(std::move(original.excepcion))
	, impl(original.impl)
{
	original.impl = nullptr;
}

Thread& Thread::operator= (Thread&& original) noexcept
{
	using std::swap;
	swap(original.retorno, retorno);
	swap(original.excepcion, excepcion);
	swap(original.impl, impl);
	return *this;
}

Thread::~Thread ()
{
	if (!termino()) {
		impl->editandoControles.ejecutarConLock([&] () {
			impl->huerfano = true;
		});
	}
}

bool Thread::termino ()
{
	if (impl != nullptr) {
		if (impl->retornoInmediato || impl->excepcionLanzada) {
			SDL_WaitThread(impl->thread, &retorno);
			excepcion = impl->excepcionLanzada;
			delete impl;
			impl = nullptr;
		}
	}
	return impl == nullptr;
}

int Thread::esperar ()
{
	if (!termino()) {
		SDL_WaitThread(impl->thread, &retorno);
		excepcion = impl->excepcionLanzada;
		delete impl;
		impl = nullptr;
	}
	if (excepcion) {
		std::rethrow_exception(excepcion);
	} else {
		return retorno;
	}
}

} /* namespace Threads */
