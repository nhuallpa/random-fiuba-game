#ifndef __WEAPON__
#define __WEAPON__

#include "View.h"
#include <list>
#include "..\..\utils\Util.h"
#include "..\controlador\Entity\Shape.h"

using namespace std;

class Weapon : public View{

public:
	Weapon(WeaponId id, Shape s, list<string> keys, string allowWeapon);
	~Weapon();
	bool findWeapon(string key);
	void setWeapon(string key);
	void setRender();
	void removeWeapon(string key);
	void draw(SDLScreen & screen);
	void allow();
private:
	list<string> lWeaponView;
	WeaponId id;
	string allowWeapon;
	int x, y, width, height;
	void drawItems(SDLScreen & screen);
};

#endif
