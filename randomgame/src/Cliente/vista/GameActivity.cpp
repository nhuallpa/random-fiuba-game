#include "GameActivity.h"
#define WORM_W 20
#define WORM_H 30




GameActivity::GameActivity(SDLScreen & screen, 
							GameDomain* domain, 
							GameController* cController,
							std::string playerId, Updater & updater)
							:Activity(screen), cController(cController), playerId(playerId), updater(updater)
{

	builder = new GameViewBuilder(domain, &screen);
	builder->setPlayerID(playerId);
	this->setListeners(screen);
	this->wormIdSelected = -1;
	this->wormIdDesSelected = -1;
	this->isMyTurn = false;
	this->idWeapon = NO_WEAPON;
	this->aimView = NULL;
	
}

void GameActivity::buildView()
{
	builder->buildContainer();
	builder->buildSky();
	//builder.buildFigures();
	builder->buildEart();
	builder->buildCharacters();
	builder->buildProjectileContainer();
	builder->buildWater();
	builder->buildStateBar();
	builder->buildMenuWeapon();
	this->setContentView(builder->getGameView());
	GameView* gameView = static_cast<GameView*>(this->aView);
	aimView = new AimView();
	gameView->add(aimView);
	this->cController->addOnChangeListener(aimView);
	this->cController->addOnMovementListener(aimView);
}

void GameActivity::update() 
{
	
	GameView* gameView = static_cast<GameView*>(this->aView);
	std::map<int,GameElement>* domainElements = this->builder->getDomain()->getDomainElements();
	std::map<int,GameElement>::iterator it;
	Log::t(VIEW,"Actualizando %d elemento", domainElements->size());
	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		Log::t(VIEW,"elemento id %d",domainElement.getId());
		try
		{
			if (domainElement.getType() == WORM) 
			{
				WormView* aWorm = gameView->findWormById(domainElement.getId());
				StateConn stateConn = this->builder->getDomain()->getPlayerState(domainElement.getPlayerID());
				if (!this->isThisClientOwner(domainElement.getId()))
				{
					if (stateConn == DISCONNECTED)
					{
						aWorm->putGrey();
						Log::d("El usuario %s tiene estado %d",domainElement.getPlayerID().c_str(),stateConn );	
					}
					else
					{
						aWorm->quitGrey();
					}
						
				}
				aWorm->update(&domainElement);
			}  
			else if (domainElement.getType() == WEAPON)
			{
				ProjectileView * aProjectile = gameView->findProjectileById(domainElement.getId());
				if (aProjectile->isDetonateDone()) 
				{
					this->futureFree.push_back(aProjectile->getId());
				}
				aProjectile->update(&domainElement);
			}
		}
		catch (GameException e) {
			Log::e(e.what());
		}
	}

	std::vector<int>::iterator itProj;
	for (itProj = this->futureFree.begin(); itProj != this->futureFree.end(); ++itProj)
	{
		int id = *itProj;
		gameView->freeProjectileView(id);
		this->builder->getDomain()->removeElement(id);
		Log::i("Elimine projectile %d en la vista", id);
	}
	this->futureFree.clear();

	this->aView->update();

}

GameActivity::~GameActivity(void)
{
	delete builder;
}

void GameActivity::deselectPreviewsWorm()
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	if (this->wormIdSelected > 0) {
		WormView* aWorm = gameView->findWormById(this->wormIdSelected);

		aWorm->deselect();
		updater.doStopWorm(aWorm->getId());
		this->cController->remuveListener(aWorm);

		this->wormIdSelected = -1;

		aWorm->unselectWeapon();
	}
	
}

void GameActivity::stop()
{
	if (this->wormIdSelected > 0) 
	{
		updater.doStopWorm(this->wormIdSelected);
		this->wormIdSelected = -1;
	}
}

void GameActivity::selectWorm(WormView* aWorm)
{
	this->wormIdSelected = aWorm->getId();
	aWorm->select();
	if (this->playerId.compare(aWorm->getPlayer()) == 0)
	{
		this->cController->addListener(aWorm);
	}
}

