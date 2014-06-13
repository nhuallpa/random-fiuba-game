#ifndef __AIMVIEW__
#define __AIMVIEW__

#include "WormView.h"
#include "Weapon.h"
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
	void draw(SDLScreen & screen);
	void OnCoordinate(CoordEvent e);
	void OnMovement(MovementEvent e);
	void unAim();
	bool isShootMouse();
	bool isShootEnter();

	//devuelvo <IdWorm, IdWeapon>
	pair<int, int> getData();
	int getAngle();

private:
	bool bShootMouse,
		 bShootEnter;
	int x, y, xRelative, yRelative,
		xDraw, yDraw;
	WormView* worm;
	Weapon* weapon;
	void PositionUp();
	void PositionUnder();
	void PositionAbs();

	bool firstCoord();
	bool secondCoord();
	bool thirdCoord();
	bool fourthCoord();
	void aimBuildMouse();
	void aimBuildEnter();

};

#endif

