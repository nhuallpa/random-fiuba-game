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

void GameViewBuilder::buildSky(ViewGroup* container)
{
	container->add(new SkyView("sky"));
}

void GameViewBuilder::buildFigures(ViewGroup* container)
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
		} else if (domainElement->getType() == ElementType::SQUARE) 
		{
			RectangleView* aRectangle;
			Log::d("Creando rectangulo del RECTANGULO");
			aRectangle = new RectangleView("#FF0000FF");
			int vertexIndex = 1;

			std::list<std::pair<float,float>> & theVertex = domainElement->getVertex();
			std::list<std::pair<float,float>>::iterator itVertex;
				
			for ( itVertex = theVertex.begin();
					itVertex != theVertex.end();
					++itVertex) 
			{
				Log::t("Vertex %d [%f, %f]", vertexIndex ,(itVertex->first), (itVertex->second));
				int x = (int)(itVertex->first) / 10;
				int y = (int)(itVertex->second);
				switch (vertexIndex)
				{
					case 1:
						aRectangle->setVertexA(x, y);
						break;
					case 2:
						aRectangle->setVertexB(x, y);
						break;
					case 3:
						aRectangle->setVertexC(x, y);
						break;
					case 4:
						aRectangle->setVertexD(x, y);
						break;
				}
				vertexIndex++;
			}
			aFigure = aRectangle;
		}
		if (aFigure) 
		{
			container->add(aFigure);
		}

	}
}

void GameViewBuilder::buildWater(ViewGroup* container)
{
	//ParserYaml* aParser = ParserYaml::getInstance();
	//std::string color = aParser->getEscenarioColorAgua();
	//
	///*** TODO: retrive from domain*/
	//int heigth = 100;
	//
	//container->add(new WaterView(heigth, color)); 
}

void GameViewBuilder::buildTerrain(ViewGroup* container)
{
}