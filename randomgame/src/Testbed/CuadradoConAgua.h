  #ifndef CUADRADOAGUA_H_
  #define CUADRADOAGUA_H_
  #define DEGTORAD 0.0174532925199432957f
  #define RADTODEG 57.295779513082320876f
#include <set>
#include <vector>
#include <iostream>

#include "iforce2d_Buoyancy_functions.h"
typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;

  class CuadradoConAguaTest : public Test
    {
        public:
		std::set<fixturePair> m_fixturePairs;
        CuadradoConAguaTest() { 
		
			int posX = 0;
			int posY = 10;
			float angle= 45.0;
			float masa = 32.0;
			int h=10;
			int w=10;

			m_world->SetGravity(b2Vec2(0.0f, -10.0f));
			b2Vec2 center = b2Vec2( posX+w/2, posY+h/2 );
			int magicNumber = 32;
			


			b2BodyDef myBodyDef;
			myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
			myBodyDef.position.Set(posX+w/2, posY+h/2); //set the starting position
			myBodyDef.angle = (angle * DEGTORAD); //set the starting angle

			b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);
			b2PolygonShape boxShape;
			boxShape.SetAsBox(h,w,center,angle * DEGTORAD);
			b2FixtureDef boxFixtureDef;
			boxFixtureDef.shape = &boxShape;
			boxFixtureDef.density = 1.0f;
			dynamicBody->CreateFixture(&boxFixtureDef);
			dynamicBody->SetUserData(&magicNumber);
			std::cout << "Primero: " << dynamicBody->GetUserData() << std::endl;


			// Ahora creo el agua
			
			center = b2Vec2( posX, posY-200 );
			
			b2PolygonShape waterShape;
			boxShape.SetAsBox(w*100,h*10,center,0);
			b2FixtureDef waterFixtureDef;
			waterFixtureDef.shape = &waterShape;
			waterFixtureDef.isSensor = true;


			b2BodyDef bd;
			bd.type = b2BodyType(0);
			bd.position.Set(-1.112629318237305e+01f, 1.750797271728516e+00f);
			bd.angle = 0.000000000000000e+00f;
			bd.linearVelocity.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
			bd.angularVelocity = 0.000000000000000e+00f;
			bd.linearDamping = 0.000000000000000e+00f;
			bd.angularDamping = 0.000000000000000e+00f;
			bd.allowSleep = bool(4);
			bd.awake = bool(2);
			bd.fixedRotation = bool(0);
			bd.bullet = bool(0);
			bd.active = bool(32);
			bd.gravityScale = 1.000000000000000e+00f;
			b2Body* waterBody = m_world->CreateBody(&bd);


			b2FixtureDef fd;
			fd.friction = 2.000000029802322e-01f;
			fd.restitution = 0.000000000000000e+00f;
			fd.density = 2.000000000000000e+00f;
			fd.isSensor = bool(1);
			fd.filter.categoryBits = uint16(1);
			fd.filter.maskBits = uint16(65535);
			fd.filter.groupIndex = int16(0);
			b2PolygonShape shape;
			b2Vec2 vs[8];
			shape.SetAsBox(w*100,h*10,center,0);
			/*vs[0].Set(-5.544052124023438e-01f, -1.515119433403015e+00f);
			vs[1].Set(-5.544052124023438e-01f, 7.516476631164551e+00f);
			vs[2].Set(-4.341683959960938e+01f, 7.516476631164551e+00f);
			vs[3].Set(-4.341683959960938e+01f, -1.515119433403015e+00f);
			shape.Set(vs, 4);*/

			fd.shape = &shape;

			waterBody->CreateFixture(&fd);





		
		} 

		void BeginContact(b2Contact* contact)
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        //This assumes every sensor fixture is fluid, and will interact
        //with every dynamic body.
        if ( fixtureA->IsSensor() &&
             fixtureB->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.insert( make_pair(fixtureA, fixtureB) );
        else if ( fixtureB->IsSensor() &&
                  fixtureA->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.insert( make_pair(fixtureB, fixtureA) );
    }

    void EndContact(b2Contact* contact)
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        //This check should be the same as for BeginContact, but here
        //we remove the fixture pair
        if ( fixtureA->IsSensor() &&
             fixtureB->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.erase( make_pair(fixtureA, fixtureB) );
        else if ( fixtureB->IsSensor() &&
                  fixtureA->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.erase( make_pair(fixtureB, fixtureA) );
    }
        
		void Step(Settings* settings)
        {
            //run the default physics and rendering
            Test::Step(settings); 

			//go through all buoyancy fixture pairs and apply necessary forces
        std::set<fixturePair>::iterator it = m_fixturePairs.begin();
        std::set<fixturePair>::iterator end = m_fixturePairs.end();
        while (it != end) {

            //fixtureA is the fluid
            b2Fixture* fixtureA = it->first;
			std::cout << it->second->GetBody()->GetUserData() << std::endl;
            b2Fixture* fixtureB = it->second;

            float density = fixtureA->GetDensity();


			//cosas turbias
			
            std::vector<b2Vec2> intersectionPoints;
			if ( findIntersectionOfFixtures(fixtureA, fixtureB, intersectionPoints) ) {
				b2Vec2 vel=b2Vec2(0,-15);
				it->second->GetBody()->SetLinearVelocity(vel);

                //find centroid
                //float area = 0;
                //b2Vec2 centroid = ComputeCentroid( intersectionPoints, area);

                //apply buoyancy force
                //float displacedMass = fixtureA->GetDensity() * area;
                //b2Vec2 gravity( 0, -4 );
                //b2Vec2 buoyancyForce = displacedMass * -gravity;
                //fixtureB->GetBody()->ApplyForce( buoyancyForce, centroid );


			//	//apply complex drag
   //             float dragMod = 0.25f;//adjust as desired
   //             float liftMod = 0.25f;//adjust as desired
   //             float maxDrag = 2000;//adjust as desired
   //             float maxLift = 500;//adjust as desired
   //             for (int i = 0; i < intersectionPoints.size(); i++) {
   //                 b2Vec2 v0 = intersectionPoints[i];
   //                 b2Vec2 v1 = intersectionPoints[(i+1)%intersectionPoints.size()];
   //                 b2Vec2 midPoint = 0.5f * (v0+v1);

   //                 //find relative velocity between object and fluid at edge midpoint
   //                 b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( midPoint ) -
   //                         fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( midPoint );
   //                 float vel = velDir.Normalize();

   //                 b2Vec2 edge = v1 - v0;
   //                 float edgeLength = edge.Normalize();
   //                 b2Vec2 normal = b2Cross(-1,edge);
   //                 float dragDot = b2Dot(normal, velDir);
   //                 if ( dragDot < 0 )
   //                     continue;//normal points backwards - this is not a leading edge

   //                 //apply drag
   //                 float dragMag = dragDot * dragMod * edgeLength * density * vel * vel;
   //                 dragMag = b2Min( dragMag, maxDrag );
   //                 b2Vec2 dragForce = dragMag * -velDir;
   //                 fixtureB->GetBody()->ApplyForce( dragForce, midPoint );

   //                 //apply lift
   //                 float liftDot = b2Dot(edge, velDir);
   //                 float liftMag =  dragDot * liftDot * liftMod * edgeLength * density * vel * vel;
   //                 liftMag = b2Min( liftMag, maxLift );
   //                 b2Vec2 liftDir = b2Cross(1,velDir);
   //                 b2Vec2 liftForce = liftMag * liftDir;
   //                 fixtureB->GetBody()->ApplyForce( liftForce, midPoint );
			//}

			}
			 ++it;
			}
		}

        static Test* Create()
        {
            return new CuadradoConAguaTest;
        }



    };
  
  #endif