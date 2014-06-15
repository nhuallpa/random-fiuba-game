#ifndef __WATERVIEWIMG__
#define __WATERVIEWIMG__

#include "View.h"
#include <map>

using namespace std;

class WaterViewImg : public View{

public:
	WaterViewImg();
	~WaterViewImg();
	void actionWater();
	void draw(SDLScreen & screen);
private:
	map<int, string> mapa;
};


#endif
