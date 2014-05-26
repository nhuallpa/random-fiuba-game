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
#include <list>
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\TerrainProcessor.h"
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\Physics\Bodies\Worm\Worm2d.h"
#include "C:\random-fiuba-game\TestBed\src\utils\Clipper\clipper.hpp"

using namespace std;
using namespace ClipperLib;


#ifndef BODY_TYPES_H
#define BODY_TYPES_H

#define FUERZA_MOV 150
#define FUERZA_SALTO 85
#define VELOCIDAD 10

class BodyTypes;

b2Vec2 normals[3];

class MyContactListener : public b2ContactListener
{



	void BeginContact(b2Contact* contact) {

		//check if fixture A is body (2)
		b2WorldManifold worldManifold;

		if ( (int)(contact->GetFixtureA()->GetUserData()) == 3 ){  
			contact->GetWorldManifold(&worldManifold);
			normals[0].x = worldManifold.normal.x;
			normals[0].y = worldManifold.normal.y;
			contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
		}


		//check if fixture B was the body
		if ( (int)(contact->GetFixtureB()->GetUserData()) == 3 ){
			contact->GetWorldManifold(&worldManifold);
			normals[0].x = worldManifold.normal.x;
			normals[0].y = worldManifold.normal.y;
			contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
		}

	} //Begin Contact - END


	void EndContact(b2Contact* contact) {
		if ( (int)(contact->GetFixtureB()->GetUserData()) == 3 ){

			contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0,-10));
		}

		if ( (int)(contact->GetFixtureA()->GetUserData()) == 3 ){
			contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0,-10));

		}

	}
};

typedef enum{
	KEY_RIGHT,
	KEY_LEFT,
	KEY_JUMP,
	NOTHING
} keyAction;

class BodyTypes : public Test
{
public:

	b2Body* bodies[3];

	MyContactListener myContactListenerInstance;
	keyAction action;

	BodyTypes()
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

			ground->CreateFixture(&fd);
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
			bodies[0]->CreateFixture(&myFixtureDef);

			circleShape.m_p.Set(0,1);

			bodies[0]->CreateFixture(&myFixtureDef);
			bodies[0]->SetFixedRotation(true);


			
			Paths subj(1), clip(1), solution;

