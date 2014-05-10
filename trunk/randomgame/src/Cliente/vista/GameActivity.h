#pragma once
#ifndef __GAME_ACTIVITY_H_
#define __GAME_ACTIVITY_H_
#include <iostream>
#include "Activity.h"
#include "GameViewBuilder.h"
#include "TextureManager.h"

#include "../../Servidor/modelo/GameLevel.h"
#include <SDL_rect.h>
#include "../../utils/Util.h"
#include "Camera.h"

class GameActivity : public Activity, public OnClickListener
{
private:
	//GameLevel* cLevel;
	//std::map<int,GameElement*> domainElements;
	GameController* cController;
	GameViewBuilder* builder;
	
	/*para calcular el zoom*/


	int wormIdSelected;
	void calcRectPosition(SDL_Rect& wormRect,WormView *aWorm);

public:
//	GameActivity(const SDLScreen & screen, GameViewBuilder & builder, GameLevel * cLevel, GameController* cController);

	GameActivity(SDLScreen & screen, GameViewBuilder & builder, GameController* cController);

	void buildView( GameViewBuilder & builder);

	void update();

	void onCreate();

	void setListeners(SDLScreen & screen);

	void OnClick(ClickEvent e);

	void deselectPreviewsWorm();

	void selectWorm(WormView* aWorm);

	bool hasClickedWorm(SDL_Point clickPoint);

	int getWormIdSelected() {return this->wormIdSelected;}

	WormView* retrieveWormClicked(SDL_Point clickPoint);

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

