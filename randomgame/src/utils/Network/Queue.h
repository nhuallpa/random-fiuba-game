#ifndef QUEUE_H_
#define QUEUE_H_

#include "Mutex.h"
#include "Condition.h"
#include <list>

template <class T>
class Queue
{
public:
	Queue();

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
	return mutex.saferun<T>([&] {
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
	mutex.saferun([&] {
		valores.push_back(std::move(valor));
		noVacio.signal();
	});
}

template <class T>
size_t Queue<T>::size () {
	return mutex.saferun<size_t>([&] {
		return valores.size();
	});
}

template <class T>
bool Queue<T>::empty () {
	return size() == 0;
}
#endif /* QUEUE_H_ */
