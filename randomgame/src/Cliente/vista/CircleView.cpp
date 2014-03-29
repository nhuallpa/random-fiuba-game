#include "CircleView.h"


CircleView::CircleView(int x, int y, int radio, Uint32 color, int rotation): 
								FigureView(x,y,color,rotation)
{
	this->setRadio(radio);
}


CircleView::~CircleView(void)
{
}

void CircleView::draw(SDLScreen & screen) 
{
	aacircleColor(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadio(),
						this->getColor());

	filledCircleColor(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadio(),
						this->getColor());
}