void GameActivity::doExplotion(float x, float y, float radio)
{
	Log::i(" Explotar terreno en %f y %f  y radio %f [UL]", x, y, radio);
	GameView* gameView = static_cast<GameView*>(this->aView);
	tPoint pointSDL = TextureManager::Instance().convertPointUL2PXSDL(x, y);

	int xView = pointSDL.x;
	int yView = pointSDL.y;

	int rView = radio * ESCALA_UL2PX;
	Log::i(" Explotar terreno en %d y %d  y radio %d [PX]", xView, yView, rView);
	gameView->getDestroyEart(xView, yView, rView);
}


void GameActivity::calcRectPosition(SDL_Rect& wormRect,WormView *aWorm){
	
	Camera cam = TextureManager::Instance().getCamera();
	wormRect.x = (aWorm->getX()-(WORM_W/2)-cam.getX());
	wormRect.y = (aWorm->getY()-(WORM_H/2)-cam.getY());
	
	wormRect.w = WORM_W;  
	wormRect.h = WORM_H;  

}

bool GameActivity::hasClickedWorm(SDL_Point clickPoint)
{
	bool wormClicked = false;
	std::map<int,GameElement>* domainElements = this->builder->getDomain()->getDomainElements();
	std::map<int,GameElement>::iterator it;
	GameView* gameView = static_cast<GameView*>(this->aView);
	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		if (domainElement.getType() == WORM){
			WormView* aWorm = gameView->findWormById(domainElement.getId());
			if (aWorm != NULL){
				SDL_Rect wormRect;
				this->calcRectPosition(wormRect,aWorm);
				if (SDL_EnclosePoints(&clickPoint,1,&wormRect,NULL))
				{
					wormClicked =  true;
					break;
				}
			}
		}
	}
	return wormClicked;
}

bool GameActivity::hasClickedMenu(SDL_Point clickPoint){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->hasClickedMenu(clickPoint);
}

bool GameActivity::hasClickedWeapon(SDL_Point clickPoint){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->hasClickedWeapon(clickPoint);
}

Weapon* GameActivity::retrieveWeaponClicked(SDL_Point clickPoint){
	GameView* gameView = static_cast<GameView*>(this->aView);
	return gameView->retrieveWeaponClicked(clickPoint);
}

WormView* GameActivity::retrieveWormClicked(SDL_Point clickPoint)
{
	WormView* aWormClicked = NULL;
	std::map<int,GameElement>* domainElements = this->builder->getDomain()->getDomainElements();
	std::map<int,GameElement>::iterator it;
	GameView* gameView = static_cast<GameView*>(this->aView);
	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		try {
			if (domainElement.getType() == WORM){
				WormView* aWorm = gameView->findWormById(domainElement.getId());
				SDL_Rect wormRect;
				this->calcRectPosition(wormRect,aWorm);
				if (SDL_EnclosePoints(&clickPoint,1,&wormRect,NULL))
				{
					aWormClicked = aWorm;
					break;
				}
			}
		} catch (GameException & e) {
			Log::e(e.what());		
		}
	}
	return aWormClicked;
}


