#ifndef __WATERVIEWIMG__
#define __WATERVIEWIMG__

#include "View.h"
#include "..\controlador\Entity\Shape.h"
#include "..\..\utils\Timer.h"
#include <map>

using namespace std;

class WaterViewImg : public View{

public:
	WaterViewImg();
	~WaterViewImg();
	void actionWater();
	void draw(SDLScreen & screen);
	static WaterViewImg* FactoryWater(); 
private:
	Timer timer;
	bool bRender;
	map<string, Shape> water;
	map<string, Shape>::iterator it;
	void loadWater();
	void iniView();
	void iniRender();
	void controlRender();
};


#endif
