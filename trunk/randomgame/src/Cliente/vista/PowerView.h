#pragma once

#ifndef __POWER_VIEW_H__
#define __POWER_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "../../utils/Constantes/Colors.h"
class PowerView: public View
{
private:

	TextView label;

public:
	PowerView(int x, int y);

	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	~PowerView(void);

};

#endif /** __POWER_VIEW_H__ **/