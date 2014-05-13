  #ifndef CUADRADO_H_

#include <list>

#define CUADRADO_H_
  #define DEGTORAD 0.0174532925199432957f
  #define RADTODEG 57.295779513082320876f
    
  class CuadradoTest : public Test
    {
        public:
        CuadradoTest() { 
		
			int posX = 0;
			int posY = 10;
			float angle= 45.0;
			float masa = 32.0;
			int h=10;
			int w=10;
			b2Body* m_attachment;
			b2Vec2 vertices[8];


						//Creo el poligono en Box2D
			b2FixtureDef myFixtureDef;
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_staticBody; //this will be a static body
			myBodyDef.position.Set(0, 0); //in the middle
			m_attachment = m_world->CreateBody(&myBodyDef);
			myFixtureDef.friction=2;
			

			b2PolygonShape polygonShape;

			
vertices[0] = b2Vec2(596.00000, 0.00000000)   ;
vertices[1] = b2Vec2(242.00000, 353.00000)   ;
vertices[2] = b2Vec2(194.00000, 365.00000)   ;
vertices[3] = b2Vec2(165.00000, 365.00000)   ;
vertices[4] = b2Vec2(154.00000, 358.00000)   ;
vertices[5] = b2Vec2(143.00000, 346.00000) ;
vertices[6] = b2Vec2(138.00000, 335.00000)   ;
vertices[7] = b2Vec2(122.04762, 0.00000000)  ;
			polygonShape.Set(vertices, 8); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body



vertices[0] = b2Vec2(122.04762, 0.00000000)  ;
vertices[1] = b2Vec2(136.00000, 293.00000)   ;
vertices[2] = b2Vec2(59.565220, 0.00000000)  ;
			polygonShape.Set(vertices, 3); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


													
vertices[0] = b2Vec2(74.400002, 174.60001)   ;
vertices[1] = b2Vec2(112.00000, 231.00000)   ;
vertices[2] = b2Vec2(104.00000, 229.00000)   ;
vertices[3] = b2Vec2(74.516853, 177.40451)   ;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


															   
vertices[0] = b2Vec2(130.00000, 270.00000)   ;
vertices[1] = b2Vec2(116.00000, 238.88889)   ;
vertices[2] = b2Vec2(116.00000, 216.33334)   ;
			polygonShape.Set(vertices, 3); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


														  
vertices[0] = b2Vec2(56.000000, 31.000000)   ;
vertices[1] = b2Vec2(64.000000, 113.00000)   ;
vertices[2] = b2Vec2(56.000000, 68.200012)   ;
			polygonShape.Set(vertices, 3); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

															  
vertices[0] = b2Vec2(56.000000, 68.200012)   ;
vertices[1] = b2Vec2(59.000000, 85.000000)   ;
vertices[2] = b2Vec2(56.000000, 84.000000)   ;
			polygonShape.Set(vertices, 3); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

															   
vertices[0] = b2Vec2(74.516853, 177.40451)   ;
vertices[1] = b2Vec2(100.00000, 222.00000)   ;
vertices[2] = b2Vec2(86.000000, 208.00000)   ;
vertices[3] = b2Vec2(74.604652, 179.51166)   ;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


															  
vertices[0] = b2Vec2(74.604652, 179.51166)   ;
vertices[1] = b2Vec2(80.000000, 193.00000)   ;
vertices[2] = b2Vec2(75.000000, 189.00000)   ;
			polygonShape.Set(vertices, 3); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body


															   
vertices[0] = b2Vec2(116.00000, 216.33334)   ;
vertices[1] = b2Vec2(116.00000, 237.00000)   ;
vertices[2] = b2Vec2(74.400002, 174.60001)   ;
vertices[3] = b2Vec2(68.561981, 34.487579)   ;
			polygonShape.Set(vertices, 4); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

				
				m_world->SetGravity(b2Vec2(0.0f, -10.0f));

			//
			// AGREGAR POLIGONO A BOX2D 




		
		} 
        
		void Step(Settings* settings)
        {
            //run the default physics and rendering
            Test::Step(settings); 
		}

        static Test* Create()
        {
            return new CuadradoTest;
        }
    };
  
  #endif