			//un cuadrado
			b2BodyDef bd;
						b2FixtureDef myFixtureDef2;
						myFixtureDef2.friction=0.999;
			myFixtureDef2.userData = ( (void*)2 );
			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f, 8.0f);
			bd.allowSleep = false;
			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape shape;
			shape.SetAsBox(5.0f, 8.0f);
			myFixtureDef2.shape = &shape; //change the shape of the fixture
			body->CreateFixture(&myFixtureDef2);
			
			b2PolygonShape* poly = (b2PolygonShape*)body->GetFixtureList()->GetShape();
			std::list<std::pair<float,float>> vertexList;
			int count = poly->GetVertexCount();

			for( int i = 0; i < count; i++ ){
				b2Vec2 verts = poly->GetVertex(i);
				b2Vec2 f = body->GetWorldPoint(verts);
				subj[0].push_back(IntPoint(f.x,f.y));
			}

			//otro cuadrado

			//b2BodyDef bd2;
			//bd2.type = b2_dynamicBody;
			//bd2.position.Set(1.0f, 1.0f);
			//bd2.allowSleep = false;
			//b2Body* body2 = m_world->CreateBody(&bd2);

			//b2PolygonShape shape2;
			//shape2.SetAsBox(5.0f, 6.0f);

			//body2->CreateFixture(&shape2, 1.0f);

	
	////define outer blue 'subject' polygon
	//subj[0] << 
	//  IntPoint(180,200) << IntPoint(260,200) <<
	//  IntPoint(260,150) << IntPoint(180,150);
	//
	////define subject's inner triangular 'hole' (with reverse orientation)
	//subj[1] << 
	//  IntPoint(215,160) << IntPoint(230,190) << IntPoint(200,190);
	//
	//define orange 'clipping' polygon
	clip[0] << 
	  IntPoint(0,2) << IntPoint(5,2) << 
	  IntPoint(5,6) << IntPoint(0,6);
	
	//perform intersection ...
	Clipper c;
	c.AddPaths(subj, ptSubject, true);
	c.AddPaths(clip, ptClip, true);
	c.Execute(ctIntersection, solution, pftNonZero, pftNonZero);
	




			////Create terrain
			//char* path="C:\\random-fiuba-game\\randomgame\\randomgame-server\\res\\images\\terrain3.png";
			//float epsilon=5;
			//int scale =15;
			//int waterLevel=50;
			//TerrainProcessor* aTerrainProcessor = new TerrainProcessor(m_world,path,epsilon, scale,waterLevel);
			//auto terrainPolygons = aTerrainProcessor->getListOfPolygons();

			auto bodyCount1 = m_world->GetBodyCount();
			for(int i=0; i < bodyCount1 ; i++)
			{
				auto bodycount2 = m_world->GetBodyCount();
				auto bodies = m_world->GetBodyList();
				void* userData=(bodies->GetFixtureList()->GetUserData());
				if(	(int)userData == 2)
				{
					m_world->DestroyBody(bodies);
					addToWorld(m_world, solution);
				}
			}
		}

		// Define platform
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-4.0f, 5.0f);
			m_platform = m_world->CreateBody(&bd);
			m_speed = 3.0f;
		}


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
		printf("normals[0].x: %f, normals[0].y: %f",normals[0].x,normals[0].y);
		if ( action == KEY_JUMP){
			bodies[0]->ApplyLinearImpulse( b2Vec2(0,FUERZA_SALTO), bodies[0]->GetWorldCenter() );
		}

		if ( action == KEY_LEFT){

			if ( normals[0].x > 0.02 && normals[0].y > 0.15){
				//bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
				bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals[0].y,VELOCIDAD*normals[0].x));
				action = NOTHING;
			}

			if (normals[0].x < -0.02 && normals[0].y > 0.15){
				//bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
				bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals[0].y,VELOCIDAD*normals[0].x));
				action = NOTHING;
			}
			if ((normals[0].x <= 0.02 || normals[0].x >= -0.02) && normals[0].y > 0.15){
				//printf("\nen el plano horizontal");
				//bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV,0), bodies[0]->GetWorldCenter() );
				bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD,0));
				action = NOTHING;
			}


		}

		if ( action == KEY_RIGHT){

			if ( normals[0].x > 0.02 && normals[0].y > 0.15){
				//bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
				bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals[0].y,-VELOCIDAD*normals[0].x));
				action = NOTHING;
			}

			if (normals[0].x < -0.02 && normals[0].y > 0.15){
				//bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
				bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals[0].y,-VELOCIDAD*normals[0].x));
				action = NOTHING;
			}
			if ((normals[0].x <= 0.02 || normals[0].x >= -0.02) && normals[0].y > 0.15){
				//printf("\nen el plano horizontal");
				//bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV,0), bodies[0]->GetWorldCenter() );

				bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD,0));
				action = NOTHING;
			}	



		}
	}

	void addToWorld(b2World* m_world, Paths solution)
	{
		// AGREGAR POLIGONO SOLUTION A BOX2D 

			//Creo el poligono en Box2D
			b2FixtureDef myFixtureDef;
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_staticBody; //this will be a static body
			myBodyDef.position.Set(0, 0); //in the middle
			myFixtureDef.friction=0.999;
			
			myFixtureDef.userData = ( (void*)2 );
			m_attachment = m_world->CreateBody(&myBodyDef);

			b2PolygonShape polygonShape;
			b2Vec2 vertices[8];
			pathsToVec2d(vertices,solution[0]);
			polygonShape.Set(vertices, solution[0].size()); //pass array to the shape

			myFixtureDef.shape = &polygonShape; //change the shape of the fixture
			m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body
			int* st= 0;
			m_attachment->SetUserData(st);
	}

	void pathsToVec2d(b2Vec2* vertices, Path solution)
	{
		for(int i =0; i< solution.size();i++)
		{
			vertices[i] = b2Vec2(solution.at(i).X,solution.at(i).Y);
		}
	}




	static Test* Create()
	{
		return new BodyTypes;
	}


	b2Body* m_attachment;
	b2Body* m_platform;
	float32 m_speed;
};

#endif