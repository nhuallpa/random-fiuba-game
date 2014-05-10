#include "WormView.h"


WormView::WormView(int id, int x, int y)
	: View(x, y), id(id), direction(SDL_FLIP_NONE), state(WORM_VIEW_MOTIONLESS)
{
	currentSprite = &this->spriteWalk;
	this->selected = false;
}


WormView::~WormView(void)
{
}


void WormView::clean()
{

}
	
void WormView::update() 
{
	if (this->state == WORM_VIEW_DOING)
	{
		currentSprite->update();
	} 
	else if (this->state == WORM_VIEW_MOTIONLESS)
	{
		currentSprite->clean();
	}

	

}

void WormView::draw(SDLScreen & screen)
{ 
	
	char buffer[50];
	char buffer2[50];
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getX()-(currentSprite->getWidth()/2), 
										this->getY()-(currentSprite->getHeight()/2), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(), this->direction);
	strcpy(buffer,"Worm ");
	itoa(this->id,buffer2,10);
	strcat(buffer,buffer2);
	
	TextureManager::Instance().drawText(screen.getRenderer(),this->getX(),this->getY(),"+",0xFF00FF00);
	if (this->isSelected())
		TextureManager::Instance().drawText(screen.getRenderer(),this->getX()-(currentSprite->getWidth()/2),this->getY()-(currentSprite->getHeight()/2),buffer,0xFFFFFFFF);

}

bool WormView::isSelected(){
	return this->selected;
}

void WormView::select(){
	this->selected = true;
}
void WormView::deselect(){
	this->selected = false;
}

void WormView::OnMovement(MovementEvent e){


	if (e.x == 1) // derecha
	{
		this->state = WORM_VIEW_DOING;
		this->direction = SDL_FLIP_HORIZONTAL;
	}
	else if (e.x == -1) // izquierda
	{
		this->state = WORM_VIEW_DOING;
		this->direction = SDL_FLIP_NONE;
	} 
	else if (e.x == 0) // quieto
	{
		this->state = WORM_VIEW_MOTIONLESS;
	}

}
