#pragma once
#ifndef __POLYGON_VIEW_H_
#define __POLYGON_VIEW_H_
#include <list>
#include "FigureView.h"
class PolygonView :	public FigureView
{
	std::list<tPoint> m_points;

public:
	PolygonView(int x, int y, Uint32 color, int rotation);

	void addPoint(int x, int y);

	void draw(SDLScreen & screen);


	~PolygonView(void);
};

#endif /**__POLYGON_VIEW_H_*/