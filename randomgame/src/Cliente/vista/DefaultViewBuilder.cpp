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

	// build simple figures
	listFigures.push_back(new RectangleView(100,100,40,40,"#FF0000FF", 0));
	listFigures.push_back(new CircleView(100,250,20,"#00FF00FF", 0));

	// build a polygon
	PolygonView* polygon = new PolygonView(200, 150, "#0000FFFF", 0);
	polygon->addPoint(10,10);
	polygon->addPoint(10,20);
	polygon->addPoint(30,30);
	polygon->addPoint(20,10);
	listFigures.push_back(polygon);

	// add all views into view group
	std::list<FigureView*>::iterator it;
	for (it = listFigures.begin(); it != listFigures.end(); ++it) 
	{
		container->add(*it);
	}

}

void DefaultViewBuilder::buildWater(ViewGroup* container)
{
	container->add(new WaterView(100, "#0000FF99")); 
}
