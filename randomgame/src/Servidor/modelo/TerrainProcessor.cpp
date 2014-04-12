#include "TerrainProcessor.h"
#include "../../libs/Box2D/Box2D.h"
#include "Exceptions\ContourException.h"

TerrainProcessor::TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale)
{
	b2Body* m_attachment;
	Bmp* aBmpFile = new Bmp(path);
	ContourBmp* aContourBmp = new ContourBmp(aBmpFile);
	this->aListOfPolygons= new list< list< pair<float,float> > > ();


	list< list<Position* > *>* cc =aContourBmp->getContour();
	list< list<Position* >* >::iterator itComponente = cc->begin();
	while(itComponente != cc->end() )
	{
		vector<b2Vec2> lista;
		vector<vector<b2Vec2>> result;
		HandleContour hc;

		list<Position*>::iterator itPosition = (*itComponente)->end();
		while(itPosition != (*itComponente)->begin()){
			--itPosition;
			lista.push_back(b2Vec2((float)(*itPosition)->getX(), (float)(*itPosition)->getY()));
		}
		try
		{
			result = hc.getPolygonConvex(lista, epsilon, scale);
		}
		catch(ContourExp e)
		{
			Log::e(HANDLE_CONTOUR, e.what());
			lista.clear();
		}

		for(int nroDePoligono=0; nroDePoligono< result.size(); nroDePoligono++)
		{
			vector<b2Vec2> aPolygon= result[nroDePoligono];
			int cantDeVerticesDelPoligono = aPolygon.size();
			b2Vec2 vertices[8];
			list< pair<float,float> > aListOfPoints;
			for(int nroVertice=0; nroVertice < cantDeVerticesDelPoligono; nroVertice++)
			{
				b2Vec2 unVertice = aPolygon[nroVertice];
				vertices[nroVertice] = this->transformBmpToBox2D(unVertice, aBmpFile->getHeight(), aBmpFile->getWidth());
				pair<float,float> aPosition(vertices[nroVertice].x,vertices[nroVertice].y);
				aListOfPoints.push_back(aPosition);
			}

			aListOfPolygons->push_back(aListOfPoints);
			//
			// AGREGAR POLIGONO A BOX2D 

			//Creo el poligono en Box2D
			b2FixtureDef myFixtureDef;
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_staticBody; //this will be a static body
			myBodyDef.position.Set(0, 0); //in the middle
			m_attachment = m_world->CreateBody(&myBodyDef);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, cantDeVerticesDelPoligono); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

		}
		itComponente++;
	}


	ContourBmp::deleteListOfListPositions(cc);

	cout << "Neo: \"I'm in\" " << endl;


	delete aContourBmp;

}



//	swapea los valores del b2vec
b2Vec2 TerrainProcessor::transformBmpToBox2D(b2Vec2 vertex, int height, int width)
	{
		ParserYaml* aParser = ParserYaml::getInstance();
		b2Vec2 nuevo;
		nuevo.y =((-1*vertex.x)+height-1)*(atoi((aParser->getEscenarioAltoU()).c_str() ) / height);
		nuevo.x = (vertex.y)*(atoi((aParser->getEscenarioAnchoU()).c_str() ) / width);
		return nuevo;
	}

list< list< pair<float,float> > > * TerrainProcessor::getListOfPolygons()
{
	return this->aListOfPolygons;
}

TerrainProcessor::~TerrainProcessor(void)
{
}
