#pragma once
#ifndef __GAME_ACTIVITY_H_
#define __GAME_ACTIVITY_H_
#include <iostream>
#include "Activity.h"
#include "GameViewBuilder.h"

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

public:
//	GameActivity(const SDLScreen & screen, GameViewBuilder & builder, GameLevel * cLevel, GameController* cController);

	GameActivity(SDLScreen & screen, GameViewBuilder & builder, GameController* cController);

	void buildView( GameViewBuilder & builder);

	void update();

	void onCreate();

	void setListeners(SDLScreen & screen);

	void OnClick(ClickEvent e);

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */
