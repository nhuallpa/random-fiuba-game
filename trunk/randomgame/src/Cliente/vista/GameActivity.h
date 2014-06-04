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
#include "../Updater.h"


class GameActivity : public Activity, 
					 public OnClickListener, 
					 public OnMovementListener,
					 public OnActionListener
{
private:

	GameController* cController;
	GameViewBuilder* builder;

	Updater updater;
	
	std::string playerId;

	/*para calcular el zoom*/
	void calcRectPosition(SDL_Rect& wormRect,WormView *aWorm);

	bool isMyTurn;

public:

	int wormIdDesSelected;
	int wormIdSelected;

	GameActivity(SDLScreen & screen, GameDomain* domain, GameController* cController, std::string playerId, Updater & updater);

	void buildView( GameViewBuilder* builder);

	void stop();

	void clear();

	void update();

	void onCreate();

	void setListeners(SDLScreen & screen);

	void OnClick(ClickEvent e);

	void OnMovement(MovementEvent e);

	void OnAction(ActionEvent e);

	void deselectPreviewsWorm();

	void doExplotion(float x, float y, float radio);

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

	void otherTurn(std::string playerId);

	void endMyTurn();

	void beginMyTurn();

	

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

