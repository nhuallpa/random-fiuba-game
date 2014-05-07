#include "GameActivity.h"


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
}

void GameActivity::buildView( GameViewBuilder & builder)
{
	this->builder = &builder;
	builder.buildContainer();
	builder.buildSky();
	builder.buildFigures();
	builder.buildEart();
	builder.buildCharacters();
	builder.buildWater();



}

void GameActivity::update() 
{
	GameView* gameView = static_cast<GameView*>(this->aView);
	//ARIEL: Refactor grande, ver si no rompi :)
	std::map<int,GameElement>* domainElements = this->builder->getDomainElements();
	
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
	}
	this->aView->update();
}

GameActivity::~GameActivity(void)
{
}

void GameActivity::OnClick(ClickEvent e){
	Log::d("**************CLICK*****************");

	std::map<int,GameElement>* domainElements = this->builder->getDomainElements();
	std::map<int,GameElement>::iterator it;
	GameView* gameView = static_cast<GameView*>(this->aView);
	for (it = domainElements->begin(); it != domainElements->end(); ++it)
	{
		GameElement domainElement = it->second;
		Log::d("playerId: %s",domainElement.getPlayerID().c_str());
		if (domainElement.getType() == WORM){
			WormView* aWorm = gameView->findWormById(domainElement.getId());
			if (aWorm != NULL){
				SDL_Rect wormRect;
				wormRect.x = aWorm->getX();
				wormRect.y = aWorm->getY();
				wormRect.w = aWorm->getX()+10;
				wormRect.h = aWorm->getY()+10;
				SDL_Point clickPoint;
				clickPoint.x = e.x;
				clickPoint.y = e.y;
				if ( (!aWorm->isSelected()) &&(SDL_EnclosePoints(&clickPoint,1,&wormRect,NULL))){
					aWorm->select();
					// Si el worm es del jugador lo registro/des-registro como listener.
					if ( !domainElement.getPlayerID().compare(this->builder->getPlayerID()) ){
						this->cController->addListener(aWorm);
						
					}
				}
				else if (aWorm->isSelected()){
					aWorm->deselect();
					this->cController->remuveListener(aWorm);
				}
			}
		}
	
	}
	Log::d("*********** FIN CLICK***************");
}


void GameActivity::setListeners(SDLScreen &  screen) 
{
	this->cController->addListener(&TextureManager::Instance().getCamera());
	this->cController->addListener(this);
	this->cController->addListener(&screen);
}