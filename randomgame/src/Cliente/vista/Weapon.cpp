#include "Weapon.h"
#include "TextureManager.h"


Weapon::Weapon(WeaponId id, int x, int y, int width, int height)
:View(x,y){
	this->id = id, this->x = x, this->y = y;
	this->width = width, this->height = height;
	this->render = true;
}

Weapon::~Weapon(){

}


void Weapon::setRender(){
	if(this->render){
		//Log::e("Erik, NO Dibujo Notificacion");
		this->render = false;
	}
	else{
		//Log::e("Erik, Dibujo Notificacion");
		this->render = true;
	}
}

void Weapon::setState(WSTATE ws){
	this->state = ws;
}

void Weapon::setWeapon(WSTATE ws, string ref){
	this->weapons.insert(pair<WSTATE, string>(ws, ref));
}

string Weapon::getWeapon(WSTATE ws){
	map<WSTATE, string>::iterator it;
	it = this->weapons.find(ws);
	if(it != this->weapons.end()){
		return it->second;
	}
	return "";
}


void Weapon::draw(SDLScreen & screen){

	if(!this->render){
		return;
	}
	TextureManager::Instance().drawFrameOnScreen(
					this->weapons[this->state], 
					this->x, 
					this->y, 
					this->width, 
					this->height, 
					0, 
					0, 
					screen.getRenderer(),
					false, 
					SDL_FLIP_NONE);
}
