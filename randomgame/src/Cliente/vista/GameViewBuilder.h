#pragma once
#ifndef __GAME_VIEW_BUILDER_H__
#define __GAME_VIEW_BUILDER_H__
#include "SkyView.h"
#include "ViewGroup.h"
#include "WaterView.h"
#include "RectangleView.h"
#include "PolygonView.h"
#include "CircleView.h"
#include "TriangleView.h"
#include "TerrainView.h"
#include "ViewBuilder.h"
#include "../../Servidor/modelo/GameElement.h"

class GameViewBuilder :
	public ViewBuilder
{
	std::map<int,GameElement> domainElements;

public:

	GameViewBuilder(const std::map<int,GameElement>& map);
	~GameViewBuilder(void);

	
	ViewGroup* buildContainer();

	void buildSky(ViewGroup* container);

	void buildFigures(ViewGroup* container);

	void buildWater(ViewGroup* container);

	void buildTerrain(ViewGroup* container);
};

#endif /**__GAME_VIEW_BUILDER_H__*/