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
			Log::d("Imprimiendo vertices del RECTANGULO");
			//std::list<std::pair<float,float>> theVertex = it->second.getVertex();
			//
			//std::list<std::pair<float,float>>::iterator itVertex;
			//// Vertex A
			//itVertex = theVertex.begin();
			//RectangleView* aRectangle = new RectangleView("#FF0000FF");
			//try {
			//	++itVertex;
			//	aRectangle->setVertexA((int)(itVertex->first), (int)(itVertex->second));
			//	Log::d("Va[%f, %f]", (itVertex->first), (itVertex->second));
			//	++itVertex;
			//	aRectangle->setVertexB((int)itVertex->first, (int)itVertex->second);
			//	Log::d("Vb[%f, %f]", (itVertex->first), (itVertex->second));
			//	++itVertex;
			//	aRectangle->setVertexC((int)itVertex->first, (int)itVertex->second);
			//	Log::d("Vc[%f, %f]", (itVertex->first), (itVertex->second));
			//	++itVertex;
			//	aRectangle->setVertexD((int)itVertex->first, (int)itVertex->second);
			//	Log::d("Vd[%f, %f]", (itVertex->first), (itVertex->second));
			//} 
			//catch (std::exception & e) 
			//{
			//	Log::d("Excepcion: %s", e.what());
			//}


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