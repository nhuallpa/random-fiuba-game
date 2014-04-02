#include "RectangleView.h"


RectangleView::RectangleView(std::string  color): FigureView(0,0,color,0)
{
	init();
}
void RectangleView::init()
{
	vertexA.x = 0;
	vertexA.y = 0;
	vertexB.x = 0;
	vertexB.y = 0;
	vertexC.x = 0;
	vertexC.x = 0;
	vertexD.y = 0;
	vertexD.y = 0;
}

/**DEPRECATED*/
RectangleView::RectangleView(int x, int y, int width, int height, std::string  color, int rotation):
								FigureView(x,y,color,rotation)
{
	this->setWidth(width);
	this->setHeight(height);
	init();
}


RectangleView::~RectangleView(void)
{
}


void RectangleView::draw(SDLScreen & screen)
{
	vertexX[0] = vertexA.x;
	vertexX[1] = vertexB.x;
	vertexX[2] = vertexC.x;
	vertexX[3] = vertexD.x;
	vertexY[0] = vertexA.y;
	vertexY[1] = vertexB.y;
	vertexY[2] = vertexC.y;
	vertexY[3] = vertexD.y;
	
	filledPolygonColor(screen.getRenderer(),
				vertexX,
				vertexY,
				4,
				this->getColorCod());
	polygonColor(screen.getRenderer(),
				vertexX,
				vertexY,
				4,
				this->getBorderColorCod());


	/* Only draw a rectangule without rotation
	tPoint vertex1;
	tPoint vertex2;

	vertex1.x = (-1)*(this->getWidth() / 2);
	vertex1.y = (this->getWidth() / 2);
	vertex2.x = (this->getWidth() / 2);
	vertex2.y = (-1)*(this->getWidth() / 2);

	boxColor(screen.getRenderer(), 
					this->getX() + vertex1.x, 
					this->getY() + vertex1.y,					
					this->getX() + vertex2.x,
					this->getY() + vertex2.y, 
					this->getColorCod());
	*/

}

void RectangleView::setVertexA(int x, int y)
{
	this->vertexA.x = x;
	this->vertexA.y = y;
}
void RectangleView::setVertexB(int x, int y)
{
	this->vertexB.x = x;
	this->vertexB.y = y;
}
void RectangleView::setVertexC(int x, int y)
{
	this->vertexC.x = x;
	this->vertexC.y = y;
}

void RectangleView::setVertexD(int x, int y)
{
	this->vertexD.x = x;
	this->vertexD.y = y;
}
