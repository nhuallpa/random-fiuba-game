#include "RectangleView.h"


RectangleView::RectangleView(int x, int y, int width, int height, Uint32 color, int rotation):
								FigureView(x,y,color,rotation)
{
	this->setWidth(width);
	this->setHeight(height);
}


RectangleView::~RectangleView(void)
{
}


void RectangleView::draw(SDLScreen & screen)
{
	boxColor(screen.getRenderer(), 
					this->getX(), 
					this->getY(),					
					this->getX() + this->getWidth(),
					this->getY() + this->getHeight(), 
					this->getColor());
}