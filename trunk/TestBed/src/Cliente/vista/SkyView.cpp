#include "SkyView.h"


SkyView::SkyView(std::string imageId)
				: View(0, 0), imageId(imageId)
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
