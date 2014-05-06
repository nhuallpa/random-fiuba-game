#include "GameViewBuilder.h"

//Ya no se crea mas en base al nivel
//GameViewBuilder::GameViewBuilder(GameLevel * cLevel):cLevel(cLevel)
//{
//	gameView = NULL;
//}

GameViewBuilder::GameViewBuilder(){
	gameView = NULL;
}



GameViewBuilder::~GameViewBuilder(void)
{
	if (gameView) delete gameView;
}


void GameViewBuilder::buildContainer()
{

	std::pair<int, int> dimension = TextureManager::Instance().getDimension("eart");
	gameView = new GameView(0,0,dimension.first, dimension.second);
}

void GameViewBuilder::buildSky()
{
	gameView->setSky(new SkyView("sky"));
}

void GameViewBuilder::buildEart()
{
	gameView->setEart(new EartView("eart"));
}

void GameViewBuilder::buildFigures()
{
	//std::map<int,GameElement*> domainElements = this->cLevel->getEntities();
	std::map<int,GameElement*>::iterator it;
	Log::d(VIEW_BUILDER,"Construyendo Figuras. Cantidad = %d", domainElements.size());

	ParserYaml* aParser = ParserYaml::getInstance();

	for (it = domainElements.begin(); it != domainElements.end(); ++it)
	{
		GameElement* domainElement = it->second;
		FigureView* aFigure = 0;
		std::string color= aParser->getColorById(Util::int2string(domainElement->getId()));
		if (domainElement->getType() == CIRCLE) 
		{
			Log::d("Creando CIRCULO");


			float radius = domainElement->getRadiusScaled();
			Log::t("Radio: %f", radius);

			EllipseView* aCircle = new EllipseView(color);
			aCircle->updateRadius(radius);
			aCircle->updatePositions(domainElement->getPosition());
			aCircle->setId(domainElement->getId());
			aFigure = aCircle;

		} 
		else if (domainElement->getType() == SQUARE) 
		{
			Log::d("Creando RECTANGULO");
			RectangleView* aRectangle = new RectangleView(color);
			aRectangle->updateVertex(domainElement->getVertex());
			aRectangle->setId(domainElement->getId());
			aFigure = aRectangle;
		}
		else if (domainElement->getType() == TRIANGLE) 
		{
			Log::d("Creando TRIANGULO");
			TriangleView* aTriangle = new TriangleView(color);
			aTriangle->updateVertex(domainElement->getVertex());
			aTriangle->setId(domainElement->getId());
			aFigure = aTriangle;
		}
		else if (domainElement->getType() == PENTA) 
		{
			Log::d("Creando PENTAGONO");
			PentagonView* aPentagon = new PentagonView(color);
			aPentagon->updateVertex(domainElement->getVertex());
			aPentagon->setId(domainElement->getId());
			aFigure = aPentagon;
		}
		else if (domainElement->getType() == HEXAGON) 
		{
			Log::d("Creando HEXAGONO");
			HexagonView* aHexagon = new HexagonView(color);
			aHexagon->updateVertex(domainElement->getVertex());
			aHexagon->setId(domainElement->getId());
			aFigure = aHexagon;
		}
		if (aFigure) 
		{
			this->gameView->putFigure(aFigure->getId(), aFigure);
			aFigure = 0;
		}

	}
}

void GameViewBuilder::buildWater()
{
	ParserYaml* aParser = ParserYaml::getInstance();
	std::string color = aParser->getEscenarioColorAgua();
	
	int scale = ESCALA_UL2PX;
	

	//ARIEL: Aca meti mano y cambie el valor del agua para que lo saque del YAML
	int heigth = (int)( Util::string2float( aParser->getEscenarioAgua() ) * scale);
	
	gameView->setWater(new WaterView(heigth, color));
}

void GameViewBuilder::buildTerrain()
{	//ARIEL: Comento porque esto dibujaba en base a poligonos
	//Log::d("Creando TERRENO en vista");
	//ParserYaml* aParser = ParserYaml::getInstance();
	//std::string color = aParser->getEscenarioColorTierra();

	//TerrainView* aTerrain = new TerrainView(color);

	//list< list< pair<float,float> > > * polygonsPoint = this->cLevel->getTerrain()->getListOfPolygons();
	//list< list< pair<float,float> > >::iterator itPolygons;

	//int countPolygons = 0;

	//std::list<std::list<tPoint>> polygonsToView;
	//for (itPolygons = polygonsPoint->begin(); itPolygons!=polygonsPoint->end(); ++itPolygons) 
	//{
	//	countPolygons++;
	//	Log::t("Creando polygono nro: %d", countPolygons);
	//	list< pair< float, float> > ::iterator itPoints;	
	//	list< pair<float,float> > points = (*itPolygons);


	//	std::list<tPoint> pointsToView;
	//	for (itPoints = points.begin(); itPoints!=points.end(); ++itPoints) 
	//	{
	//		Log::t("----> Punto: %f %f", itPoints->first, itPoints->second);
	//		tPoint aPoint = Util::convertPointUL2PXSDL(itPoints->first, itPoints->second);
	//		
	//		pointsToView.push_back(aPoint);
	//	}
	//	polygonsToView.push_back(pointsToView);
	//}

	//delete polygonsPoint;
	//
	//std::list<std::list<tPoint>>::iterator it;

	//for (it = polygonsToView.begin(); it != polygonsToView.end(); ++it)
	//{
	//	aTerrain->buildPart((*it));
	//}

	//this->gameView->setTerrain(aTerrain);
}

void GameViewBuilder::buildCharacters()
{
	WormView* aWorm = new WormView(90, 30, 50);
	WormView* aWorm2 = new WormView(91, 200, 60);
	WormView* aWorm3 = new WormView(92, 500, 100);

	// todo: obtener los id de sprite del yaml
	try 
	{
		aWorm->setSpriteWalk(SpriteConfigurator::Instance().get("wwalk"));
		aWorm2->setSpriteWalk(SpriteConfigurator::Instance().get("wwalk"));
		aWorm3->setSpriteWalk(SpriteConfigurator::Instance().get("wwalk"));
	} 
	catch (std::exception & e) 
	{
		Log::e(e.what());
	}
	this->gameView->putWorm(aWorm->getId(), aWorm);
	this->gameView->putWorm(aWorm->getId(), aWorm2);
	this->gameView->putWorm(aWorm->getId(), aWorm3);
}
