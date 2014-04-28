#include "WormView.h"


WormView::WormView(int id, int x, int y)
	: View(x, y), id(id)
{
	currentSprite = &this->spriteWalk;
}


WormView::~WormView(void)
{
}


void WormView::clean()
{

}
	
void WormView::update() 
{
	currentSprite->update();
}

void WormView::draw(SDLScreen & screen)
{
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getX(), 
										this->getY(), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(), SDL_FLIP_HORIZONTAL);

}
