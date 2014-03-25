#include "WaterView.h"


WaterView::WaterView(std::string imageId, int x, int y, int width, int height)
							: View(x, y, width, height), imageId(imageId)
{
}


WaterView::~WaterView(void)
{
}


void WaterView::clean()
{

}
	
void WaterView::update() 
{

}

void WaterView::draw(SDLScreen & screen)
{
	TextureManager::Instance().draw(imageId.c_str(),
								this->getX(),
								this->getY(),
								this->getWidth(),
								this->getHeight(),
								screen.getRenderer());

}

