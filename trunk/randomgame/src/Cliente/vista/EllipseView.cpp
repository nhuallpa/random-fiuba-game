#include "EllipseView.h"


EllipseView::EllipseView(std::string  color): 
						FigureView(0,0,color,0)
{
	this->setRadioX(10);
	this->setRadioY(15);
}


EllipseView::~EllipseView(void)
{
}

void EllipseView::draw(SDLScreen & screen) 
{
	
	filledEllipseColor(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadioX(),
						this->getRadioY(),
						this->getColorCod());

	ellipseColor(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadioX(),
						this->getRadioY(),
						this->getBorderColorCod());

}

void EllipseView::update(GameElement* domainElement)
{
	this->updatePositions(domainElement->getPosition());
}

void EllipseView::updatePositions(std::pair<float, float> positions)
{

	std::pair<float, float> scale_factor = Util::getTransformFromU2PX();
	float factorX = scale_factor.first;
	float factorY = scale_factor.second;
			
	Log::t("Factor x y: [%f, %f]", factorX, factorY);

	int posX = positions.first * factorX;
	int posY = positions.second * factorY;
	
	this->setX(posX);
	this->setY(posY);
	Log::t("Posicion x y: [%dpx, %dpx]", posX, posY);
}

