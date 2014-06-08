#include "MenuWeaponView.h"
#include "TextureManager.h"
#include "..\controlador\Entity\Shape.h"
#include <list>

#define X_MENU 400
#define Y_MENU 20
#define WIDTH_WEAPON  32
#define HEIGHT_WEAPON 32

MenuWeaponView::MenuWeaponView(int x, int y)
	:View(x,y){

}


MenuWeaponView::~MenuWeaponView(){

}


void MenuWeaponView::actionMenu(){
	if(menu->findWeapon("MenuWeapon")){
		menu->removeWeapon("MenuWeapon");
	}
	else{
		menu->setWeapon("MenuWeapon");
	}
}

void MenuWeaponView::draw(SDLScreen & screen){
	
	if(menu->findWeapon("MenuWeapon")){
		menu->draw(screen);
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			it->second->draw(screen);
		}
	}
	else{

	}


}


void MenuWeaponView::allowWeapon(list<WeaponId> items){
	list<WeaponId>::iterator it;
	map<WeaponId, Weapon*>::iterator it2;

	for(it = items.begin();
		it != items.end();
		it++){
		it2 = mapa.find((*it));
		if(it2 != mapa.end()){
			it2->second->allow();
		}
	}

}


bool MenuWeaponView::hasClickedMenu(SDL_Point clickPoint){
	bool result = false;
	if(menu->findWeapon("MenuWeapon")
	&& (menu->hasClickedMenu(clickPoint))){
		result = true;
	}
	return result;
}

bool MenuWeaponView::hasClickedWeapon(SDL_Point clickPoint){
	bool result = false;
	if(menu->findWeapon("MenuWeapon")){
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			if(it->second->hasClickedMenu(clickPoint)){
				result = true;
				break;
			}
		}
	}
	return result;
}


Weapon* MenuWeaponView::retrieveWeaponClicked(SDL_Point clickPoint){
	Weapon* result = NULL;
	if(menu->findWeapon("MenuWeapon")){
		map<WeaponId, Weapon*>::iterator it;
		for(it = mapa.begin(); it != mapa.end(); it++){
			if(it->second->hasClickedMenu(clickPoint)){
				result = it->second;
				break;
			}
		}
	}
	return result;
}

Weapon* MenuWeaponView::findWeaponById(int idWeapon){
	Weapon* result = NULL;
	WeaponId key = (WeaponId) idWeapon;
	map<WeaponId, Weapon*>::iterator it;
	it = mapa.find(key);
	if(it != mapa.end()){
		result = it->second;
	}
	return result;
}


void MenuWeaponView::buildWeapon(){
	int x, y;
	Shape *shape = NULL;
	list<string> lweapons;
	Weapon * weapon;

	x = X_MENU;
	y = Y_MENU;

	shape = new Shape(x, y, 280, 214);
	if(shape != NULL){
		//lweapons.push_back("MenuWeapon");
		menu = new Weapon(NO_WEAPON, *shape, lweapons, "");
		delete shape;
	}

	x += 10;
	y += 25;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("bazooka.1.2");
		weapon = new Weapon(BAZOOKA, *shape, lweapons, "bazooka.1.1");
		mapa.insert(pair<WeaponId, Weapon*>(BAZOOKA,weapon));
		delete shape;
	}

	x += WIDTH_WEAPON;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("grenade.1.2");
		weapon = new Weapon(GRENADE, *shape, lweapons, "grenade.1.1");
		mapa.insert(pair<WeaponId, Weapon*>(GRENADE,weapon));
		delete shape;
	}
	
	x += WIDTH_WEAPON;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("hgrenade.1.2");
		weapon = new Weapon(HOLY, *shape, lweapons, "hgrenade.1.1");
		mapa.insert(pair<WeaponId, Weapon*>(HOLY,weapon));
		delete shape;
	}

	x += WIDTH_WEAPON;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("donkey.1.2");
		weapon = new Weapon(BURRO, *shape, lweapons, "donkey.1.1");
		mapa.insert(pair<WeaponId, Weapon*>(BURRO,weapon));
		delete shape;
	}


	x += WIDTH_WEAPON;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("dynamite.1.2");
		weapon = new Weapon(DYNAMITE, *shape, lweapons, "dynamite.1.1");
		mapa.insert(pair<WeaponId, Weapon*>(DYNAMITE,weapon));
		delete shape;
	}


	x += WIDTH_WEAPON;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("airstrke.1.2");
		weapon = new Weapon(AIRATTACK, *shape, lweapons, "airstrke.1.1");
		mapa.insert(pair<WeaponId, Weapon*>(AIRATTACK,weapon));
		delete shape;
	}


	x += WIDTH_WEAPON;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("banana.1.2");
		weapon = new Weapon(BANANA, *shape, lweapons, "banana.1.1");
		mapa.insert(pair<WeaponId, Weapon*>(BANANA,weapon));
		delete shape;
	}


	x += WIDTH_WEAPON;
	lweapons.clear();

	shape = new Shape(x, y, WIDTH_WEAPON, HEIGHT_WEAPON);
	if(shape != NULL){
		lweapons.push_back("hmissile.1.2");
		weapon = new Weapon(HMISSILE, *shape, lweapons, "hmissile.1.2");
		mapa.insert(pair<WeaponId, Weapon*>(HMISSILE,weapon));
		delete shape;
	}

}

