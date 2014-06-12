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
	//sprites["nuve"].clean();
}

void SkyView::draw(SDLScreen & screen)
{
	TextureManager::Instance().drawBackground(imageId.c_str(),
								screen.getRenderer());

	Sprite* currentSprite = &sprites["nuve"];
	TextureManager::Instance().drawFrame("nuve", 
										50, 
										50, 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer());

	TextureManager::Instance().drawFrame("nuve", 
										500, 
										50, 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer());

	TextureManager::Instance().drawFrame("nuve", 
										700, 
										50, 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer());

}
