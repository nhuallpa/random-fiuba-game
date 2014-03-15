#ifndef MAKE_UNIQUE_H_
#define MAKE_UNIQUE_H_

#include <memory>

template <class T, class... Args>
std::unique_ptr<T> make_unique (Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


#endif /* MAKE_UNIQUE_H_ */
