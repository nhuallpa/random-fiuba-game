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
	Sint16* vertexX = new Sint16[m_points.size()];
	Sint16* vertexY = new Sint16[m_points.size()];

	std::list<tPoint>::iterator  it;

	int index=0;
	for (it = m_points.begin(); it != m_points.end(); ++it)  
	{
		vertexX[index] = (*it).x;
		vertexY[index] = (*it).y;
	}

	polygonColor(screen.getRenderer(),
				vertexX,
				vertexY,
				m_points.size(),
				this->getColor());

	delete [] vertexX;
	delete [] vertexY;
}

PolygonView::~PolygonView(void)
{
}
