#include "GameActivity.h"
#define WORM_W 30
#define WORM_H 30



GameActivity::GameActivity(SDLScreen & screen, 
							GameViewBuilder & builder, 
							GameController* cController,
							std::string playerId)
							:Activity(screen), cController(cController), playerId(playerId)
{
	this->buildView(builder);
	this->setContentView(builder.getGameView());
	this->setListeners(screen);
	this->wormIdSelected = -1;
	GameView* gameView = static_cast<GameView*>(this->aView);
	gameView->getStateBar()->setMsj("Ingreso al juego");
}

void GameActivity::buildView( GameViewBuilder & builder)
{
	this->builder = &builder;
	builder.buildContainer();
	builder.buildSky();
	//builder.buildFigures();
	builder.buildEart();
	builder.buildCharacters();
	builder.buildWater();
	builder.buildStateBar();

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
				if (stateConn == DISCONNECTED)
					aWorm->putGrey();
				if (stateConn == CONNECTED || stateConn == RECONNECTED)
					aWorm->quitGrey();


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
}

void GameActivity::deselectPreviewsWorm()
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	if (this->wormIdSelected > 0) {
		WormView* aWorm = gameView->findWormById(this->wormIdSelected);
		aWorm->deselect();
		this->cController->remuveListener(aWorm);
		this->wormIdSelected = -1;
		MovementEvent m;
		m.x = 0;
		m.y = 0;
		aWorm->OnMovement(m);
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
	else deselectPreviewsWorm();
}


void GameActivity::setListeners(SDLScreen &  screen) 
{
	this->cController->addListener(&TextureManager::Instance().getCamera());
	this->cController->addListener(this);
	this->cController->addListener(&screen);
}


void GameActivity::buildNewWorms(std::string playerID, int id, int x, int y) 
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	GameElement aGameElem(id, playerID, WORM, x, y, 0, 0, 0, 0, false);
	aGameElem.setAction(MOVELESS);
	this->builder->getDomain()->addElementToDomain(aGameElem);
	WormView* aWormView = this->builder->createWorm(&aGameElem);
	gameView->getWormContainer()->add(aWormView);

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