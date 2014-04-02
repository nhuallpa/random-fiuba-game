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
	container->add(new SkyView("sky"));
}

void DefaultViewBuilder::buildFigures(ViewGroup* container)
{

	std::list< FigureView* > listFigures;

	// build simple figures
	RectangleView* rectangle= new RectangleView("#FF0000FF");
	rectangle->setVertexA(150,150);
	rectangle->setVertexB(150,200);
	rectangle->setVertexC(200,200);
	rectangle->setVertexD(200,150);

	listFigures.push_back(rectangle);

	listFigures.push_back(new CircleView(100,250,20,"#00FF00FF", 0));

	// build a polygon
	// Drawing a pentagon
	PolygonView* polygon = new PolygonView("#00FFFFFF");
	polygon->addPoint(275,300);
	polygon->addPoint(300,350);
	polygon->addPoint(350,350);
	polygon->addPoint(375,300);
	polygon->addPoint(325,275);
	
	listFigures.push_back(polygon);

	// build a triangle
	TriangleView* triangle = new TriangleView("#FFFF00FF");
	triangle->setVertexA(50,50);
	triangle->setVertexB(40,70);
	triangle->setVertexC(60,70);
	listFigures.push_back(triangle);

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
