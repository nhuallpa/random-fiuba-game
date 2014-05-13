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
#include "EartView.h"
#include "SpriteConfigurator.h"
#include "../../utils/Util.h"
#include "../../utils/Constantes/Constantes.h"
#include "../controlador/GameController.h"
#include "../modelo/GameDomain.h"

class GameViewBuilder 
{
	
	//GameLevel* cLevel;
	GameView* gameView;
	
	// Worm ID, (X,Y)
	//std::map<int,GameElement> domainElements;

	std::string playerID;

	GameController* cController;

	GameDomain* domain;


	WormView* createWorm(GameElement * domainElement);

public:

	GameDomain* getDomain(){ return this->domain;}

	//GameViewBuilder(GameLevel * cLevel);
	GameViewBuilder(GameController* cController, GameDomain* domain);
	~GameViewBuilder(void);

	std::string getPlayerID() { return this->playerID; }
	void setPlayerID(std::string  playerID){ this->playerID = playerID; }
	
	void buildContainer();

	void buildSky();

	void buildFigures();

	void buildWater();

	void buildTerrain();

	void buildCharacters();

	void buildEart();

	void buildStateBar();

	//void addElementToDomain(GameElement worm);

//	std::map<int,GameElement>* getDomainElements() { return &this->domainElements;}

	GameView* getGameView() { return this->gameView;} 

};

#endif /**__GAME_VIEW_BUILDER_H__*/