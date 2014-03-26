#include "GameActivity.h"


GameActivity::GameActivity(const SDLScreen & screen):Activity(screen)
{
	rectView=0;
	skyView=0;
	waterView=0;
	viewContainer=0;

	rectView = new FigureView("cuadrado",100,100);
	skyView = new SkyView("fondo");
	waterView = new WaterView("water",60,60,205,101);
	
	viewContainer = new ViewGroup(0,0,0,0);
	viewContainer->add(skyView);
	viewContainer->add(rectView);
	viewContainer->add(waterView);

	this->setContentView(viewContainer);
}

GameActivity::~GameActivity(void)
{
	if (rectView) delete rectView;
	if (skyView) delete skyView;
	if (waterView) delete waterView;
	if (viewContainer) delete viewContainer;
}
