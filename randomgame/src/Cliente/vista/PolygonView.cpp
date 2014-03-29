#include "PolygonView.h"


PolygonView::PolygonView(int x, int y, Uint32 color, int rotation)
								: FigureView(x,y,color,rotation)
{
}

void PolygonView::addPoint(int x, int y)
{
	tPoint newPoint;
	newPoint.x = x;
	newPoint.y = y;
	m_points.push_back(newPoint);
}

void PolygonView::draw(SDLScreen & screen) 
{

}

PolygonView::~PolygonView(void)
{
}
