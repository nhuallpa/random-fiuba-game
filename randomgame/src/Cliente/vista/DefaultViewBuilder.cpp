#include "DefaultViewBuilder.h"


DefaultViewBuilder::DefaultViewBuilder(void)
{
}

DefaultViewBuilder::~DefaultViewBuilder(void)
{
}

ViewGroup* DefaultViewBuilder::buildContainer()
{
	return new ViewGroup(0,0,0,0);
}

void DefaultViewBuilder::buildSky(ViewGroup* container)
{
	container->add(new SkyView("fondo"));
}

void DefaultViewBuilder::buildFigures(ViewGroup* container)
{

	std::list< FigureView* > listFigures;

	listFigures.push_back(new RectangleView(100,100,40,40,0xff0000ff, 0));
	listFigures.push_back(new CircleView(100,250,20,0xffffffff, 0));

	//FigureView* polygon = new PolygonView(200, 150, 0xffffffff, 0);

	listFigures.push_back(new CircleView(100,250,20,0xffffffff, 0));


	std::list<FigureView*>::iterator it;
	for (it = listFigures.begin(); it != listFigures.end(); ++it) 
	{
		container->add(*it);
	}

}

void DefaultViewBuilder::buildWater(ViewGroup* container)
{
	container->add(new WaterView(100, 0xffffff55)); 
}
