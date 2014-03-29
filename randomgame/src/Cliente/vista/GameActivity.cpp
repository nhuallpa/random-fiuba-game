#include "GameActivity.h"


GameActivity::GameActivity(const SDLScreen & screen):Activity(screen)
{
	skyView=0;
	waterView=0;
	viewContainer=0;

	skyView = new SkyView("fondo");
	waterView = new WaterView(100, 0xffffff55); // agua marina

	mFigures.push_back(new RectangleView(100,100,40,40,0xff0000ff, 0));
	mFigures.push_back(new CircleView(100,250,20,0xffffffff, 0));

	viewContainer = new ViewGroup(0,0,0,0);
	viewContainer->add(skyView);
	
	std::list<FigureView*>::iterator it;
	for (it = mFigures.begin(); it != mFigures.end(); ++it) 
	{
		viewContainer->add(*it);
	}
	
	viewContainer->add(waterView);

	this->setContentView(viewContainer);
}

GameActivity::~GameActivity(void)
{
	std::list<FigureView*>::iterator it;
	for (it = mFigures.begin(); it != mFigures.end(); ++it) 
	{
		delete (*it);
	}
	mFigures.clear();

	if (skyView) delete skyView;
	if (waterView) delete waterView;
	if (viewContainer) delete viewContainer;
}
