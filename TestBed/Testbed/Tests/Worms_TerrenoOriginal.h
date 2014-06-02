
/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <cstdio>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\TerrainProcessor.h"
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\Physics\Bodies\Worm\Worm2d.h"
#include "TerrenoConWorms.h"
//#include "geometry.hpp"
#include <unordered_set>
#define BOOST_GEOMETRY_OVERLAY_NO_THROW
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/math/constants/constants.hpp>
#define PI 3.141592654f

namespace bg = boost::geometry;



using namespace std;



#ifndef WORMSTORIG_H
#define WORMSTORIG_H

#define FUERZA_MOV 150
#define FUERZA_SALTO 85
#define VELOCIDAD 10



class WormsTOrig;

        b2Vec2 normals1[3];


class MyContactListener1 : public b2ContactListener
  {

        

    void BeginContact(b2Contact* contact) {
  
      ////check if fixture A is body (2)
      //b2WorldManifold worldManifold;

      //    if ( (int)(contact->GetFixtureA()->GetUserData()) == 3 ){  
      //          contact->GetWorldManifold(&worldManifold);
      //          normals1[0].x = worldManifold.normal.x;
      //          normals1[0].y = worldManifold.normal.y;
      //          contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
      //    }
      //  
  
      ////check if fixture B was the body
      //if ( (int)(contact->GetFixtureB()->GetUserData()) == 3 ){
      //          contact->GetWorldManifold(&worldManifold);
      //          normals1[0].x = worldManifold.normal.x;
      //          normals1[0].y = worldManifold.normal.y;
      //          contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
      //    }
      //  
    } //Begin Contact - END
  

    void EndContact(b2Contact* contact) {
                //if ( (int)(contact->GetFixtureB()->GetUserData()) == 3 ){
                //        
                //        contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0,-10));
                //}

                //if ( (int)(contact->GetFixtureA()->GetUserData()) == 3 ){
                //        contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0,-10));

                //}

        }
  };


class WormsTOrig : public Test
{
public:

        b2Body* bodies[3];

		std::vector<b2Body*> myTerrain;
		std::list<polygon*>* myPol;
        MyContactListener1 myContactListenerInstance;
        keyAction action;
		bool mouseDown;

		polygon makeConvexRing(b2Vec2 position, float radius, int vertices)
		{
			polygon convexRing;
			const float theta = boost::math::constants::two_pi<float>() / static_cast<float>(vertices);

			float c = std::cos(theta);
			float s = std::sin(theta);

			float t = 0.0f;
			float y = 0.0f;
			float x = radius;
			for (float i = 0; i < vertices; i++)
			{
				float v_x = x + position.x;
				float v_y = y + position.y;
				bg::append(convexRing, point(v_x, v_y));

				t = x;
				x = c * x - s * y;
				y = s * t + c * y;
			}

			return convexRing;
		}


		
		
		float gradosAradianes(float grados){
				return (grados*PI/180.0f);
		}

		void doExplosion(b2Vec2 removalPosition, int removalRadius, b2World* mundo){

			polygon* explosion = new polygon();
			float x0 = -500.0f ,y0 = -500.0f;
			float x,y;
			//for(int i = 0; i < 360; i+=10){
			//	x = removalRadius*cos(gradosAradianes(i)) + removalPosition.x;
			//	y = removalRadius*sin(gradosAradianes(i)) + removalPosition.y;
			//		if(x0==-500.0f && y0==-500.0f){
			//				x0 = x;
			//				y0 = y;
			//		}
			//		explosion->outer().push_back(point(x,y));
			//}
			//explosion->outer().push_back(point(x0,y0));
			*explosion = makeConvexRing(removalPosition, removalRadius, 16);
			

		list <polygon*>* resultado = new list<polygon*>();
        for(list<polygon*>::iterator it = this->myPol->begin(); it != this->myPol->end(); it++){
                list <polygon>* output = new list<polygon>();
                boost::geometry::difference(*(*it), *explosion, *output);
                for(list<polygon>::iterator it2 = output->begin(); it2 != output->end(); it2++){
                        resultado->push_back(&(*it2));
                }
                //output.clear();
        }
        this->myPol->clear();
        this->myPol = resultado;

		for(std::vector<b2Body*>::iterator it = myTerrain.begin(); it != myTerrain.end(); it++){
                mundo->DestroyBody(*it);
        }

        myTerrain.clear();

        for(std::list<polygon*>::iterator it = resultado->begin(); it != resultado->end(); it++){
                b2BodyDef* bd = new b2BodyDef();
                b2Vec2* vs = new b2Vec2[(*it)->outer().size()];
                int i = 0;

                for(vector<point>::iterator it2 = (*it)->outer().begin(); it2 != (*it)->outer().end(); it2++){
                        vs[i].Set((*it2).get<0>(),(*it2).get<1>());
                        i++;
                }

                b2ChainShape shape;
                shape.CreateChain(vs, i);
                //shape.CreateLoop(vs,i);
                b2Body* tierra = mundo->CreateBody(bd);
                tierra->CreateFixture(&shape, 1.0f);
                myTerrain.push_back(tierra);
        }




		}

		void MouseDown(const b2Vec2 &p)
		{
			doExplosion(p,5.0,m_world);
		}


