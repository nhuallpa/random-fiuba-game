#ifndef __MENU_WEAPON_VIEW__
#define __MENU_WEAPON_VIEW__

#include "View.h"

class MenuWeaponView : public View{

public:
	MenuWeaponView(int x, int y);
	~MenuWeaponView();
	void draw(SDLScreen & screen);
};


#endif
