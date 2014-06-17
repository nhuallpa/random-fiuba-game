#include "WormView.h"


WormView::WormView(int id)
	: View(0, 0), id(id), flip(SDL_FLIP_NONE), state(WORM_VIEW_MOTIONLESS)
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
	this->widhtLife100 = 25;
	this->widhtLifeCurrent = 25;
	this->currentLife = 100;
	this->enableScroll();
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
	this->selectWeapon((WeaponId)domainElement->getWeaponId());
	//Log::i("WormView::update >> weapon %d", this->weaponId);
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
            domainElement->getAction() == MOVE_RIGHT || 
			domainElement->getAction() == WITH_WEAPON_RIGHT)
    {
			// todo: estado derecha
            this->flip = SDL_FLIP_HORIZONTAL;
    } 
    else if (domainElement->getAction() == MOVELESS_LEFT || 
            domainElement->getAction() == NOT_CONNECTED_LEFT ||
            domainElement->getAction() == MOVE_LEFT ||
			domainElement->getAction() == WITH_WEAPON_LEFT)
    {
			// todo: estado IZquierda
            this->flip = SDL_FLIP_NONE;        
    }

	if (domainElement->getAction() == MOVELESS || domainElement->getAction() == WITH_WEAPON_LEFT || domainElement->getAction() == WITH_WEAPON_RIGHT)
    {
            this->state = WORM_VIEW_MOTIONLESS;
    }

	if (domainElement->getLife() < this->currentLife) {
		this->widhtLifeCurrent = (int)(((float)domainElement->getLife() * (float)this->widhtLife100) / 100.0f);
		if (this->widhtLifeCurrent > this->widhtLife100) {
			this->widhtLifeCurrent = this->widhtLife100;
		}
		if (this->widhtLifeCurrent <= 0) {
			this->widhtLifeCurrent = 1;
		}
		this->currentLife = domainElement->getLife();
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
										this->flip);
	
	 
	if (this->isSelected())
	{
		//labelUsuario.draw(screen.getRenderer(),-TextureManager::Instance().getCamera().getX() + this->getXCenter(), -TextureManager::Instance().getCamera().getY() + this->getYCenter()-9);
		labelNombre.draw(screen.getRenderer(),
						 this->getXCenter(),
						 this->getYCenter());
	}

	SDL_Rect rect;
	rect.x = this->getX()-10;
	rect.y = this->getY()-22;
	rect.w = this->widhtLifeCurrent;
	rect.h = 5;
	TextureManager::Instance().drawBox(screen.getRenderer(), 
													rect.x, 
													rect.y, 
													rect.x + rect.w,
													rect.y + rect.h, 
													0xFF01DF3A);
	
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
		this->flip = SDL_FLIP_HORIZONTAL;
	}
	else if (e.x == -1) // izquierda
	{
		this->state = WORM_VIEW_DOING;
		this->flip = SDL_FLIP_NONE;
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

tDirection WormView::getDirection()
{
	if (this->flip == SDL_FLIP_NONE) {
		return D_LEFT;
	} else {
		return D_RIGHT;
	}
}