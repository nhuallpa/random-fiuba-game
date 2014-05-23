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

	GameController* cController;
	GameViewBuilder* builder;
	
	std::string playerId;

	/*para calcular el zoom*/
	int wormIdSelected;
	void calcRectPosition(SDL_Rect& wormRect,WormView *aWorm);

public:

	GameActivity(SDLScreen & screen, GameViewBuilder & builder, GameController* cController, std::string playerId);

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

	void buildNewWorms(std::string playerID, int id, int x, int y) ;

	bool isThisClientOwner(int wormId);

	bool isAlive(int wormId);

	void setMessageView(std::string msg);

	void showMessageError(std::string msg);

	void showMessageInfo(std::string msg);

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

