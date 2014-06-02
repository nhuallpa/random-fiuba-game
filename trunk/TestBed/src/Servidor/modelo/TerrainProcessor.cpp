#include "TerrainProcessor.h"
#include "../../libs/Box2D/Box2D.h"
#include "Exceptions\ContourException.h"
#include "HandlerBmp\TerrainImg.h"
#include "..\..\utils\Util.h"





TerrainProcessor::TerrainProcessor(b2World* m_world, char* path,float epsilon){

	b2Body* m_attachment;
	TerrainImg* aBmpFile;
	try
	{
		aBmpFile = new TerrainImg(path);
	}
	catch (int e)
	{
		makeDefaultTerrain(m_world,5);
		return;
	}

	ContourBmp* aContourBmp = new ContourBmp(aBmpFile);

	this->height =aBmpFile->getHeight();
	this->width =aBmpFile->getWidth();

	std::vector<Position> contourVector = aContourBmp->getContourMS();

	HandleContour hc;

	contourVector = hc.rdp(contourVector,epsilon);

	b2Vec2* vec = new b2Vec2[contourVector.size()];
	int i = 0;
	for (i = contourVector.size() - 1; i>=0; i--) {
		// reducing a bit the polys
		if (i%10==0) {
			vec[i].Set( contourVector[i].getX(),contourVector[i].getY() );
		}
	}

	b2ChainShape shape;
	shape.CreateChain(vec, i);
	printf("creando");
    shape.CreateLoop(vec,i);

	b2FixtureDef myFixtureDef;
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody; //this will be a static body
	myBodyDef.position.Set(0, 0); //in the middle
	myFixtureDef.friction=0.999;
			
	myFixtureDef.userData = ( (void*)2 );
	m_attachment = m_world->CreateBody(&myBodyDef);

	myFixtureDef.shape = &shape; //change the shape of the fixture
	m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

	int* st= 0;
	m_attachment->SetUserData(st);







}

TerrainProcessor::TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale,int waterLevel)
{
	this->rangeTerrainOverWater= new list<pair<int,int>>();
	b2Body* m_attachment;
	TerrainImg* aBmpFile;
	this->aListOfPolygons= new list< list< pair<float,float> > > ();
	try
	{
		aBmpFile = new TerrainImg(path);
	}
	catch (int e)
	{
		makeDefaultTerrain(m_world,waterLevel);
		return;
	}

	ContourBmp* aContourBmp = new ContourBmp(aBmpFile);

	this->height =aBmpFile->getHeight();
	this->width =aBmpFile->getWidth();


	list< list<Position* > *>* cc =aContourBmp->getContour();
					this->maxPointTerrain=aContourBmp->getMaxPointTerrain();
		rangeTerrainOverWater =aContourBmp->getConnectedComponentsOptimized(waterLevel);
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

		result = this->getPolygonConvex(lista, epsilon, scale, height, width,waterLevel);

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
			myFixtureDef.friction=0.999;
			
			myFixtureDef.userData = ( (void*)2 );
			m_attachment = m_world->CreateBody(&myBodyDef);

			b2PolygonShape polygonShape;
			polygonShape.Set(vertices, cantDeVerticesDelPoligono); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body
			int* st= 0;
			m_attachment->SetUserData((void*)2);

		}
		itComponente++;
	}


	ContourBmp::deleteListOfListPositions(cc);
	delete aContourBmp;

}






vector<vector<b2Vec2>> TerrainProcessor::	
	getPolygonConvex(vector<b2Vec2> lista, float epsilon, int scale, int &height, int& width, int waterLevel){
		vector<vector<b2Vec2>> result;
		HandleContour hc;
		try
		{
			result = hc.getPolygonConvex(lista, epsilon, scale);
		}
		catch(ContourExp e)
		{
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
			delete this->rangeTerrainOverWater;
			this->rangeTerrainOverWater= new list<pair<int,int>>();
			this->rangeTerrainOverWater->push_back(pair<int,int>(10-waterLevel,10-waterLevel));
			this->maxPointTerrain=pair<int,int>(6,5);
		}
		return result;
}


