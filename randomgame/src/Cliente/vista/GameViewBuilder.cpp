#include "GameViewBuilder.h"


GameViewBuilder::GameViewBuilder(const std::map<int,GameElement>& map):
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
	std::map<int,GameElement>::iterator it;
	Log::d(VIEW_BUILDER,"Construyendo Figuras. Cantidad = %d", domainElements.size());
	for (it = domainElements.begin(); it != domainElements.end(); ++it)
	{
		FigureView* aFigure = 0;
		if (it->second.getType() == ElementType::CIRCLE) 
		{
			int posX= it->second.getPosition().first;
			int posY= it->second.getPosition().second;
			//	int radio = it->second.
			aFigure = new CircleView(posX, posY,20,"#00FF00FF", 0);
		} else if (it->second.getType() == ElementType::SQUARE) 
		{
			Log::d("imprimiendo vertices en vista");
			std::list<std::pair<float,float>> theVertex = it->second.getVertex();
			
			//std::list<std::pair<float,float>>::iterator itVertex;
			//// Vertex A
			//itVertex = theVertex.begin();
			//RectangleView* aRectangle = new RectangleView("#FF0000FF");
			//aRectangle->setVertexA((int)(itVertex->first), (int)(itVertex->second));
			//++it;
			//aRectangle->setVertexB((int)itVertex->first, (int)itVertex->second);
			//++it;
			//aRectangle->setVertexC((int)itVertex->first, (int)itVertex->second);
			//++it;
			//aRectangle->setVertexD((int)itVertex->first, (int)itVertex->second);

			//aFigure = aRectangle;
		}
		if (aFigure) 
		{
			container->add(aFigure);
		}

	}
}

void GameViewBuilder::buildWater(ViewGroup* container)
{
}

void GameViewBuilder::buildTerrain(ViewGroup* container)
{
}