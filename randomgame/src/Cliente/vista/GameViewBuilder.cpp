#include "GameViewBuilder.h"


GameViewBuilder::GameViewBuilder(const std::map<int,GameElement*>& map):
						domainElements(map)
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

	for (it = domainElements.begin(); it != domainElements.end(); ++it)
	{
		GameElement* domainElement = it->second;
		FigureView* aFigure = 0;
		if (domainElement->getType() == ElementType::CIRCLE) 
		{
			int posX= domainElement->getPosition().first;
			int posY= domainElement->getPosition().second;

			aFigure = new CircleView(posX, posY,20,"#00FF00FF", 0);
		} 
		else if (domainElement->getType() == ElementType::SQUARE) 
		{
			Log::d("Creando rectangulo del RECTANGULO");
			RectangleView* aRectangle = new RectangleView("#FF0000FF");
			aRectangle->updateVertex(domainElement->getVertex());
			aRectangle->setId(domainElement->getId());
			aFigure = aRectangle;
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
	int heigth = 100;
	
	container->add(new WaterView(heigth, color)); 
}

void GameViewBuilder::buildTerrain(ViewGroup* container)
{
}