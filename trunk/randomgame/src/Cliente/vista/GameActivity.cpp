#include "GameActivity.h"
#define WORM_W 60
#define WORM_H 60


//GameActivity::GameActivity(const SDLScreen & screen, 
//							GameViewBuilder & builder, 
//							GameLevel * cLevel,
//							GameController* cController)
//							:Activity(screen), cLevel(cLevel), cController(cController)
//{
//	this->buildView(builder);
//	this->setContentView(builder.getGameView());
//	this->setListeners();
//}

GameActivity::GameActivity(SDLScreen & screen, 
							GameViewBuilder & builder, 
							GameController* cController)
							:Activity(screen), cController(cController)
{
	this->buildView(builder);
	this->setContentView(builder.getGameView());
	this->setListeners(screen);
	this->wormIdSelected = -1;
	
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

}

void GameActivity::update() 
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	//ARIEL: Refactor grande, ver si no rompi :)
	//NESTOR: Quito las figuras por ahora. Hay que actualiza la vista.
	/*std::map<int,GameElement>* domainElements = this->builder->getDomain()->getDomainElements();
	
	std::map<int,GameElement>::iterator it;
	Log::d(VIEW,"Actualizando %d en elemento", domainElements->size());

	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		Log::d(VIEW,"elemento %d",domainElement.getType());
		try
		{
			FigureView* aFigure = gameView->findFigureById(domainElement.getId());
			aFigure->update(&domainElement);
		}
		catch (GameException e) {
			Log::e(e.what());
		}
	}*/
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
	}
	
}

void GameActivity::selectWorm(WormView* aWorm)
{
	this->wormIdSelected = aWorm->getId();
	aWorm->select();
	this->cController->addListener(aWorm);
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
				/*
				// todo: corregir este RECT usando el 
				Camera cam = TextureManager::Instance().getCamera();
				SDL_Rect wormRect;
				wormRect.x = aWorm->getX()-(WORM_W/2)-cam.getX(); // deberia se el centroide
				wormRect.y = aWorm->getY()-(WORM_H/2)-cam.getY();  // deberia se el centroide
				wormRect.w = WORM_W;   // tomar alto de constant y usar centroide
				wormRect.h = WORM_H;  // tomar ancho de constant y usar centroide
				*/
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
	SDL_Point clickPoint;
	clickPoint.x = e.x;
	clickPoint.y = e.y;
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