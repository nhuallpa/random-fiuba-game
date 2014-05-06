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

GameActivity::GameActivity(const SDLScreen & screen, 
							GameViewBuilder & builder, 
							GameController* cController)
							:Activity(screen), cController(cController)
{
	this->buildView(builder);
	this->setContentView(builder.getGameView());
	this->setListeners();
}

void GameActivity::buildView( GameViewBuilder & builder)
{
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
	//ARIEL: Refactor
	//std::map<int,GameElement*> domainElements = this->cLevel->getEntities();
	
	std::map<int,GameElement*>::iterator it;
	Log::d(VIEW,"Actualizando %d en elemento", domainElements.size());

	for (it = domainElements.begin(); it != domainElements.end(); ++it)
	{
		GameElement* domainElement = it->second;
		Log::d(VIEW,"elemento %s",domainElement->getType());
		try
		{
			FigureView* aFigure = gameView->findFigureById(domainElement->getId());
			aFigure->update(domainElement);
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
	Log::d("CLICK");
}


void GameActivity::setListeners() 
{
	this->cController->addListener(&TextureManager::Instance().getCamera());
	this->cController->addListener(this);
}