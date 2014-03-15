#ifndef QUEUE_H_
#define QUEUE_H_

#include "Threads/Mutex.h"
#include "Threads/Condition.h"
#include <list>

namespace Threads {

template <class T>
class Queue
{
public:
	Queue();

	~Queue() = default;
	Queue (const Queue&) = delete;
	Queue (Queue&&) = default;
	Queue& operator= (const Queue&) = delete;
	Queue& operator= (Queue&&) = default;

	T pop ();
	void push (T valor);
	size_t size ();
	bool empty ();

private:
	Mutex mutex;
	Condition noVacio;
	std::list<T> valores;
};


// implementacion del template
template <class T>
Queue<T>::Queue ()
	: mutex()
	, noVacio(mutex)
	, valores()
{
}

template <class T>
T Queue<T>::pop () {
	return mutex.ejecutarConLock<T>([&] {
		while (valores.empty()) {
			noVacio.wait();
		}
		T retval = std::move(valores.front());
		valores.pop_front();
		return retval;
	});
}

template <class T>
void Queue<T>::push (T valor) {
	mutex.ejecutarConLock([&] {
		valores.push_back(std::move(valor));
		noVacio.signal();
	});
}

template <class T>
size_t Queue<T>::size () {
	return mutex.ejecutarConLock<size_t>([&] {
		return valores.size();
	});
}

template <class T>
bool Queue<T>::empty () {
	return size() == 0;
}

} /* namespace Threads */
#endif /* QUEUE_H_ */
