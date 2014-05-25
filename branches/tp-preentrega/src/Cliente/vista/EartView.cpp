#include "EartView.h"


EartView::EartView(std::string imageId):View(0, 0), imageId(imageId)
{
	this->counter = 0;
	convertToStreamTexture();
}


EartView::~EartView(void)
{

}

void EartView::draw(SDLScreen & screen)
{
	if (this->counter > 300)
	{
		this->drawExplotion(200, 200, 30);
	}
	
	TextureManager::Instance().drawScrollableBackground(imageId, screen.getRenderer());
}

void EartView::drawExplotion(int x, int y, int radius)
{

}

void EartView::convertToStreamTexture()
{

}