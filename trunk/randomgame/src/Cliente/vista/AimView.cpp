#include "AimView.h"
#include "TextureManager.h"

AimView::AimView():View(30,30){
	bDraw = bShoot = bArrow = bCoord = false;
	it = Util::aim.begin();
	yy = 0;
}

AimView::~AimView(){}


void AimView::aimBuild(){
	switch(this->weapon->getId()){
		case BURRO:
		case AIRATTACK:
			aimMouseBuild();
			break;
		case BAZOOKA:
		case GRENADE:
		case HOLY:
		case HMISSILE:
			aimArrowBuild();
			break;
		default:;
	}
}

void AimView::setWorm(WormView* aWorm, Weapon* aWeapon){

	this->worm = aWorm;
	this->weapon = aWeapon;
}
void AimView::aimArrowBuild(){
	this->PositionAbs();
	this->xDraw = this->x + it->second.pointView.x; 
	this->yDraw = this->y + it->second.pointView.y;

	bDraw = bArrow =  bShoot = true;
	bCoord = false;
}

void AimView::aimMouseBuild(){
	bDraw = bCoord = bShoot = true;
	bArrow = false;
	SDL_ShowCursor(0);

}

bool AimView::isShoot(){
	return bShoot;
}

void AimView::unAim(){
	bDraw = bShoot = false;
	bArrow = false;
	bCoord = false;
	SDL_ShowCursor(1);
}

void AimView::OnCoordinate(CoordEvent e){
	if(bCoord){
		this->xDraw = e.x - 30;
		this->yDraw = e.y - 30;
	}
}

void AimView::OnMovement(MovementEvent e){
	tPoint position;
	if(bArrow){
		if(e.y == -1){
			getPositionUp(&position);
			this->xDraw = this->x + position.x;
			this->yDraw = this->y + position.y;
		}
		else if(e.y == 1){
			getPositionUnder(&position);
			this->xDraw = this->x + position.x;
			this->yDraw = this->y + position.y;
		}
		else if((e.x == 1) || (e.x == -1)){

		}

	}
}

int AimView::getAngle(){
	if(it != Util::aim.end()){
		return it->first;
	}
	return -1;
}

pair<int, int> AimView::getData(){
	return pair<int, int>(this->worm->getId(), this->weapon->getId());
}

void AimView::getPositionUp(tPoint * point){
	if(Util::aim.size()>0){
		it++;
		if(it == Util::aim.end()){
			it = Util::aim.begin();
		}
		point->x = it->second.pointView.x;
		point->y = it->second.pointView.y;
	}
}

void AimView::getPositionUnder(tPoint * point){
	if(Util::aim.size()>0){
		it--;
		if(it == Util::aim.begin() || it == Util::aim.end()){
			if(it == Util::aim.begin()){
			}
			else{
				it = Util::aim.end();
				it--;
			}
		}
		point->x = it->second.pointView.x;
		point->y = it->second.pointView.y;
	}



}

void AimView::PositionAbs(){
	this->x = this->worm->getXCenter();
	this->y = this->worm->getYCenter();
}



void AimView::draw(SDLScreen & screen){
	if(bDraw && bCoord){
		TextureManager::Instance().drawFrameOnScreen(
						"aim", this->xDraw, this->yDraw, 60, 57, 
						0, 0, screen.getRenderer(),
						false, SDL_FLIP_NONE);
		}
	else if(bDraw && bArrow){
		TextureManager::Instance().drawFrame(
						"aim", this->xDraw, this->yDraw, 60, 57, 
						0, 0, screen.getRenderer(),
						false, SDL_FLIP_NONE);
	}
}