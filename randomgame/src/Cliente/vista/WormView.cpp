#include "WormView.h"


WormView::WormView(int id, int x, int y)
	: View(x, y), id(id)
{
	currentSprite = &this->spriteWalk;
	this->selected = false;
}

WormView::WormView(int id, int x, int y,std::string playerID)
	: View(x, y), id(id)
{
	currentSprite = &this->spriteWalk;
	this->selected = false;
	this->playerID = playerID;
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
	Uint32 color;// = 0xFF3ADF00;
	if (this->playerID.compare("PLAYER 1") == 0) color = VERDE;
	else if (this->playerID.compare("PLAYER 2")== 0) color = AMARILLO;
	else if (this->playerID.compare("PLAYER 3")== 0) color = CELESTE;
	else if (this->playerID.compare("PLAYER 4")==0) color = VIOLETA;

	
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
	strcpy(buffer,this->playerID.c_str());
	itoa(this->id,buffer2,10);
	strcat(buffer,buffer2);
	if (this->isSelected())
		TextureManager::Instance().drawText(screen.getRenderer(),this->getX(),this->getY(),buffer,color);

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

}