void GameActivity::OnClick(ClickEvent e){
	GameView* gameView = static_cast<GameView*>(this->aView);
	
	WormView* aWorm = NULL;

	//Agrego para escuchar el clic del arma
	if(aimView->isShootMouse()){
		int xMira= e.x;
		int yMira= e.y;
		std::pair<int, int> data = this->aimView->getData();
		Log::i("\nShoot 1: x %d, y %d FACTOR 0",xMira,yMira);
		updater.doShoot(data.first, data.second, xMira, yMira, 0);
		aimView->unAim();
		return; //proceso y me voy
	}




	// nota: e.x e.y son posiciones de click en la pantalla sin importar el zoom ó scroll
	SDL_Point clickPoint = TextureManager::Instance().convertPointScreen2SDL(e.x,e.y);

	if (hasClickedWorm(clickPoint)) {
		aWorm = retrieveWormClicked(clickPoint);
		if (!aWorm->isSelected()) {
			deselectPreviewsWorm();
			selectWorm(aWorm);
			if(this->idWeapon != NO_WEAPON){
				deselectPreviewsWeapon();
				aimView->unAim();
			}
		}
	}
	else if (wormIdSelected != -1 && hasClickedMenu(clickPoint))
	{
		if(hasClickedWeapon(clickPoint)){
			WeaponId aux = this->idWeapon;
			if(this->idWeapon != NO_WEAPON){
				deselectPreviewsWeapon();
				aimView->unAim();
			}

			Weapon* aWeapon = retrieveWeaponClicked(clickPoint);
			this->idWeapon = aWeapon->getId();
			aWeapon->selected();
			aWorm = gameView->findWormById(wormIdSelected);
			aWorm->selectWeapon(this->idWeapon);
			updater.doSelectWapon(wormIdSelected, this->idWeapon);

			//logica de la mira
			aimView->setWorm(aWorm, aWeapon);
			aimView->aimBuild();


			if(aux == this->idWeapon ){
				deselectPreviewsWeapon();
				aWorm->unselectWeapon();
				updater.doUnselectWapon(wormIdSelected, this->idWeapon);
				aimView->unAim();
			}
		}
		else{
			/*TODO: entra en este else cuando un worm esta seleccionado
					y soca algun sector del menu donde no hay armas			
			*/
		}
	}
	else
	{
		deselectPreviewsWorm();
		deselectPreviewsWeapon();
		aimView->unAim();		
	}

	
}

void GameActivity::deselectPreviewsWeapon(){
	if(this->idWeapon != NO_WEAPON){
		GameView* gameView = static_cast<GameView*>(this->aView);
		Weapon* aWeapon = gameView->findWeaponById(idWeapon);
		aWeapon->unSelected();
		this->idWeapon = NO_WEAPON;
	}

}


void GameActivity::otherTurn(std::string playerId) 
{
	// seter el label del gameview para mostar el turno de peppito
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMessageCenter("Is turn of " + playerId);
	this->isMyTurn = false;
}

void GameActivity::endMyTurn() {
	if ( this->isMyTurn ){
		Log::i("\nRemoving all listeners");
		this->cController->remuveOnClickListener(this);
		this->cController->remuveOnMovementListener(this);
		this->cController->remuveOnActionListener(this);
	}
}


void GameActivity::beginMyTurn() 
{
	this->isMyTurn = true;
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMessageCenter("Is your turn");
	this->cController->addOnClickListener(this);
	this->cController->addOnMovementListener(this);
	this->cController->addOnActionListener(this);
}


void GameActivity::setListeners(SDLScreen &  screen) 
{
	this->cController->addListener(&TextureManager::Instance().getCamera());
	this->cController->addListener(&screen);
}


void GameActivity::buildNewWorms(std::string playerID, int id, int x, int y) 
{
	GameView* gameView = static_cast<GameView*>(this->aView);

	GameElement aGameElem(id, playerID, WORM, x, y, 0, 0, 0, 0, false);
	
	this->builder->getDomain()->addElementToDomain(aGameElem);
	WormView* aWormView = this->builder->createWorm(&aGameElem);
	gameView->getWormContainer()->add(aWormView);

}

void GameActivity::buildProjectile(int idElement, float x, float y, int type)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	Log::i("GameActivity::buildProjectile >> Agregando GameElement id: %d,pos[ %f, %f ]", idElement, x, y);
	GameElement aGameElem(idElement, this->playerId, WEAPON, x, y, 0, 0, 0, 0, false);
	
	this->builder->getDomain()->addElementToDomain(aGameElem);

	ProjectileView* aProjectileView = this->builder->createBullet(&aGameElem, type);
	Log::i("GameActivity::buildProjectile >> Agregando ProjectileView id: %d,pos[ %d, %d ]", aProjectileView->getId(), aProjectileView->getX(), aProjectileView->getY());
	gameView->getProjectileContainer()->add(aProjectileView);

	// Quien esta selecionado al disparar??
	try {
		WormView* aWorm = gameView->findWormById(this->wormIdSelected);
		Log::i("GameActivity::buildProjectile >> WormView %d seleccionado y pos %d, %d [px]", aWorm->getId(), aWorm->getX(), aWorm->getY());
	} catch (GameException & e) {

	}

}

