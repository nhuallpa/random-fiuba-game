#pragma once

#ifndef __PLAYER_PROGRESS_VIEW_H__
#define __PLAYER_PROGRESS_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "../../utils/Constantes/Colors.h"
class PlayerProgressView: public View
{
protected:

public:
	PlayerProgressView();

	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	~PlayerProgressView(void);

};

#endif /** __PLAYER_PROGRESS_VIEW_H__ **/