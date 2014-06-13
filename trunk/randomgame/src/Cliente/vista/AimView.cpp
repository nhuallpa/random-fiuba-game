#include "AimView.h"
#include "TextureManager.h"

AimView::AimView():View(30,30){
	bShootMouse = 
	bShootEnter = false;
	xRelative = 90, yRelative = 0;
}

AimView::~AimView(){}


void AimView::aimBuild(){
	switch(this->weapon->getId()){
		case BURRO:
		case AIRATTACK:
			aimBuildMouse();
			break;
		case BAZOOKA:
		case GRENADE:
		case HOLY:
		case HMISSILE:
			aimBuildEnter();
			break;
		default:;
	}
}

void AimView::setWorm(WormView* aWorm, Weapon* aWeapon){

	this->worm = aWorm;
	this->weapon = aWeapon;
}
void AimView::aimBuildEnter(){
	this->PositionAbs();
	this->xDraw = this->x + this->xRelative; 
	this->yDraw = this->y + this->yRelative;

	bShootEnter = true;
	bShootMouse = false;
}

void AimView::aimBuildMouse(){
	bShootMouse = true;
	bShootEnter = false;
	SDL_ShowCursor(0);
}

bool AimView::isShootMouse(){
	return bShootMouse;
}

bool AimView::isShootEnter(){
	return bShootEnter;
}

void AimView::unAim(){
	bShootMouse = 
	bShootEnter = false;
	SDL_ShowCursor(1);
}

void AimView::OnCoordinate(CoordEvent e){
	if(bShootMouse){
		this->xDraw = e.x - 30;
		this->yDraw = e.y - 30;
	}
}

void AimView::OnMovement(MovementEvent e){
	if(bShootEnter){
		if(e.me == M_ANTICLOCK){
			PositionUp();
			this->xDraw = this->x + this->xRelative;
			this->yDraw = this->y + this->yRelative;
		}
		else if(e.me == M_SHEDULE){
			PositionUnder();
			this->xDraw = this->x + this->xRelative;
			this->yDraw = this->y + this->yRelative;
		}
		else if((e.x == 1) || (e.x == -1)){

		}

	}
}

int AimView::getAngle(){
	return -1;
}

pair<int, int> AimView::getData(){
	return pair<int, int>(this->worm->getId(), this->weapon->getId());
}

void AimView::PositionUp(){
	if(this->firstCoord()){
		xRelative-= STEP_AIM, yRelative-= STEP_AIM;
	}
	else if(this->secondCoord()){
		xRelative-= STEP_AIM, yRelative+= STEP_AIM;
	}
	else if(this->thirdCoord()){
		xRelative+= STEP_AIM, yRelative+= STEP_AIM;
	}
	else if(this->fourthCoord()){
		xRelative+= STEP_AIM, yRelative-= STEP_AIM;
	}
}

void AimView::PositionUnder(){
	if(this->firstCoord()){
		xRelative+= STEP_AIM, yRelative+= STEP_AIM;
	}
	else if(this->secondCoord()){
		xRelative+= STEP_AIM, yRelative-= STEP_AIM;
	}
	else if(this->thirdCoord()){
		xRelative-= STEP_AIM, yRelative-= STEP_AIM;
	}
	else if(this->fourthCoord()){
		xRelative-= STEP_AIM, yRelative+= STEP_AIM;
	}
}

void AimView::PositionAbs(){
	this->x = this->worm->getXCenter();
	this->y = this->worm->getYCenter();
}



void AimView::draw(SDLScreen & screen){
	if(bShootMouse){
		TextureManager::Instance().drawFrameOnScreen(
						"aim", this->xDraw, this->yDraw, 60, 57, 
						0, 0, screen.getRenderer(),
						false, SDL_FLIP_NONE);
		}
	else if(bShootEnter){
		TextureManager::Instance().drawFrame(
						"aim", this->xDraw, this->yDraw, 60, 57, 
						0, 0, screen.getRenderer(),
						false, SDL_FLIP_NONE);
	}
}








bool AimView::firstCoord() {
	return ((xRelative>0)&& (yRelative<=0));
}
bool AimView::secondCoord(){
	return ((xRelative<=0)&& (yRelative<0));
}
bool AimView::thirdCoord() {
	return ((xRelative<0)&& (yRelative>=0));
}
bool AimView::fourthCoord(){
	return ((xRelative>=0)&& (yRelative>0));
}
