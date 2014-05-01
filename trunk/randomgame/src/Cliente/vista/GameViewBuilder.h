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
#include "../../Servidor/modelo/GameElement.h"
#include "../../Servidor/modelo/GameLevel.h"

class GameViewBuilder 
{
	
	GameLevel* cLevel;
	GameView* gameView;

public:

	GameViewBuilder(GameLevel * cLevel);
	~GameViewBuilder(void);

	
	void buildContainer();

	void buildSky();

	void buildFigures();

	void buildWater();

	void buildTerrain();

	void buildCharacters();

	void buildEart();

	GameView* getGameView() { return this->gameView;} 
};

#endif /**__GAME_VIEW_BUILDER_H__*/