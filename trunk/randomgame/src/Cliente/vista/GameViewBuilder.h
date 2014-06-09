#pragma once
#ifndef __GAME_VIEW_BUILDER_H__
#define __GAME_VIEW_BUILDER_H__
#include "SkyView.h"
#include "ViewGroup.h"
#include "GameView.h"
#include "FigureViewGroup.h"
#include "WaterView.h"
#include "RectangleView.h"
#include "PentagonView.h"
#include "HexagonView.h"
#include "PolygonView.h"
#include "CircleView.h"
#include "EllipseView.h"
#include "TriangleView.h"
#include "TerrainView.h"
#include "WormView.h"
#include "ProjectileView.h"
#include "MenuWeaponView.h"
#include "EartView.h"
#include "SDLScreen.h"
#include "SpriteConfigurator.h"
#include "../../utils/Util.h"
#include "../../utils/Constantes/Constantes.h"
#include "../controlador/GameController.h"
#include "../modelo/GameDomain.h"

class GameViewBuilder 
{
	
	GameView* gameView;
	
	SDLScreen * screen;

	std::string playerID;

	GameDomain* domain;


	

public:

	GameDomain* getDomain(){ return this->domain;}

	GameViewBuilder(GameDomain* domain, SDLScreen * screen);
	~GameViewBuilder(void);

	std::string getPlayerID() { return this->playerID; }

	WormView* createWorm(GameElement * domainElement);

	ProjectileView* createBullet(GameElement * domainElement);

	void setPlayerID(std::string  playerID){ this->playerID = playerID; }
	
	void buildContainer();

	void buildProjectileContainer();

	void buildSky();

	void buildFigures();

	void buildWater();

	void buildTerrain();

	void buildCharacters();

	void buildEart();

	void buildStateBar();

	void buildMenuWeapon();

	

	GameView* getGameView() { return this->gameView;} 

};

#endif /**__GAME_VIEW_BUILDER_H__*/