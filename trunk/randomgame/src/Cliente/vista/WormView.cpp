#include "WormView.h"


WormView::WormView(int id)
	: View(0, 0), id(id), direction(SDL_FLIP_NONE), state(WORM_VIEW_MOTIONLESS)
{
	currentSprite = NULL;
	this->selected = false;
	this->gray = false;
	this->color = COLOR_VERDE;
	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	this->weaponId = NO_WEAPON;
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

void WormView::selectWeapon(WeaponId idWapon)
{
	this->weaponId = idWapon;
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
			// todo: estado derecha
            this->direction = SDL_FLIP_HORIZONTAL;
    } 
    else if (domainElement->getAction() == MOVELESS_LEFT || 
            domainElement->getAction() == NOT_CONNECTED_LEFT ||
            domainElement->getAction() == MOVE_LEFT)
    {
			// todo: estado IZquierda
            this->direction = SDL_FLIP_NONE;        
    }

    if (domainElement->getAction() == MOVELESS)
    {
            this->state = WORM_VIEW_MOTIONLESS;
    }
}
	
void WormView::update() 
{
	if (currentSprite == NULL) {
		currentSprite = &this->sprites["caminar"];
	}

	if (this->state == WORM_VIEW_DOING)
	{
		// Camino sin arma
		if (currentSprite != &this->sprites["caminar"]) {
			currentSprite = &this->sprites["caminar"];
		}
		currentSprite->update();
	} 
	else if (this->state == WORM_VIEW_MOTIONLESS)
	{
		if (this->weaponId == GRENADE && currentSprite != &this->sprites["granada"]) 
		{
			currentSprite = &this->sprites["granada"];
		} 
		if (this->weaponId == DYNAMITE && currentSprite != &this->sprites["dinamita"]) 
		{
			currentSprite = &this->sprites["dinamita"];
		}
		if (this->weaponId == BAZOOKA && currentSprite != &this->sprites["bazooka"]) 
		{
			currentSprite = &this->sprites["bazooka"];
		}
		if (this->weaponId == HOLY && currentSprite != &this->sprites["holy"]) 
		{
			currentSprite = &this->sprites["holy"];
		}
		if ((this->weaponId == AIRATTACK || this->weaponId == BURRO)
						&& currentSprite != &this->sprites["radio"]) 
		{
			currentSprite = &this->sprites["radio"];
		}
		

		if (this->weaponId == NO_WEAPON && currentSprite != &this->sprites["caminar"]) 
		{
			currentSprite = &this->sprites["caminar"];
		}
		
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
		labelUsuario.draw(screen.getRenderer(),-TextureManager::Instance().getCamera().getX() + this->getXCenter(), -TextureManager::Instance().getCamera().getY() + this->getYCenter()-9);
		labelNombre.draw(screen.getRenderer(),-TextureManager::Instance().getCamera().getX() + this->getXCenter(),-TextureManager::Instance().getCamera().getY() + this->getYCenter());
	}
	
}

bool WormView::isSelected(){
	return this->selected;
}

void WormView::select(){
	this->selected = true;
}
void WormView::deselect(){
	this->state = WORM_VIEW_MOTIONLESS;
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
