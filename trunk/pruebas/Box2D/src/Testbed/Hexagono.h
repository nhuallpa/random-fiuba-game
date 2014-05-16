#ifndef HEXAGONO_H_
#define HEXAGONO_H_
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#include <math.h>
    
  class HexagonoTest : public Test
    {
        public:
        HexagonoTest() { 
		
			int posX = 0;
			int posY = 10;
			float angle= 45.0;
			float masa = 32.0;
			float scale = 2.0;
			bool isFixed = false;


			//body definition
			b2BodyDef myBodyDef;
			if (!isFixed){
				myBodyDef.type = b2_dynamicBody;
			}else{
				myBodyDef.type = b2_staticBody;
			}
    
			//hexagonal shape definition
			b2PolygonShape polygonShape;
			b2Vec2 vertices[6];
			for (int i = 0; i < 6; i++) {
			  float angle = -i/6.0 * 360 * DEGTORAD;
			  vertices[i].Set(scale*sinf(angle), scale*cosf(angle));
			}
 
			polygonShape.Set(vertices, 6);
  
			//fixture definition
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &polygonShape;
			myFixtureDef.density = 1;
    
			//create dynamic body
			myBodyDef.position.Set(posX, posY);
			b2Body* body = m_world->CreateBody(&myBodyDef);
			body->CreateFixture(&myFixtureDef);


		} 
        
		void Step(Settings* settings)
        {
            //run the default physics and rendering
            Test::Step(settings); 
		}

        static Test* Create()
        {
            return new HexagonoTest;
        }
    };
  
  #endif