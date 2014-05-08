#include "WormView.h"


WormView::WormView(int id, int x, int y)
	: View(x, y), id(id)
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
	if (this->isSelected())
		TextureManager::Instance().drawText(screen.getRenderer(),this->getX(),this->getY(),buffer,0xFFFFFFFF);

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

	//aca tienen que llamar al metodo del cliente addLocalMovementFromView() pasandome 
	//el wormID y el Move que hacen (izq,der,salto,..etc)

	Playable p;

	//p.action = 	MOVE_RIGHT - MOVE_LEFT -  JUMP - 
	p.wormid = this->id;

	// aca llaman al cliente: Cliente -> addLocalMovementFromView(p);

}