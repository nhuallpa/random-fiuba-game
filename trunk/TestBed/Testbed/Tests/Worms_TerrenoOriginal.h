
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

namespace bg = boost::geometry;

BOOST_GEOMETRY_REGISTER_POINT_2D(b2Vec2, float, bg::cs::cartesian, x, y)

typedef boost::geometry::model::ring<b2Vec2, false, true> ring_t;
typedef std::vector<ring_t> ring_collection_t;

typedef std::unordered_set<b2Body*> QueryResult;
typedef std::pair<b2Body*, ring_t> match_t;



using namespace std;



#ifndef WORMSTORIG_H
#define WORMSTORIG_H

#define FUERZA_MOV 150
#define FUERZA_SALTO 85
#define VELOCIDAD 10





		ring_t convertShape(b2Vec2 position, const b2ChainShape* source_shape)
		{
			auto vertices = source_shape->m_vertices;
			auto vertexCount = source_shape->m_count;
			ring_t ring(vertices, vertices + vertexCount);
			std::transform(ring.begin(), ring.end(), ring.begin(), [=](b2Vec2 v){ return v + position; });
			bg::correct(ring);

			return ring;
		}


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

        MyContactListener1 myContactListenerInstance;
        keyAction action;
		bool mouseDown;

		struct WorldQueryCallback : public b2QueryCallback
		{
			WorldQueryCallback(b2Shape::Type filter, Shape::Category categoryFilter_)
			: shapeFilter(filter)
			, categoryFilter(categoryFilter_)
			{ }

			bool ReportFixture(b2Fixture* fixture) override
			{
				auto type = fixture->GetShape()->GetType();
				auto fixtureCategory = fixture->GetFilterData().categoryBits;
				if (type == shapeFilter && (categoryFilter & fixtureCategory))
				{
					foundBodies.insert(fixture->GetBody());
				}
				return true;
			}

			QueryResult foundBodies;
			b2Shape::Type shapeFilter;
			Shape::Category categoryFilter;

		};


ring_collection_t subtract(const ring_t& source, const ring_t& subtrahend)
		{
			ring_collection_t out;
			bg::difference(source, subtrahend, out);
			return out;
		}




		void doExplosion(b2Vec2 removalPosition, int removalRadius, b2World* mundo){


			bool flag=false;
			//auto foundBodies = queryDestructibleBodies(removalPosition, removalRadius, *mundo);
			//auto foundBodies = myTerrain;
			auto batch = matchBodiesToRings(myTerrain.begin(), myTerrain.end());
			

			ring_t diff = makeConvexRing(removalPosition, removalRadius, 16);
			boost::geometry::correct(diff);
			std::vector<b2ChainShape> converted;
			for( std::vector<match_t>::iterator it = batch.begin(); it != batch.end(); ++it){
				auto subtractionResult = subtract(it->second, diff);
				converted = convertGeometry(subtractionResult);

				//Aca en converted tengo el vector de b2Shape

				if (!subtractionResult.empty())
				{
					for ( int i=0; i<myTerrain.size() && !flag; i++)
						mundo->DestroyBody(myTerrain[i]);
						flag = true;
						
				}
			}

			
			if ( flag ){
				myTerrain.clear();
				for ( int i=0; i < converted.size(); i++){
					b2BodyDef bd;
					b2Body* body = mundo->CreateBody(&bd);
					auto fix = body->CreateFixture(&converted[i], 0.0f);
					//converted[i].CreateLoop(result,count);
					b2Filter filter;
					filter.categoryBits = Shape::destructible;
					fix->SetFilterData(filter);
					myTerrain.push_back(body);
				}
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
                        TerrainProcessor* aTerrainProcessor = new TerrainProcessor(m_world,path,epsilon, scale,waterLevel,true,&myTerrain);
                        

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



	template<typename It>
	std::vector<match_t> matchBodiesToRings(It begin, It end)
	{
		std::vector<match_t> batch;

		std::transform(begin, end, std::back_inserter(batch), [](b2Body* body) ->std::pair<b2Body*, ring_t>
		{
			auto f = body->GetFixtureList();
			auto shape = static_cast<b2ChainShape*>(f->GetShape());
			return std::make_pair(body, convertShape(body->GetWorldCenter(), shape));
		});

		return batch;
	}

	std::unordered_set<b2Body*> queryDestructibleBodies(b2Vec2 position, float radius, const b2World& world)
	{
		WorldQueryCallback callback(b2Shape::e_chain, Shape::destructible);
		b2AABB aabb;
		aabb.lowerBound = b2Vec2(position.x - radius, position.y - radius );
		aabb.upperBound = b2Vec2( position.x + radius, position.y + radius );

		world.QueryAABB(&callback, aabb);

		return callback.foundBodies;
	}


	std::vector<b2ChainShape> convertGeometry(ring_collection_t& rings){
		std::vector<b2ChainShape> shapes;
		for ( ring_collection_t::iterator r = rings.begin(); r != rings.end(); ++r ){
			b2ChainShape* shape = new b2ChainShape();
			//shape->CreateChain(r->data(), r->size());
			shape->CreateLoop(r->data(), r->size());
			shapes.push_back(*shape);
		}
		return shapes;
	}



	// Genera un circulo a partir de la posicion de Box2d, radio y la cantidad de vertices de precision
	ring_t makeConvexRing(b2Vec2 position, float radius, int vertices)	{
		ring_t convexRing;
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
			bg::append(convexRing, b2Vec2(v_x, v_y));

			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		}

		return convexRing;
	}



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