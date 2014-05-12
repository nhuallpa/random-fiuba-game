#include "WormView.h"


WormView::WormView(int id)
	: View(0, 0), id(id), direction(SDL_FLIP_NONE), state(WORM_VIEW_MOTIONLESS)
{
	currentSprite = &this->spriteWalk;
	this->selected = false;
	this->gray = false;
}


WormView::~WormView(void)
{
}


void WormView::clean()
{

}

void WormView::update(GameElement* domainElement)
{
	std::pair<float, float> pointUL = domainElement->getPosition();
	tPoint pointSDL = TextureManager::Instance().convertPointUL2PXSDL(pointUL.first, pointUL.second);
	this->setX(pointSDL.x);
	this->setY(pointSDL.y);
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
	if (this->isSelected()) this->putGrey();
	else this->quitGrey();
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getX()-(currentSprite->getWidth()/2), 
										this->getY()-(currentSprite->getHeight()/2), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),this->gray, this->direction);
	strcpy(buffer,"Worm ");
	itoa(this->id,buffer2,10);
	strcat(buffer,buffer2);
	
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

bool WormView::isGrey(){ return this->gray;}
void WormView::putGrey(){ this->gray = true;}
void WormView::quitGrey(){this->gray = false;}


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
