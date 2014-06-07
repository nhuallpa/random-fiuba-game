#include "Weapon.h"
#include "TextureManager.h"
#include <algorithm>


Weapon::Weapon(WeaponId id, Shape s, list<string> keys)
:View(x,y){
	pair<int, int> data;
	this->id = id;
	data = s.getPosition();
	this->x = data.first;
	this->y = data.second;
	data = s.getDimension();
	this->width = data.first;
	this->height = data.second;
	lWeaponView.insert(lWeaponView.begin(),
					   keys.begin(),
					   keys.end());
}

Weapon::~Weapon(){

}

void Weapon::setWeapon(string key){
	lWeaponView.push_back(key);
}

void Weapon::removeWeapon(string key){
	list<string>::iterator it;
	it = find(lWeaponView.begin(), 
		      lWeaponView.end(), key);
	if(it != lWeaponView.end()){
		lWeaponView.erase(it);
	}
}

bool Weapon::findWeapon(string key){
	list<string>::iterator it;
	it = find(lWeaponView.begin(), 
		      lWeaponView.end(), key);
	return (it != lWeaponView.end());
}

void Weapon::draw(SDLScreen & screen){
	drawItems(screen);
}

void Weapon::drawItems(SDLScreen & screen){
	list<string>::iterator it;
	for(it  = lWeaponView.begin();
		it != lWeaponView.end();
		it++){
		TextureManager::Instance().drawFrameOnScreen(
					(*it), x, y, width, height, 
					0, 0, screen.getRenderer(),
					false, SDL_FLIP_NONE);
	}

}


