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


FigureViewGroup* DefaultViewBuilder::buildFigureContainer()
{
	return new FigureViewGroup(0,0,0,0);
}

void DefaultViewBuilder::buildSky(ViewGroup* container)
{
	container->add(new SkyView("sky"));
}

void DefaultViewBuilder::buildFigures(FigureViewGroup* container)
{

	std::list< FigureView* > listFigures;

	// build simple figures
	RectangleView* rectangle= new RectangleView("#FF0000FF");
	rectangle->setVertexA(150,150);
	rectangle->setVertexB(150,200);
	rectangle->setVertexC(200,200);
	rectangle->setVertexD(200,150);

	listFigures.push_back(rectangle);
	CircleView* aCircleView = new CircleView("#00FF00FF");
	aCircleView->setX(100);
	aCircleView->setY(250);
	aCircleView->setRadio(20);
	listFigures.push_back(aCircleView);

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

void DefaultViewBuilder::buildTerrain(ViewGroup* container)
{
	TerrainView* aTerrain = new TerrainView("#BC794FFF");

	// Set points of each polygon
	std::list<std::list<tPoint>> pointsOfPolygons;
	std::list<tPoint> points;
	int i=1;
	for (i=1; i <= 8; i++) {
		tPoint aPoint;
		aPoint.x = i*50 + 80;
		if (i<=3) {	aPoint.y = 500 - i*100 ;	} 
		else if (i<=6) 	{ aPoint.y = 370; }
		else if (i<8) {	aPoint.y = 100 + i*10 ; }
		else { aPoint.y = 400; }
		points.push_back(aPoint);
	}
	pointsOfPolygons.push_back(points);

	std::list<std::list<tPoint>>::iterator it;

	for (it = pointsOfPolygons.begin(); it != pointsOfPolygons.end(); ++it)
	{
		aTerrain->buildPart((*it));
	}

	container->add(aTerrain); 
}

