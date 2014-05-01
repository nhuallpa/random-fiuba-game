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
	
	char buffer[50];
	char buffer2[50];
	
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getX(), 
										this->getY(), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(), SDL_FLIP_HORIZONTAL);
	strcpy(buffer,"Worm ");
	itoa(this->id,buffer2,10);
	strcat(buffer,buffer2);
	TextureManager::Instance().drawText(screen.getRenderer(),this->getX(),this->getY(),buffer,0xFFFFFFFF);

}