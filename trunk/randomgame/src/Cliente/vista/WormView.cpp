#include "WormView.h"


WormView::WormView(int id)
	: View(0, 0), id(id), direction(SDL_FLIP_NONE), state(WORM_VIEW_MOTIONLESS)
{
	currentSprite = &this->spriteWalk;
	this->selected = false;
	this->gray = false;
	this->color = COLOR_VERDE;
}

void WormView::setUserLabel(std::string text, SDL_Renderer* renderer, TTF_Font* font)
{
	
	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;

	green.a = 0xFF;
	green.r = 0x00;
	green.g = 0xFF;
	green.b = 0x00;
	

	labelUsuario.loadFromRenderedText(text, white, renderer,  font);
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
	char buffer3[50];
	/*if (this->isSelected()) 
		this->putGrey();
	else 
		this->quitGrey();*/
	
	strcpy(buffer3,this->player.c_str());

	strcpy(buffer,"Worm ");
	itoa(this->id,buffer2,10);
	strcat(buffer,buffer2);

	
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
		/*TextureManager::Instance().drawText(screen.getRenderer(),this->getXCenter(),this->getYCenter() - 8,buffer3,0xFFFFFFFF);
		TextureManager::Instance().drawText(screen.getRenderer(),this->getXCenter(),this->getYCenter(),buffer,0xFFFFFFFF);*/
		labelUsuario.setColor(green.r,green.g,green.b);
	}
	else
	{
		/*TextureManager::Instance().drawText(screen.getRenderer(),this->getXCenter(),this->getYCenter() - 8,buffer3,this->color);
		TextureManager::Instance().drawText(screen.getRenderer(),this->getXCenter(),this->getYCenter(),buffer,this->color);*/
		labelUsuario.setColor(white.r,white.g,white.b);
	}

	labelUsuario.draw(screen.getRenderer(),this->getXCenter(), this->getYCenter());
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

int WormView::getXCenter()
{
	return this->getX()-(currentSprite->getWidth()/2);
}


int WormView::getYCenter()
{
	return this->getY()-(currentSprite->getHeight()/2);
}
