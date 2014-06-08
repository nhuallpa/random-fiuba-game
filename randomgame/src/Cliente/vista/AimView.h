#ifndef __AIMVIEW__
#define __AIMVIEW__

#include "WormView.h"
#include "Weapon.h"
#include "..\..\utils\Util.h"
#include "..\controlador\Contracts\OnCoordListener.h"
#include "..\controlador\Entity\CoordEvent.h"
#include "View.h"
#include <SDL.h>
#include <map>

using namespace std;

class AimView : public View, public OnCoordListener{
public:
	AimView();
	~AimView();
	void aimBuild(WormView* aWorm, Weapon* aWeapon);
	void aimMouseBuild(WormView* aWorm, Weapon* aWeapon);
	void draw(SDLScreen & screen);
	void OnCoordinate(CoordEvent e);
	void unAim();
	bool isShoot();

	//devuelvo <IdWorm, IdWeapon>
	pair<int, int> getData();

private:
	bool bDraw, bShoot;
	int x, y;
	WormView* worm;
	Weapon* weapon;
};

#endif

