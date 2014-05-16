#include "GameViewBuilder.h"




GameViewBuilder::GameViewBuilder(GameController* cController, GameDomain* domain, SDLScreen * screen)
	: cController(cController), domain(domain), screen(screen)
{
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
	std::map<int,GameElement>::iterator it;
	Log::d(VIEW_BUILDER,"Construyendo Figuras. Cantidad = %d", this->domain->getDomainElements()->size() );

	ParserYaml* aParser = ParserYaml::getInstance();

	for (it = this->domain->getDomainElements()->begin(); it != this->domain->getDomainElements()->end(); ++it)
	{
		GameElement domainElement = it->second;
		FigureView* aFigure = 0;
		std::string color= aParser->getColorById(Util::int2string(domainElement.getId()));
		if (domainElement.getType() == CIRCLE) 
		{
			Log::d("Creando CIRCULO");


			float radius = domainElement.getRadiusScaled();
			Log::t("Radio: %f", radius);

			EllipseView* aCircle = new EllipseView(color);
			aCircle->updateRadius(radius);
			aCircle->updatePositions(domainElement.getPosition());
			aCircle->setId(domainElement.getId());
			aFigure = aCircle;

		} 
		else if (domainElement.getType() == SQUARE) 
		{
			Log::d("Creando RECTANGULO");
			RectangleView* aRectangle = new RectangleView(color);
			aRectangle->updateVertex(domainElement.getVertex());
			aRectangle->setId(domainElement.getId());
			aFigure = aRectangle;
		}
		else if (domainElement.getType() == TRIANGLE) 
		{
			Log::d("Creando TRIANGULO");
			TriangleView* aTriangle = new TriangleView(color);
			aTriangle->updateVertex(domainElement.getVertex());
			aTriangle->setId(domainElement.getId());
			aFigure = aTriangle;
		}
		else if (domainElement.getType() == PENTA) 
		{
			Log::d("Creando PENTAGONO");
			PentagonView* aPentagon = new PentagonView(color);
			aPentagon->updateVertex(domainElement.getVertex());
			aPentagon->setId(domainElement.getId());
			aFigure = aPentagon;
		}
		else if (domainElement.getType() == HEXAGON) 
		{
			Log::d("Creando HEXAGONO");
			HexagonView* aHexagon = new HexagonView(color);
			aHexagon->updateVertex(domainElement.getVertex());
			aHexagon->setId(domainElement.getId());
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

//void GameViewBuilder::addElementToDomain(GameElement element){
//
//	this->domainElements.insert( std::make_pair(element.getId(),element) );
//
//}




void GameViewBuilder::buildCharacters()
{

	std::map<int,GameElement>::iterator it;

	for (it = this->domain->getDomainElements()->begin(); it != this->domain->getDomainElements()->end(); ++it)
	{
		GameElement domainElement = it->second;

		if (domainElement.getType() == WORM) 
		{
			WormView* aWorm = createWorm(&domainElement);
			this->gameView->putWorm(aWorm->getId(), aWorm);
		} 
	}
	
	// todo: obtener los id de sprite del yaml
	
}

void GameViewBuilder::buildStateBar()
{
	StateBarView* stateBar = new StateBarView();
	this->gameView->setStateBar(stateBar);
}

WormView* GameViewBuilder::createWorm(GameElement * domainElement)
{
		WormView* aWorm = new WormView(	domainElement->getId());
		Log::i("Adding worm: %d, at position: %f, %f", domainElement->getId(), 
													   domainElement->getPosition().first, 
													   domainElement->getPosition().second);
		aWorm->update(domainElement);

		/*esta linea hay que borrarla, es caca*/
		//this->domain->setPlayerState("usuario",DISCONNECTED,COLOR_AMARILLO);
		/**************************************/
		std::stringstream name;
		name<<"Worm "<< domainElement->getId();

		aWorm->setColor(this->getDomain()->getPlayerColor(domainElement->getPlayerID()));
		aWorm->setPlayer(domainElement->getPlayerID());
		aWorm->setUserLabel(domainElement->getPlayerID());
		aWorm->setName(name.str());


		try 
		{
			aWorm->setSpriteWalk(SpriteConfigurator::Instance().get("wwalk"));
		} 
		catch (std::exception & e) 
		{
			Log::e(e.what());
			return NULL;
		}
		return aWorm;
}

