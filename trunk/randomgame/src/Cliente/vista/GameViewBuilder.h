#pragma once
#ifndef __GAME_VIEW_BUILDER_H__
#define __GAME_VIEW_BUILDER_H__
#include "SkyView.h"
#include "ViewGroup.h"
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
#include "ViewBuilder.h"
#include "../../utils/Util.h"
#include "../../Servidor/modelo/GameElement.h"
#include "../../Servidor/modelo/GameLevel.h"

class GameViewBuilder :
	public ViewBuilder
{
	
	GameLevel* cLevel;

public:

	GameViewBuilder(GameLevel * cLevel);
	~GameViewBuilder(void);

	
	ViewGroup* buildContainer();

	FigureViewGroup* buildFigureContainer();

	void buildSky(ViewGroup* container);

	void buildFigures(FigureViewGroup* container);

	void buildWater(ViewGroup* container);

	void buildTerrain(ViewGroup* container);
};

#endif /**__GAME_VIEW_BUILDER_H__*/