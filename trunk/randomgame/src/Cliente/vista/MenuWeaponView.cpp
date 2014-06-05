#include "MenuWeaponView.h"
#include "TextureManager.h"


MenuWeaponView::MenuWeaponView(int x, int y)
	:View(x,y){

}


MenuWeaponView::~MenuWeaponView(){

}

void MenuWeaponView::buildWeapon(){

	//creo el menu WeaponId=NO_WEAPON, debo registrar la url
	Weapon* menu = new Weapon(NO_WEAPON,30,30,267,214);
	menu->setWeapon(ENABLE,"MenuWeapon");
	menu->setState(ENABLE);
	//menu->setRender(false);
	mapa.insert(pair<WeaponId, Weapon*>(NO_WEAPON,menu));
}


void MenuWeaponView::actionMenu(){
	Weapon* menu = mapa[NO_WEAPON];
	menu->setRender();
}

void MenuWeaponView::draw(SDLScreen & screen){
	
	map<WeaponId, Weapon*>::iterator it;
	for(it = mapa.begin(); it != mapa.end(); it++){
		it->second->draw(screen);
	}


	//TextureManager::Instance().drawFrameOnScreen("MenuWeapon", 
	//								30, 
	//								30, 
	//								267, 
	//								214, 
	//								0, 
	//								0, 
	//								screen.getRenderer(),
	//								false, 
	//								SDL_FLIP_NONE);
	

	//screen.setTarget(2);


	//screen.setTarget(1);
}