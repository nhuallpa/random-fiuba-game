 #ifndef CUADRADOAGUA_H_
#define CUADRADOAGUA_H_
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define INCLINACION 30
#include <set>
#include <vector>
#include <iostream>
#include <math.h>
class InclinacionTest;    

class MyContactListener : public b2ContactListener
  {

	

    void BeginContact(b2Contact* contact) {
  
      //check if fixture A is body (2)
      b2WorldManifold worldManifold;
	   //worldManifold.normal; //b2Vec2

	  if ( (int)(contact->GetFixtureA()->GetUserData()) == 2 ){
		  
    contact->GetWorldManifold(&worldManifold);

    //now you can use these properties for whatever you need
   
		  //contact->GetFixtureA()->GetBody()->ApplyForce(b2Vec2(0,1000),contact->GetFixtureA()->GetBody()->GetWorldCenter());
														
	  }
        
  
      //check if fixture B was the body
      if ( (int)(contact->GetFixtureB()->GetUserData()) == 2 ){
		  contact->GetWorldManifold(&worldManifold);
		  //contact->GetFixtureB()->GetBody()->ApplyForce(b2Vec2(0,10000),contact->GetFixtureB()->GetBody()->GetWorldCenter());
	  }
        
  
    }
  
    void EndContact(b2Contact* contact) {
  
	}
  };

  class InclinacionTest : public Test
    {
        public:
					b2Body* bodies[3];
			MyContactListener myContactListenerInstance;
					 bool forceOn;

        InclinacionTest() { 

			forceOn = false;
			m_world->SetContactListener(&myContactListenerInstance);
        
            //body definition
            b2BodyDef myBodyDef;
            myBodyDef.type = b2_dynamicBody;
            
            //hexagonal shape definition
            b2PolygonShape polygonShape;
            b2Vec2 vertices[6];
            for (int i = 0; i < 6; i++) {
                float angle = -i/6.0 * 360 * DEGTORAD;
                vertices[i].Set(sinf(angle), cosf(angle));
            }
 
            polygonShape.Set(vertices, 6);
  
            //fixture definition
            b2FixtureDef myFixtureDef;
            myFixtureDef.shape = &polygonShape;
            myFixtureDef.density = 1;
			myFixtureDef.restitution = 0;
			myFixtureDef.friction = 0.8;
			myFixtureDef.userData = (void*)2;
    

		    for (int i = 0; i < 3; i++) {
			  myBodyDef.position.Set(-10+i*10, 20);
			  bodies[i] = m_world->CreateBody(&myBodyDef);
			  bodies[i]->CreateFixture(&myFixtureDef);
	  
			  bodies[i]->SetFixedRotation(true);
			}

      
    //make a static floor to drop things on
	b2FixtureDef myFixtureDefGround;
    myFixtureDefGround.shape = &polygonShape;
    myFixtureDefGround.density = 1;
	myFixtureDefGround.friction = 0.9;
	myFixtureDefGround.userData = (void*)1;
	myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0); //middle, bottom
    b2Body* staticBody = m_world->CreateBody(&myBodyDef);  
	polygonShape.SetAsBox(100,1,b2Vec2(0,0),INCLINACION*DEGTORAD);		
    staticBody->CreateFixture(&myFixtureDefGround); //add a fixture to the body



                } 
        
                void Step(Settings* settings)
        {
            //run the default physics and rendering
            Test::Step(settings); 
						if (forceOn){
				bodies[0]->ApplyForce( b2Vec2(50,0), bodies[0]->GetWorldCenter() );
				bodies[2]->ApplyForce( b2Vec2(80*0.7,80*0.64), bodies[0]->GetWorldCenter() );
				
						}
                }

        static Test* Create()
        {
            return new InclinacionTest;
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