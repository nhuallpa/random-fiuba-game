#include "GameActivity.h"


GameActivity::GameActivity(const SDLScreen & screen, 
							ViewBuilder & builder):Activity(screen)
{
	View*  viewContainer = this->buildView(builder);
	this->setContentView(viewContainer);
}

View* GameActivity::buildView( ViewBuilder & builder)
{
	ViewGroup* container = builder.buildContainer();
	builder.buildSky(container);
	builder.buildFigures(container);
	builder.buildWater(container);
	return container;
}

GameActivity::~GameActivity(void)
{
	if (aView) delete aView;
	aView = 0;
}
