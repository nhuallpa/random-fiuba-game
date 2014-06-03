#include "MenuWeaponView.h"
#include "TextureManager.h"


MenuWeaponView::MenuWeaponView(int x, int y)
	:View(x,y){

}


MenuWeaponView::~MenuWeaponView(){

}

void MenuWeaponView::draw(SDLScreen & screen){
	TextureManager::Instance().drawFrameOnScreen("gun_1", 
									30, 
									30, 
									50, 
									50, 
									0, 
									0, 
									screen.getRenderer(),
									false, 
									SDL_FLIP_NONE);
}