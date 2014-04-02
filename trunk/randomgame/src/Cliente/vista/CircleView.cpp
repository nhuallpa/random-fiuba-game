#include "CircleView.h"


CircleView::CircleView(int x, int y, int radio, std::string  color, int rotation): 
								FigureView(x,y,color,rotation)
{
	this->setRadio(radio);
}


CircleView::~CircleView(void)
{
}

void CircleView::draw(SDLScreen & screen) 
{
	
	
	filledCircleColor(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadio(),
						this->getColorCod());

	aacircleColor(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadio(),
						this->getBorderColorCod());

}