vector<b2Vec2> TerrainProcessor::	
	getChains(vector<b2Vec2> lista, float epsilon, int scale, int &height, int& width, int waterLevel){
		vector<b2Vec2> result;
		HandleContour hc;

		result = hc.getPolygonConvex(lista, epsilon, scale,true);

		return result;
}





//	swapea los valores del b2vec
b2Vec2 TerrainProcessor::transformBmpToBox2D(b2Vec2 vertex, int height, int width)
{

	b2Vec2 nuevo;
	/*nuevo.y =((-1*vertex.x)+height-1)*(atoi((aParser->getEscenarioAltoU()).c_str() ) / (float)height);
	nuevo.x = (vertex.y)*(atoi((aParser->getEscenarioAnchoU()).c_str() ) / (float)width);*/
	nuevo.y =((-1*vertex.x)+height-1)/(float)ESCALA_UL2PX/1;
	nuevo.x = (vertex.y)/(float)ESCALA_UL2PX/1;
	return nuevo;
}

void TerrainProcessor::makeDefaultTerrain(b2World* m_world,int waterLevel)
{
	b2Body* m_attachment;
	b2Vec2 vertices[3];
	list< pair<float,float> > aListOfPoints;
	b2Vec2 unVerticeBase(9,2);
	b2Vec2 otroVerticeBase(9,8);
	b2Vec2 unVerticeCuspide(6,5);

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
	this->rangeTerrainOverWater->push_back(pair<int,int>(10-waterLevel,10-waterLevel));
	this->maxPointTerrain=pair<int,int>(6,5);
	this->height=10;
	this->width=10;

}

list< list< pair<float,float> > > * TerrainProcessor::getListOfPolygons()
{
	return this->aListOfPolygons;
}

TerrainProcessor::~TerrainProcessor(void)
{

}

pair<int,int> TerrainProcessor::getMaxPointTerrain()
		{
			return this->maxPointTerrain;
		}

list<pair<int,int>> * TerrainProcessor::getRangeTerrainOverWater()
		{
			return this->rangeTerrainOverWater;
		}

void TerrainProcessor::getRandomPosition(int* x,int* y){
	//list<pair<int,int> > *listaDeIslas= this->getContourTerrainOverWater(waterLevel);
	//iterator::pair<int,int> it = listaDeIslas->begin();
	//int random = Util::getRandom(0,listaDeIslas->size());
	//
	//it=it+random;

	//int x1 = Util::getRandom((*it).first,(*it).second)
	//
	//do{	
	//int y1= Util::getRandom(0, this->getHeight()-waterLevel);


	////recorrer la lista de poligonos y fijarte si toco tierra

}

int TerrainProcessor::getHeight()
{
	return this->height;
}

int TerrainProcessor::getWidth()
{
	return this->width;
}



TerrainProcessor::TerrainProcessor(){

}



TerrainProcessor::TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale,int waterLevel, bool chained, std::vector<b2Body*>* myTerrain, std::vector<polygon*>* myPol)
{
	this->rangeTerrainOverWater= new list<pair<int,int>>();
	b2Body* m_attachment;
	TerrainImg* aBmpFile;
	this->aListOfPolygons= new list< list< pair<float,float> > > ();
	try
	{
		aBmpFile = new TerrainImg(path);
	}
	catch (int e)
	{
		makeDefaultTerrain(m_world,waterLevel);
		return;
	}

	ContourBmp* aContourBmp = new ContourBmp(aBmpFile);

	this->height =aBmpFile->getHeight();
	this->width =aBmpFile->getWidth();


	list< list<Position* > *>* cc =aContourBmp->getContour();
	
	this->maxPointTerrain=aContourBmp->getMaxPointTerrain();
	
	rangeTerrainOverWater =aContourBmp->getConnectedComponentsOptimized(waterLevel);
	
	list< list<Position* >* >::iterator itComponente = cc->begin();
	
	b2Vec2 result[1000]; //= new b2Vec2[1000];
	int count = 0;
	while(itComponente != cc->end() )
	{
		vector<b2Vec2> lista;
		
		vector<b2Vec2> auxR;
		list<Position*>::iterator itPosition = (*itComponente)->end();
		while(itPosition != (*itComponente)->begin()){
			--itPosition;
			lista.push_back(b2Vec2((float)(*itPosition)->getX(), (float)(*itPosition)->getY()));
		}

		auxR = this->getChains(lista, epsilon, scale, height, width,waterLevel);
		int i = 0;
		b2Vec2 auxv;

		for ( i = 0; i < auxR.size() - 1; i++){
			auxv = transformBmpToBox2D( auxR[i], height, width);
			result[i+count].Set( auxv.x, (auxv.y) );
		}

		count += i;
		itComponente++;
	
	}


	// AGREGAR CHAIN A BOX2D 

	/*count--;*/
	b2ChainShape shape;
	//shape.CreateChain(result, count);
    shape.CreateLoop(result,count);

	b2FixtureDef myFixtureDef;
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody; //this will be a static body
	myBodyDef.position.Set(0, 0); //in the middle
	myFixtureDef.friction=0.999;
			
	myFixtureDef.userData = ( (void*)2 );
	m_attachment = m_world->CreateBody(&myBodyDef);

	myFixtureDef.shape = &shape; //change the shape of the fixture
	auto polygonFixture = m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the	
	b2Filter filter;
	filter.categoryBits = Shape::destructible;
	polygonFixture->SetFilterData(filter);
	myTerrain->push_back(m_attachment);
	
	

	//convert chain to polygons
	// save it


}












