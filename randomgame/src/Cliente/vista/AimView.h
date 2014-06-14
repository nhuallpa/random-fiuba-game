#ifndef __AIMVIEW__
#define __AIMVIEW__

#include "WormView.h"
#include "Weapon.h"
#include "..\controlador\Contracts\OnChangeListener.h"
#include "..\controlador\Contracts\OnMovementListener.h"
#include "..\controlador\Entity\ChangeEvent.h"
#include "View.h"
#include <SDL.h>
#include <map>

#define STEP_AIM 5

using namespace std;

class AimView : 
	public View, 
	public OnChangeListener,
	public OnMovementListener{
public:
	AimView();
	~AimView();
	void aimBuild();
	void setWorm(WormView* aWorm, Weapon* aWeapon);
	void draw(SDLScreen & screen);
	void OnChange(ChangeEvent e);
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
