#include "EartView.h"


EartView::EartView(std::string imageId):View(0, 0), imageId(imageId)
{
	this->counter = 0;
}


EartView::~EartView(void)
{

}

void EartView::draw(SDLScreen & screen)
{
	if (this->counter > 50)
	{
		this->counter = 0;
		this->drawExplotion(200, 200, 30);
	}
	this->counter++;
	TextureManager::Instance().drawScrollableBackground(imageId, screen.getRenderer());
}

void EartView::drawExplotion(int x, int y, int radius)
{

	Uint32 pixel = 0x00000000;
	TextureManager::Instance().fillCircleOn(this->imageId, x, y, radius, pixel);
}
