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

	this->buildView(builder);
	this->setContentView(builder->getGameView());
	this->setListeners(screen);
	this->wormIdSelected = -1;
	this->wormIdDesSelected = -1;
	GameView* gameView = static_cast<GameView*>(this->aView);
}

void GameActivity::buildView( GameViewBuilder * builder)
{
	builder->buildContainer();
	builder->buildSky();
	//builder.buildFigures();
	builder->buildEart();
	builder->buildCharacters();
	builder->buildWater();
	builder->buildStateBar();
	// Proceso de contruccion, by Erik
	builder->buildMenuWeapon();

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
		}
		catch (GameException e) {
			Log::e(e.what());
		}
	}
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
	GameView* gameView = static_cast<GameView*>(this->aView);
	int xView = x * ESCALA_UL2PX;
	int yView = y * ESCALA_UL2PX;
	int rView = radio * ESCALA_UL2PX;
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

WormView* GameActivity::retrieveWormClicked(SDL_Point clickPoint)
{
	WormView* aWormClicked = NULL;
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
					aWormClicked = aWorm;
					break;
				}
			}
		}
	}
	return aWormClicked;
}


void GameActivity::OnClick(ClickEvent e){
	WormView* aWorm = NULL;
	// nota: e.x e.y son posiciones de click en la pantalla sin importar el zoom ó scroll
	SDL_Point clickPoint = TextureManager::Instance().convertPointScreen2SDL(e.x,e.y);

	if (hasClickedWorm(clickPoint)) {
		aWorm = retrieveWormClicked(clickPoint);
		if (!aWorm->isSelected()) {
			deselectPreviewsWorm();
			selectWorm(aWorm);
		}
	}
	//else if (hasClickedMenu(clickPoint) && wormIdSelected != -1)
	//{
	//	WormView* aWorm = gameView->findWormById(this->wormIdSelected);
	//	int idWeapon = retrieveWaponId(clickPoint);
	//	selectItemMenu(idWapon);  // teambien agrega el weapon al listener, 
	//	aWorm->setWeapon(idWapon);
	//	updater.doSelectWapon(wormIdSelected, idWapon);
	//}
	else
	{
		deselectPreviewsWorm();
	}

	
}

void GameActivity::otherTurn(std::string playerId) 
{
	// seter el label del gameview para mostar el turno de peppito
}

void GameActivity::endMyTurn() 
{
	this->cController->remuveOnClickListener(this);
	this->cController->remuveOnMovementListener(this);
}


void GameActivity::beginMyTurn() 
{
	this->cController->addOnClickListener(this);
	this->cController->addOnMovementListener(this);
}


void GameActivity::setListeners(SDLScreen &  screen) 
{
	/* TODO: @Ariel, sacar estas dos lineas*/
	this->cController->addOnClickListener(this);
	this->cController->addOnMovementListener(this);

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
	int wormIdSelected = this->getWormIdSelected();

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