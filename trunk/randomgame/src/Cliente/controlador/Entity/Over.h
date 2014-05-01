#ifndef __OVER__
#define __OVER__
#include <SDL.h>
#include <vector>

using namespace std;


class Over{
	public:
		static Over* getInstance();

	private:
		Over(void);
		~Over(void);
		static Over* over;
};

#endif