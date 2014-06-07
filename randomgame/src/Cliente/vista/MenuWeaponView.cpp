#include "MenuWeaponView.h"
#include "TextureManager.h"
#include "..\controlador\Entity\Shape.h"
#include <list>

#define WIDTH_MENU 30
#define HEIGHT_MENU 30

MenuWeaponView::MenuWeaponView(int x, int y)
	:View(x,y){

}


MenuWeaponView::~MenuWeaponView(){

}

void MenuWeaponView::buildWeapon(){

	//creo el menu WeaponId=NO_WEAPON, debo registrar la url
	//creo una forma
	Shape menuShape(WIDTH_MENU,HEIGHT_MENU,267,214);
	list<string> lweapons;
	lweapons.push_back("MenuWeapon");
	menu = new Weapon(NO_WEAPON, menuShape, lweapons);

	//mapa.insert(pair<WeaponId, Weapon*>(NO_WEAPON,menu));
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