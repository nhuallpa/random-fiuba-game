#include "TerrainProcessor.h"
#include "../../libs/Box2D/Box2D.h"
#include "Exceptions\ContourException.h"
#include "HandlerBmp\TerrainImg.h"
#include "..\..\utils\Util.h"

TerrainProcessor::TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale)
{
	b2Body* m_attachment;
	TerrainImg* aBmpFile;
	this->aListOfPolygons= new list< list< pair<float,float> > > ();
	try
	{
		aBmpFile = new TerrainImg(path);
	}
	catch (int e)
	{
		makeDefaultTerrain(m_world);
		return;
	}

	ContourBmp* aContourBmp = new ContourBmp(aBmpFile);
	int height =aBmpFile->getHeight();
	int width =aBmpFile->getWidth();


	list< list<Position* > *>* cc =aContourBmp->getContour();
	list< list<Position* >* >::iterator itComponente = cc->begin();
	while(itComponente != cc->end() )
	{
		vector<b2Vec2> lista;
		vector<vector<b2Vec2>> result;

		list<Position*>::iterator itPosition = (*itComponente)->end();
		while(itPosition != (*itComponente)->begin()){
			--itPosition;
			lista.push_back(b2Vec2((float)(*itPosition)->getX(), (float)(*itPosition)->getY()));
		}

		result = this->getPolygonConvex(lista, epsilon, scale, height, width);

		for(int nroDePoligono=0; nroDePoligono< result.size(); nroDePoligono++)
		{
			vector<b2Vec2> aPolygon= result[nroDePoligono];
			int cantDeVerticesDelPoligono = aPolygon.size();
			b2Vec2 vertices[8];
			list< pair<float,float> > aListOfPoints;
			for(int nroVertice=0; nroVertice < cantDeVerticesDelPoligono; nroVertice++)
			{
				b2Vec2 unVertice = aPolygon[nroVertice];
				vertices[nroVertice] = this->transformBmpToBox2D(unVertice,height  ,width  );
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
			int* st= 0;
			m_attachment->SetUserData(st);

		}
		itComponente++;
	}


	ContourBmp::deleteListOfListPositions(cc);
	delete aContourBmp;

}






vector<vector<b2Vec2>> TerrainProcessor::	
	getPolygonConvex(vector<b2Vec2> lista, float epsilon, int scale, int &height, int& width){
		vector<vector<b2Vec2>> result;
		HandleContour hc;
		try
		{
			result = hc.getPolygonConvex(lista, epsilon, scale);
		}
		catch(ContourExp e)
		{
			Log::i(HANDLE_CONTOUR,"Error al procesar el archivo BMP, se creara uno por defecto.");
			b2Body* m_attachment;
			b2Vec2 vertices[3];
			height=10;
			width=10;
			vector< b2Vec2 > aListOfPoints;
			b2Vec2 unVerticeBase(9,3);
			b2Vec2 otroVerticeBase(9,7);
			b2Vec2 unVerticeCuspide(5,5);

			aListOfPoints.push_back(unVerticeBase);
			aListOfPoints.push_back(otroVerticeBase);
			aListOfPoints.push_back(unVerticeCuspide);

			result.push_back(aListOfPoints);

		}
		return result;
}







//	swapea los valores del b2vec
b2Vec2 TerrainProcessor::transformBmpToBox2D(b2Vec2 vertex, int height, int width)
{
	ParserYaml* aParser = ParserYaml::getInstance();
	b2Vec2 nuevo;
	nuevo.y =((-1*vertex.x)+height-1)*(atoi((aParser->getEscenarioAltoU()).c_str() ) / (float)height);
	nuevo.x = (vertex.y)*(atoi((aParser->getEscenarioAnchoU()).c_str() ) / (float)width);
	return nuevo;
}

void TerrainProcessor::makeDefaultTerrain(b2World* m_world)
{
	b2Body* m_attachment;
	b2Vec2 vertices[3];
	list< pair<float,float> > aListOfPoints;
	b2Vec2 unVerticeBase(9,3);
	b2Vec2 otroVerticeBase(9,7);
	b2Vec2 unVerticeCuspide(5,5);

	vertices[0] = this->transformBmpToBox2D(unVerticeBase, 10,10);
	vertices[1] = this->transformBmpToBox2D(otroVerticeBase, 10,10);
	vertices[2] = this->transformBmpToBox2D(unVerticeCuspide, 10,10);

	pair<float,float> aPosition93(vertices[0].x,vertices[0].y);
	pair<float,float> aPosition97(vertices[1].x,vertices[1].y);
	pair<float,float> aPosition55(vertices[2].x,vertices[2].y);

	aListOfPoints.push_back(aPosition93);
	aListOfPoints.push_back(aPosition97);
	aListOfPoints.push_back(aPosition55);

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
	polygonShape.Set(vertices, 3); //pass array to the shape

	myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body
	int* st= 0;
	m_attachment->SetUserData(st);

}

list< list< pair<float,float> > > * TerrainProcessor::getListOfPolygons()
{
	return this->aListOfPolygons;
}

TerrainProcessor::~TerrainProcessor(void)
{

}


void TerrainProcessor::getRandomPosition(int* x,int* y){
	int random = Util::getRandom(0,10);
}
