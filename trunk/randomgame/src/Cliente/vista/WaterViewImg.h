#ifndef __WATERVIEWIMG__
#define __WATERVIEWIMG__

#include "View.h"
#include "..\controlador\Entity\Shape.h"
#include "..\..\utils\Timer.h"
#include <map>

using namespace std;

class WaterViewImg : public View{

public:
	WaterViewImg(float timmerChange, bool bBackground);
	~WaterViewImg();
	void actionWater();
	void draw(SDLScreen & screen);
	static WaterViewImg* FactoryWater(int Gap, float timmerChange, bool bBackground);
private:
	Timer timer;
	int timmerChange;
	bool bRender,
		 bBackground;
	map<string, Shape> water;
	pair<string, Shape> backgroundWater; 
	map<string, Shape>::iterator it;
	void loadWater(int Gap);
	void iniView();
	void iniRender();
	void controlRender();
	void drawSurf(SDLScreen & screen);
	void drawbackground(SDLScreen & screen);
};


#endif
