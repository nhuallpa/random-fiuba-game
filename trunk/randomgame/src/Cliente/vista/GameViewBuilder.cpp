#include "GameViewBuilder.h"


GameViewBuilder::GameViewBuilder(const std::map<int,GameElement*>& map, GameLevel * cLevel):
						domainElements(map), cLevel(cLevel)
{
}


GameViewBuilder::~GameViewBuilder(void)
{
}


ViewGroup* GameViewBuilder::buildContainer()
{
	return new ViewGroup(0,0,0,0);
}

FigureViewGroup* GameViewBuilder::buildFigureContainer()
{
	return new FigureViewGroup(0,0,0,0);
}

void GameViewBuilder::buildSky(ViewGroup* container)
{
	container->add(new SkyView("sky"));
}

void GameViewBuilder::buildFigures(FigureViewGroup* container)
{
	std::map<int,GameElement*>::iterator it;
	Log::d(VIEW_BUILDER,"Construyendo Figuras. Cantidad = %d", domainElements.size());

	ParserYaml* aParser = ParserYaml::getInstance();

	for (it = domainElements.begin(); it != domainElements.end(); ++it)
	{
		GameElement* domainElement = it->second;
		FigureView* aFigure = 0;
		std::string color= aParser->getColorById(Util::int2string(domainElement->getId()));
		if (domainElement->getType() == ElementType::CIRCLE) 
		{
			Log::d("Creando CIRCULO");


			float radius = domainElement->getRadius();
			Log::t("Radio: %f", radius);

			EllipseView* aCircle = new EllipseView(color);
			aCircle->updateRadius(radius);
			aCircle->updatePositions(domainElement->getPosition());
			aCircle->setId(domainElement->getId());
			aFigure = aCircle;

		} 
		else if (domainElement->getType() == ElementType::SQUARE) 
		{
			Log::d("Creando RECTANGULO");
			RectangleView* aRectangle = new RectangleView(color);
			aRectangle->updateVertex(domainElement->getVertex());
			aRectangle->setId(domainElement->getId());
			aFigure = aRectangle;
		}
		else if (domainElement->getType() == ElementType::TRIANGLE) 
		{
			Log::d("Creando TRIANGULO");
			TriangleView* aTriangle = new TriangleView(color);
			aTriangle->updateVertex(domainElement->getVertex());
			aTriangle->setId(domainElement->getId());
			aFigure = aTriangle;
		}
		else if (domainElement->getType() == ElementType::PENTA) 
		{
			Log::d("Creando PENTAGONO");
			PentagonView* aPentagon = new PentagonView(color);
			aPentagon->updateVertex(domainElement->getVertex());
			aPentagon->setId(domainElement->getId());
			aFigure = aPentagon;
		}
		else if (domainElement->getType() == ElementType::HEXAGON) 
		{
			Log::d("Creando HEXAGONO");
			HexagonView* aHexagon = new HexagonView(color);
			aHexagon->updateVertex(domainElement->getVertex());
			aHexagon->setId(domainElement->getId());
			aFigure = aHexagon;
		}
		if (aFigure) 
		{
			container->add(aFigure);
			aFigure = 0;
		}

	}
}

void GameViewBuilder::buildWater(ViewGroup* container)
{
	ParserYaml* aParser = ParserYaml::getInstance();
	std::string color = aParser->getEscenarioColorAgua();
	
	/*** TODO: retrive from domain*/
	int heigth = 20;
	
	container->add(new WaterView(heigth, color)); 
}

void GameViewBuilder::buildTerrain(ViewGroup* container)
{
	Log::d("Creando TERRENO en vista");
	ParserYaml* aParser = ParserYaml::getInstance();
	std::string color = aParser->getEscenarioColorTierra();

	TerrainView* aTerrain = new TerrainView(color);

	list< list< pair<float,float> > > * polygonsPoint = this->cLevel->getTerrain()->getListOfPolygons();
	list< list< pair<float,float> > >::iterator itPolygons;

	int countPolygons = 0;

	std::list<std::list<tPoint>> polygonsToView;
	for (itPolygons = polygonsPoint->begin(); itPolygons!=polygonsPoint->end(); ++itPolygons) 
	{
		countPolygons++;
		Log::t("Creando polygono nro: %d", countPolygons);
		list< pair< float, float> > ::iterator itPoints;	
		list< pair<float,float> > points = (*itPolygons);


		std::list<tPoint> pointsToView;
		for (itPoints = points.begin(); itPoints!=points.end(); ++itPoints) 
		{
			Log::t("----> Punto: %f %f", itPoints->first, itPoints->second);
			tPoint aPoint = Util::convertPointUL2PXSDL(itPoints->first, itPoints->second);
			
			pointsToView.push_back(aPoint);
		}
		polygonsToView.push_back(pointsToView);
	}

	delete polygonsPoint;
	
	std::list<std::list<tPoint>>::iterator it;

	for (it = polygonsToView.begin(); it != polygonsToView.end(); ++it)
	{
		aTerrain->buildPart((*it));
	}

	container->add(aTerrain); 
}