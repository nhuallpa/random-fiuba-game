#include "GameActivity.h"


GameActivity::GameActivity(const SDLScreen & screen, 
							GameViewBuilder & builder, 
							GameLevel * cLevel,
							GameController* cController)
							:Activity(screen), cLevel(cLevel), cController(cController)
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
	std::map<int,GameElement*> domainElements = this->cLevel->getEntities();
	std::map<int,GameElement*>::iterator it;
	Log::d(VIEW,"Actualizando %d en elemento", domainElements.size());

	for (it = domainElements.begin(); it != domainElements.end(); ++it)
	{
		GameElement* domainElement = it->second;
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

void GameActivity::setListeners() 
{
	this->cController->addListener(&TextureManager::Instance().getCamera());
}