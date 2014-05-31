#include "WormView.h"


WormView::WormView(int id)
	: View(0, 0), id(id), direction(SDL_FLIP_NONE), state(WORM_VIEW_MOTIONLESS)
{
	currentSprite = &this->spriteWalk;
	this->selected = false;
	this->gray = false;
	this->color = COLOR_VERDE;
	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;

}

void WormView::setUserLabel(std::string text)
{
	labelUsuario.setText(text, white);
}

void WormView::setName(std::string text)
{
	labelNombre.setText(text, white);
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
	// ACTIONS
    if (domainElement->getAction() == MOVE_RIGHT ||
            domainElement->getAction() == MOVE_LEFT)
    {
            this->state = WORM_VIEW_DOING;
    } 
    else 
    {
            this->state = WORM_VIEW_MOTIONLESS;
    }
    // DIRECTION
    if (domainElement->getAction() == MOVELESS_RIGHT || 
            domainElement->getAction() == NOT_CONNECTED_RIGHT ||
            domainElement->getAction() == MOVE_RIGHT)
    {
            this->direction = SDL_FLIP_HORIZONTAL;
    } 
    else if (domainElement->getAction() == MOVELESS_LEFT || 
            domainElement->getAction() == NOT_CONNECTED_LEFT ||
            domainElement->getAction() == MOVE_LEFT)
    {
            this->direction = SDL_FLIP_NONE;        
    }

    if (domainElement->getAction() == MOVELESS)
    {
            this->state = WORM_VIEW_MOTIONLESS;
    }
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
	
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getXCenter(), 
										this->getYCenter(), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),
										this->gray, 
										this->direction);
	
	 
	if (this->isSelected())
	{
		labelUsuario.draw(screen.getRenderer(),this->getXCenter(), this->getYCenter()-9);
		labelNombre.draw(screen.getRenderer(),this->getXCenter(), this->getYCenter());
	}
	
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

void WormView::setColor(unsigned long color){
	this->color = color;
}

void WormView::setPlayer(std::string player){
	this->player = player;
}

std::string WormView::getPlayer(){
	return this->player;
}

int WormView::getXCenter()
{
	return this->getX()-(currentSprite->getWidth()/2);
}


int WormView::getYCenter()
{
	return this->getY()-(currentSprite->getHeight()/2);
}
