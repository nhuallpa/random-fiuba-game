#ifndef __AIMVIEW__
#define __AIMVIEW__

#include "WormView.h"
#include "Weapon.h"
#include "..\..\utils\Util.h"
#include "..\controlador\Contracts\OnCoordListener.h"
#include "..\controlador\Contracts\OnMovementListener.h"
#include "..\controlador\Entity\CoordEvent.h"
#include "View.h"
#include <SDL.h>
#include <map>

using namespace std;

class AimView : 
	public View, 
	public OnCoordListener,
	public OnMovementListener{
public:
	AimView();
	~AimView();
	void aimBuild();
	void setWorm(WormView* aWorm, Weapon* aWeapon);
	void aimMouseBuild();
	void aimArrowBuild();
	void draw(SDLScreen & screen);
	void OnCoordinate(CoordEvent e);
	void OnMovement(MovementEvent e);
	void unAim();
	bool isShoot();

	//devuelvo <IdWorm, IdWeapon>
	pair<int, int> getData();

private:
	std::map<int, AimPosition>::iterator it;
	bool bDraw, bShoot,
		 bArrow, bCoord;
	int x, y, xx, yy,
		xDraw, yDraw;
	WormView* worm;
	Weapon* weapon;
	void getPositionUp(tPoint * point);
	void getPositionUnder(tPoint * point);
};

#endif