        WormsTOrig()
        {
                action = NOTHING;
                //Set contact listener
                m_world->SetContactListener(&myContactListenerInstance);
                m_world->SetGravity(b2Vec2(0,-10));

                b2Body* ground = NULL;
                {
                        b2BodyDef bd;
                        ground = m_world->CreateBody(&bd);

                        b2EdgeShape shape;
                        shape.Set(b2Vec2(-120.0f, 0.0f), b2Vec2(120.0f, 0.0f));

                        b2FixtureDef fd;
                        fd.shape = &shape;

                        auto groundFixture = ground->CreateFixture(&fd);

						b2Filter filter;
						filter.categoryBits = Shape::normal;
						groundFixture->SetFilterData(filter);

                }

                
                {


						myPol = new list<polygon*>();
                        ////Create Bodies (AKA Worms)

						b2BodyDef myBodyDef;
						myBodyDef.type = b2_dynamicBody;

                        b2CircleShape circleShape;
                        circleShape.m_radius = 1;
                        circleShape.m_p.Set(0,0);

                        b2FixtureDef myFixtureDef;
                        myFixtureDef.shape = &circleShape;
						myFixtureDef.density = 1;
                        myFixtureDef.restitution = 0;
                        myFixtureDef.friction = 0.999;
                        myFixtureDef.userData = (void*)3;

						
						

                        myBodyDef.position.Set(26, 60);
                        bodies[0] = m_world->CreateBody(&myBodyDef);
                        auto polygonFixture =  bodies[0]->CreateFixture(&myFixtureDef);
						b2Filter filter;
						filter.categoryBits = Shape::normal;
						polygonFixture->SetFilterData(filter);


                        circleShape.m_p.Set(0,1);
                        
                        auto polygonFixture2 = bodies[0]->CreateFixture(&myFixtureDef);
                        bodies[0]->SetFixedRotation(true);
						polygonFixture2->SetFilterData(filter);




                        //Create terrain
                        char* path="C:\\random-fiuba-game\\randomgame\\randomgame-server\\res\\images\\terrain3.png";
                        float epsilon=5;
                        int scale =15;
                        int waterLevel=50;
                        TerrainProcessor* aTerrainProcessor = new TerrainProcessor();
						
						aTerrainProcessor->process(m_world,path,epsilon, scale,waterLevel,true,&myTerrain,myPol);
                        


						





                }

                // Define platform
                {
                        b2BodyDef bd;
                        bd.type = b2_dynamicBody;
                        bd.position.Set(-4.0f, 5.0f);
                        m_platform = m_world->CreateBody(&bd);
                        m_speed = 3.0f;
                }

				
				//doExplosion(b2Vec2(0,0),15.0,m_world);
        


        }



	//polygon* Funciones::explosion(Posicion* centro, float radio){
	//		polygon* poligono = new polygon();
	//		float x0 = -500.0f ,y0 = -500.0f;
	//		float x,y;
	//		for(int i = 0; i < 360; i+=10){
	//				x = radio*cos(Funciones::gradosAradianes(i)) + centro->getX();
	//				y = radio*sin(Funciones::gradosAradianes(i)) + centro->getY();
	//				if(x0==-500.0f && y0==-500.0f){
	//						x0 = x;
	//						y0 = y;
	//				}
	//				poligono->outer().push_back(point(x,y));
	//		}
	//		poligono->outer().push_back(point(x0,y0));
	//		return poligono;
	//}



        void Keyboard(unsigned char key)
        {
                switch (key)
                {
                case 'w':
                        action = KEY_JUMP;
                        break;

                case 'a':
                        action = KEY_LEFT;
                        break;

                case 'd':
                        action = KEY_RIGHT;
                        break;
                }
        }

        void Step(Settings* settings)
        {
                Test::Step(settings);
                //printf("normals1[0].x: %f, normals1[0].y: %f",normals1[0].x,normals1[0].y);
                if ( action == KEY_JUMP){
                        bodies[0]->ApplyLinearImpulse( b2Vec2(0,FUERZA_SALTO), bodies[0]->GetWorldCenter() );
                }

                if ( action == KEY_LEFT){
                        
                        if ( normals1[0].x > 0.02 && normals1[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals1[0].y,VELOCIDAD*normals1[0].x));
                                action = NOTHING;
                        }

                        if (normals1[0].x < -0.02 && normals1[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals1[0].y,VELOCIDAD*normals1[0].x));
                                action = NOTHING;
                        }
                        if ((normals1[0].x <= 0.02 || normals[0].x >= -0.02) && normals1[0].y > 0.15){
                                //printf("\nen el plano horizontal");
                                //bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV,0), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD,0));
                                action = NOTHING;
                        }
                        

                }

                if ( action == KEY_RIGHT){
                        
                        if ( normals1[0].x > 0.02 && normals1[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals1[0].y,-VELOCIDAD*normals1[0].x));
                                action = NOTHING;
                        }

                        if (normals1[0].x < -0.02 && normals1[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals1[0].y,-VELOCIDAD*normals1[0].x));
                                action = NOTHING;
                        }
                        if ((normals1[0].x <= 0.02 || normals1[0].x >= -0.02) && normals1[0].y > 0.15){
                                //printf("\nen el plano horizontal");
                                //bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV,0), bodies[0]->GetWorldCenter() );
                                
                                bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD,0));
                                action = NOTHING;
                        }       



                }
        }


        static Test* Create()
        {
                return new WormsTOrig;
        }


        b2Body* m_attachment;
        b2Body* m_platform;
        float32 m_speed;
};

#endif