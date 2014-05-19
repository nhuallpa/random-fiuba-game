#ifndef MOVIMIENTO_H_
#define MOVIMIENTO_H_
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#include <set>
#include <vector>
#include <iostream>
#include <math.h>
    
  class MovimientoTest : public Test
    {
        public:
		b2Body* bodies[3];
		 bool forceOn;
		 bool forceOff;
        MovimientoTest() { 


  forceOn = false;
  forceOff = false;

    //body definition
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    
    //shape definition
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(1, 1); //a 2x2 rectangle
  
    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 0.5;
    
    //create identical bodies in different positions
    for (int i = 0; i < 3; i++) {
      myBodyDef.position.Set(-10+i*10, 20);
      bodies[i] = m_world->CreateBody(&myBodyDef);
      bodies[i]->CreateFixture(&myFixtureDef);
    }
    

	//make a static floor to drop things on
	b2FixtureDef myFixtureDefGround;
    myFixtureDefGround.shape = &polygonShape;
    myFixtureDefGround.density = 1;
	myFixtureDefGround.friction = 0.5;

    //a static floor to drop things on
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
	polygonShape.SetAsBox(20,1);
    m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDefGround);
	}
		               
		void Step(Settings* settings)
        {
		//run the default physics and rendering
            Test::Step(settings); 

			if (forceOn)
				bodies[0]->ApplyForce( b2Vec2(50,0), bodies[0]->GetWorldCenter() );
			if (forceOff)
				bodies[0]->SetLinearVelocity(b2Vec2(0,0));

        }

        static Test* Create()
        {
            return new MovimientoTest;
        }



		void Keyboard(unsigned char key)
  {
    switch (key)
    {
      case 'q':
        //apply gradual force upwards
        forceOn = !forceOn;//toggle bool value
		  //bodies[0]->ApplyForce( b2Vec2(50,0), bodies[0]->GetWorldCenter() );
        break;
      case 'w':
        //apply immediate force upwards
        forceOff = !forceOff;
        break;
      case 'e':
        //teleport or 'warp' to new location
        bodies[2]->SetTransform( b2Vec2(10,20), 0 );
        break;
      default:
        //run default behaviour
        Test::Keyboard(key);
    }
  }



    };
  
  #endif