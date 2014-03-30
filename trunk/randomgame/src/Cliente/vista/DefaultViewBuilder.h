#pragma once
#ifndef __DEFAULT_VIEW_BUILDER_H__
#define __DEFAULT_VIEW_BUILDER_H__
#include "FigureView.h"
#include "SkyView.h"
#include "ViewGroup.h"
#include "WaterView.h"
#include "RectangleView.h"
#include "PolygonView.h"
#include "CircleView.h"
#include "ViewBuilder.h"

class DefaultViewBuilder :	public ViewBuilder
{
public:
	DefaultViewBuilder(void);
	~DefaultViewBuilder(void);

	ViewGroup* buildContainer();

	void buildSky(ViewGroup* container);

	void buildFigures(ViewGroup* container);

	void buildWater(ViewGroup* container);
};

#endif /**__DEFAULT_VIEW_BUILDER_H__*/
