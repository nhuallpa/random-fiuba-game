#include "AimView.h"
#include "TextureManager.h"

AimView::AimView():View(30,30){
	bDraw = bShoot = false;
}

AimView::~AimView(){}


void AimView::aimBuild(WormView* aWorm, Weapon* aWeapon){
	this->worm = aWorm;
	this->weapon = aWeapon;
	switch(aWeapon->getId()){
		case BURRO:
		case AIRATTACK:
			aimMouseBuild(aWorm, aWeapon);
			break;
		default:;
	}
}

void AimView::aimMouseBuild(WormView* aWorm, Weapon* aWeapon){
	bDraw = bShoot = true;
	SDL_ShowCursor(0);

}

bool AimView::isShoot(){
	return bShoot;
}

void AimView::unAim(){
	bDraw = bShoot = false;
	SDL_ShowCursor(1);
}

void AimView::OnCoordinate(CoordEvent e){
	this->x = e.x;
	this->y = e.y;
}

pair<int, int> AimView::getData(){
	return pair<int, int>(this->worm->getId(), this->weapon->getId());
}

void AimView::draw(SDLScreen & screen){
	if(bDraw){
		TextureManager::Instance().drawFrameOnScreen(
						"aim", this->x - 30, this->y - 30, 60, 57, 
						0, 0, screen.getRenderer(),
						false, SDL_FLIP_NONE);
		}
}