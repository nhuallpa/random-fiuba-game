#include "TerrainProcessor.h"
#include "../../libs/Box2D/Box2D.h"

TerrainProcessor::TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale)
{
	b2Body* m_attachment;
	Bmp* aBmpFile = new Bmp(path);
	ContourBmp* aContourBmp = new ContourBmp(aBmpFile);

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
			result = hc.getPolygonConvex(lista, 0.5, 100);
		}
		catch(exception e)
		{
			lista.clear();
		}

		for(int nroDePoligono=0; nroDePoligono< result.size(); nroDePoligono++)
		{
			vector<b2Vec2> aPolygon= result[nroDePoligono];
			int cantDeVerticesDelPoligono = aPolygon.size();
			b2Vec2 vertices[8];
			for(int nroVertice=0; nroVertice < cantDeVerticesDelPoligono; nroVertice++)
			{
				b2Vec2 unVertice = aPolygon[nroVertice];
				vertices[nroVertice] = this->transformBmpToBox2D(unVertice, aBmpFile->getHeight());
			}
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




			//o 
			//AGREGAR A UNA LISTA Y DEVOLVERLA
			//o
			//REZAR Y QUE BAJE JESUS A HACER MAGIA CON BOX2D
			//o
			//AGREGAR POLIGONO A SDL
			//
		}
		itComponente++;
	}

	//vector<b2Vec2>::iterator jt = (*result.begin()).begin();
	//vector<vector<b2Vec2>>::iterator itPolygon =result.begin();

	//while( itPolygon != result.end())
	//{
	//	vector<b2Vec2>::iterator itPolygonVertex = itPolygon->begin();
	//	const int tam= itPolygon->size();

	//		b2Vec2* vertex= new b2Vec2[tam];
	//		for(int i=0; i<tam;i++)
	//		{
	//			
	//			vertex[i] = transformBmpToBox2D(*itPolygonVertex, aBmpFile->getHeight());
	//			itPolygonVertex++;
	//		}

	//		//Creo el poligono en Box2D
	//		b2BodyDef myBodyDef;
	//		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//		myBodyDef.position.Set(0, 0); //in the middle
	//		m_attachment = m_world->CreateBody(&myBodyDef);

	//		b2PolygonShape polygonShape;
	//		polygonShape.Set(vertex, tam); //pass array to the shape
	//		b2FixtureDef myFixtureDef;
	//		myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//		m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

	//	itPolygon++;
	//}


	//	vector<b2Vec2> vec = (*itt);
	//	fputs("Primer poligono \n",pepe);
	//	for(jt = vec.begin(); jt != vec.end(); jt++){
	//		sprintf(line, "(%2.4f,%2.4f)\n", (*jt).x,(*jt).y);
	//		fputs(line, pepe);
	//	}
	//	fputs("\n\n", pepe);
	//}




	ContourBmp::deleteListOfListPositions(cc);

	cout << "Neo: \"I'm in\" " << endl;


	delete aContourBmp;

	//b2Vec2 vertices[8];



	////Poligono 1 de la componente 2
	//vertices[0].Set(111,487);
	//vertices[1].Set(111,426);
	//vertices[2].Set( 240, 287);
	//vertices[3].Set( 369,287  );
	//vertices[4].Set( 434,320  );
	//vertices[5].Set( 447, 333 );
	//vertices[6].Set( 448, 335);
	//vertices[7].Set(516,478);


	//b2BodyDef myBodyDef;
	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//b2PolygonShape polygonShape;
	//polygonShape.Set(vertices, 8); //pass array to the shape
	//b2FixtureDef myFixtureDef;
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

	////Poligono 2
	//vertices[0].Set(24,25);
	//vertices[1].Set(29,25);
	//vertices[2].Set( 29, 26);
	//vertices[3].Set( 24,26  );
	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//polygonShape.Set(vertices, 4); //pass array to the shape
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

	////Poligono 3
	//vertices[0].Set(24,17);
	//vertices[1].Set(25, 17);
	//vertices[2].Set( 26, 25);
	//vertices[3].Set( 24,25  );
	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//polygonShape.Set(vertices, 4); //pass array to the shape
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


	////Poligono 6
	//vertices[0].Set(6,14);
	//vertices[1].Set(6,8 );
	//vertices[2].Set( 16, 8);
	//vertices[3].Set( 16,14  );
	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//polygonShape.Set(vertices, 4); //pass array to the shape
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body



	////Poligono 5
	//vertices[0].Set(1,18);
	//vertices[1].Set(1, 15);
	//vertices[2].Set( 5, 15);
	//vertices[3].Set( 5,18  );
	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//polygonShape.Set(vertices, 4); //pass array to the shape
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body



	////Poligono 4
	//vertices[0].Set(5,18);
	//vertices[1].Set(5, 14);
	//vertices[2].Set( 17, 14);
	//vertices[3].Set( 17,18  );
	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//polygonShape.Set(vertices, 4); //pass array to the shape
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


	////Poligono 3
	//vertices[0].Set(1,18);
	//vertices[1].Set(18, 18);
	//vertices[2].Set( 18, 19);
	//vertices[3].Set( 1,19  );
	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//polygonShape.Set(vertices, 4); //pass array to the shape
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


	////Poligono 2
	//vertices[0].Set(1,19);
	//vertices[1].Set(20, 19);
	//vertices[2].Set( 20, 22);
	//vertices[3].Set( 1,22  );

	//myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	//myBodyDef.position.Set(0, 0); //in the middle
	//m_attachment = m_world->CreateBody(&myBodyDef);

	//polygonShape.Set(vertices, 4); //pass array to the shape
	//myFixtureDef.shape = &polygonShape; //change the shape of the fixture
	//m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body




}



//	swapea los valores del b2vec
b2Vec2 TerrainProcessor::transformBmpToBox2D(b2Vec2 vertex, int height)
	{
		b2Vec2 nuevo;
		nuevo.y =(-1*vertex.x)+height-1;
		nuevo.x = vertex.y;
		return nuevo;
	}

TerrainProcessor::~TerrainProcessor(void)
{
}
