#ifndef __WEAPON__
#define __WEAPON__

#include "View.h"
#include <map>
#include "..\..\utils\Util.h"

using namespace std;

enum WSTATE {SELECT, ENABLE, DISABLE};

class Weapon : public View{

public:
	Weapon(WeaponId id, int x, int y, int width, int height);
	~Weapon();
	void setWeapon(WSTATE ws, string ref);
	void setState(WSTATE ws);
	void setRender();
	string getWeapon(WSTATE ws);
	void draw(SDLScreen & screen);
private:
	map<WSTATE, string> weapons;
	WSTATE state;
	WeaponId id;
	bool render;
	int x, y, width, height;
};

#endif
