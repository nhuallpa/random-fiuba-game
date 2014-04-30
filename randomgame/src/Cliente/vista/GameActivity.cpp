#include "GameActivity.h"


GameActivity::GameActivity(const SDLScreen & screen, 
							ViewBuilder & builder, 
							GameLevel * cLevel,
							GameController* cController)
							:Activity(screen), cLevel(cLevel), cController(cController)
{
	ViewGroup*  viewContainer = this->buildView(builder);
	this->setContentView(viewContainer);
	this->setListeners();
}

ViewGroup* GameActivity::buildView( ViewBuilder & builder)
{
	ViewGroup* container = builder.buildContainer();
	this->figureContainer = builder.buildFigureContainer();
	builder.buildSky(container);
	builder.buildFigures(figureContainer);

	container->add(this->figureContainer);
	builder.buildCharacters(container);

	//builder.buildTerrain(container);
	builder.buildEart(container);
	builder.buildWater(container);
	return container;
}

void GameActivity::update() 
{
	std::map<int,GameElement*> domainElements = this->cLevel->getEntities();
	std::map<int,GameElement*>::iterator it;
	Log::d(VIEW,"Actualizando %d en elemento", domainElements.size());

	for (it = domainElements.begin(); it != domainElements.end(); ++it)
	{
		GameElement* domainElement = it->second;
		try
		{
			FigureView* aFigure = this->figureContainer->findById(domainElement->getId());
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
	if (aView) delete aView;
	aView = 0;
}

void GameActivity::setListeners() 
{
	this->cController->addListener(&TextureManager::Instance().getCamera());

	// todo: set listener onClick para los worms
}