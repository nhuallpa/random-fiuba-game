#include "EartView.h"


EartView::EartView(std::string imageId):View(0, 0), imageId(imageId)
{
}


EartView::~EartView(void)
{

}

void EartView::draw(SDLScreen & screen)
{
	TextureManager::Instance().drawImageOffset(imageId, 0,0,
												screen.getWidth(), screen.getHeight(),
												screen.getRenderer());
}