void TerrainProcessor::process(b2World* m_world, char* path,float epsilon, int scale,int waterLevel, bool chained, std::vector<b2Body*>* myTerrain, std::list<polygon*>* myPol)
{
	this->rangeTerrainOverWater= new list<pair<int,int>>();
	b2Body* m_attachment;
	TerrainImg* aBmpFile;
	this->aListOfPolygons= new list< list< pair<float,float> > > ();

		aBmpFile = new TerrainImg(path);


	ContourBmp* aContourBmp = new ContourBmp(aBmpFile);

	this->height =aBmpFile->getHeight();
	this->width =aBmpFile->getWidth();


	list< list<Position* > *>* cc =aContourBmp->getContour();
	
	this->maxPointTerrain=aContourBmp->getMaxPointTerrain();
	
	rangeTerrainOverWater =aContourBmp->getConnectedComponentsOptimized(waterLevel);
	
	list< list<Position* >* >::iterator itComponente = cc->begin();
	
	b2Vec2 result[1000]; //= new b2Vec2[1000];
	int count = 0;
	while(itComponente != cc->end() )
	{
		vector<b2Vec2> lista;
		
		vector<b2Vec2> auxR;
		list<Position*>::iterator itPosition = (*itComponente)->end();
		while(itPosition != (*itComponente)->begin()){
			--itPosition;
			lista.push_back(b2Vec2((float)(*itPosition)->getX(), (float)(*itPosition)->getY()));
		}

		auxR = this->getChains(lista, epsilon, scale, height, width,waterLevel);
		int i = 0;
		b2Vec2 auxv;
		polygon* pol = new polygon();	
		for ( i = 0; i < auxR.size() - 1; i++){
			auxv = transformBmpToBox2D( auxR[i], height, width);
			result[i+count].Set( auxv.x, (auxv.y) );
			pol->outer().push_back(point(auxv.x,auxv.y));	
			myPol->push_back(pol);
		}

		count += i;
		itComponente++;
	
	}


	// AGREGAR CHAIN A BOX2D 

	/*count--;*/
	b2ChainShape shape;
	//shape.CreateChain(result, count);
    shape.CreateLoop(result,count);

	b2FixtureDef myFixtureDef;
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody; //this will be a static body
	myBodyDef.position.Set(0, 0); //in the middle
	myFixtureDef.friction=0.999;
			
	myFixtureDef.userData = ( (void*)2 );
	m_attachment = m_world->CreateBody(&myBodyDef);

	myFixtureDef.shape = &shape; //change the shape of the fixture
	auto polygonFixture = m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the	
	b2Filter filter;
	filter.categoryBits = Shape::destructible;
	polygonFixture->SetFilterData(filter);
	myTerrain->push_back(m_attachment);
	
	//polygon* pol = new polygon();			
	//for ( int j=0; j < shape.m_count ; j++){
	//	pol->outer().push_back(point(shape.m_vertices[j].x,shape.m_vertices[j].y));	
	//	myPol->push_back(pol);
	//}

	


}