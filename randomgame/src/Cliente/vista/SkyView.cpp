#include "SkyView.h"


SkyView::SkyView(std::string imageId, int x, int y, int width, int height)
							: View(x, y, width, height), imageId(imageId)
{
}


SkyView::~SkyView(void)
{
}


void SkyView::clean()
{

}
	
void SkyView::update() 
{

}

void SkyView::draw(SDLScreen & screen)
{
	TextureManager::Instance().drawBackground(imageId.c_str(),
								screen.getRenderer());

}