bool GameActivity::isAlive(int wormId) {
	GameView* gameView = static_cast<GameView*>(this->aView);

	try
	{
		WormView* aWorm = gameView->findWormById(wormId);
		SDL_Rect wormDim;
		SDL_Rect scenaryDim;
		scenaryDim.y = 0;
		scenaryDim.x = 0;
		scenaryDim.w = TextureManager::Instance().getCamera().getWidthScenario();
		scenaryDim.h = TextureManager::Instance().getCamera().getHeightScenario();
		
		wormDim.x = aWorm->getXCenter();
		wormDim.y = aWorm->getYCenter();
		wormDim.w = aWorm->getW();
		wormDim.h = aWorm->getH();
		if (TextureManager::Instance().intersectRects(wormDim, scenaryDim))
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (GameException e) {
		Log::e(e.what());
		return false;
	}

	return true;
}

bool GameActivity::isThisClientOwner(int wormId)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	WormView* aWorm = gameView->findWormById(wormId);
	if (aWorm->getPlayer().compare(this->playerId)==0)
	{
			return true;
	} 
	else
	{
			return false;
	}
}

void GameActivity::setMessageView(std::string msg)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMsj(msg);
}

void GameActivity::showMessageError(std::string msg)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMsjError(msg);
}

void GameActivity::showMessageInfo(std::string msg)
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMsjInfo(msg);
}

void GameActivity::OnMovement(MovementEvent e)
{
	Playable p;


	//no lo dejo mover si va a disparar
	if(aimView->isShootEnter()/*
		|| e.me == M_ANTICLOCK
		|| e.me == M_SHEDULE*/){
		return;
	}

	int wormIdSelected = this->getWormIdSelected();
	/*WeaponId weaponSelected;
	try {
		GameView* gameView = static_cast<GameView*>(this->aView);
		weaponSelected = gameView->findWormById(wormIdSelected)->getWeaponId();
	} catch (GameElement & e) {
		weaponSelected = NO_WEAPON;
	}*/

	if (wormIdSelected > 0 && 
		this->isThisClientOwner(wormIdSelected) && 
		this->isAlive(wormIdSelected))
	{
		p.wormid = wormIdSelected;
		if (e.y == -1)  // Solo saltar
		{
			if (e.x == 1) //Salta derecha
			{
				p.action = 	JUMP_RIGHT;
				Log::t("CLIENTE: Saltar derecha");
			}
			else if (e.x == -1) // Saltar izquierda
			{
				p.action = 	JUMP_LEFT;
				Log::t("CLIENTE: Saltar izquierda");
			} 
			else 
			{
				p.action = 	JUMP;
				Log::t("CLIENTE: Saltar");
			}
			/*
			if (weaponSelected == BAZOOKA && 
				weaponSelected == GRENADE && 
				weaponSelected == HMISSILE && 
				weaponSelected == HOLY)
			{
				Log::i("CLIENTE: No salto porque tengo un arma con mira");
				return;
			}*/
		}
		else if (e.x == 1) // derecha
		{
			p.action = 	MOVE_RIGHT;
		}
		else if (e.x == -1) // izquierda
		{
			p.action = 	MOVE_LEFT;
		} 
		else if (e.x == 0) // quieto
		{
			p.action = 	MOVE_STOP;
		}
		updater.addLocalMovementFromView(p);
	}

	
}


void GameActivity::OnAction(ActionEvent e){
	Log::e("ASD: %d", (int)e.action);
	GameView* gameView = static_cast<GameView*>(this->aView);
	switch(e.action){
		case MENU: 
			gameView->actionMenu();
			break;
		case SHOOT:
			{

				if (this->wormIdSelected>0 && this->idWeapon!=NO_WEAPON) {
					int factor = e.factor;
					int xMira= e.xAim;
					int yMira= e.yAim;

					if(aimView->isShootEnter()){
						std::pair<int, int> data = this->aimView->getData();
						int angle = this->aimView->getAngle();
						xMira = yMira = angle;
						aimView->unAim();
					}
					Log::i("\nShoot 2: x %d, y %d, factor %d",xMira,yMira,factor);
					updater.doShoot(this->wormIdSelected, this->idWeapon, xMira, yMira, factor);
					deselectPreviewsWeapon();
				}
			}
			break;
		default: ;
	}
}



