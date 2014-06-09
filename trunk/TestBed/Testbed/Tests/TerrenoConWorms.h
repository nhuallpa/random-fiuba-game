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
#include <math.h>
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\TerrainProcessor.h"
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\Physics\Bodies\Worm\Worm2d.h"


using namespace std;



#ifndef BODY_TYPES_H
#define BODY_TYPES_H

#define FUERZA_MOV 150
#define FUERZA_SALTO 85
#define VELOCIDAD 10

class BodyTypes;

b2Vec2 normals[3];

BodyTypes *aBodyTypes;



typedef enum{
	KEY_RIGHT,
	KEY_LEFT,
	KEY_JUMP,
	NOTHING,
	GRENADE,
	BAZOOKA,
	HOMING,
	DOVE,
	AIRSTRIKE,
	SHEEP
} keyAction;

class BodyTypes : public Test
{
public:

	class MyContactListener : public b2ContactListener
{
	
	void BeginContact(b2Contact* contact) {

		//check if fixture A is body (2)
		b2WorldManifold worldManifold;

		//if ( (int)(contact->GetFixtureA()->GetUserData()) == 2 ){  
		//	contact->GetWorldManifold(&worldManifold);
		//	normals[0].x = worldManifold.normal.x;
		//	normals[0].y = worldManifold.normal.y;
		//	contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
		//}


		////check if fixture B was the body
		//if ( (int)(contact->GetFixtureB()->GetUserData()) == 2 ){
		//	contact->GetWorldManifold(&worldManifold);
		//	normals[0].x = worldManifold.normal.x;
		//	normals[0].y = worldManifold.normal.y;
		//	contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
		//}


		if ( (int)(contact->GetFixtureA()->GetUserData()) == 7 ){  
			Paths solutions=aBodyTypes->destroyTerrain(contact->GetFixtureB()->GetBody(), contact->GetFixtureA()->GetBody());
					addSolutionsToWorld(contact->GetFixtureA()->GetBody()->GetWorld(), solutions);
			contact->GetFixtureA()->GetBody()->GetWorld()->DestroyBody(contact->GetFixtureA()->GetBody());
		}


		//check if fixture B was the body
		if ( (int)(contact->GetFixtureB()->GetUserData()) == 7 ){
			Paths solutions=aBodyTypes->destroyTerrain(contact->GetFixtureA()->GetBody(), contact->GetFixtureB()->GetBody());
			addSolutionsToWorld(contact->GetFixtureA()->GetBody()->GetWorld(), solutions);
						contact->GetFixtureB()->GetBody()->GetWorld()->DestroyBody(contact->GetFixtureB()->GetBody());
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





	//b2Body* bodies[3];

	MyContactListener myContactListenerInstance;
	keyAction action;
	bool mouseDown;
	b2Vec2 puntoMouse;

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
			ground->SetUserData((void*)1);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-120.0f, 0.0f), b2Vec2(120.0f, 0.0f));

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.userData = ( (void*)1 );
			ground->CreateFixture(&fd);
		}


		{

			////Create Bodies (AKA Worms)

			//b2BodyDef myBodyDef;
			//myBodyDef.type = b2_dynamicBody;

			//b2CircleShape circleShape;
			//circleShape.m_radius = 1;
			//circleShape.m_p.Set(0,0);

			//b2FixtureDef myFixtureDef;
			//myFixtureDef.shape = &circleShape;
			//myFixtureDef.density = 1;
			//myFixtureDef.restitution = 0;
			//myFixtureDef.friction = 0.999;
			//myFixtureDef.userData = (void*)3;

			//myBodyDef.position.Set(26, 60);
			//bodies[0] = m_world->CreateBody(&myBodyDef);
			//bodies[0]->CreateFixture(&myFixtureDef);

			//circleShape.m_p.Set(0,1);

			//bodies[0]->CreateFixture(&myFixtureDef);
			//bodies[0]->SetFixedRotation(true);



			Paths subj(1), clip(1), solution;

			//un cuadrado
			b2BodyDef bd;
			b2FixtureDef myFixtureDef2;
			myFixtureDef2.friction=0.999;
			myFixtureDef2.userData = ( (void*)2 );
			bd.type = b2_staticBody;
			bd.position.Set(5.0f, 10.0f);
			bd.allowSleep = false;
			b2Body* body = m_world->CreateBody(&bd);
			body->SetUserData((void*)2);

			b2PolygonShape shape;
			shape.SetAsBox(5.0f, 10.0f);
			myFixtureDef2.shape = &shape; //change the shape of the fixture
			body->CreateFixture(&myFixtureDef2);




			//explosion


			//Create terrain
			/*char* path="C:\\random-fiuba-game\\randomgame\\randomgame-server\\res\\images\\terrain3.png";
			float epsilon=0.5;
			int scale =15;
			int waterLevel=50;
			TerrainProcessor* aTerrainProcessor = new TerrainProcessor(m_world,path,epsilon, scale,waterLevel);*/
			//auto terrainPolygons = aTerrainProcessor->getListOfPolygons();

			//auto bodies = m_world->GetBodyList();
			//Paths solutions;
			//int bodiesRecorridos=0;
			//while(bodiesRecorridos < m_world->GetBodyCount())
			//{
			//	void* userData=(bodies->GetFixtureList()->GetUserData());
			//	auto nextBody=bodies->GetNext();
			//	if(	(int)userData == 2)
			//	{
			//		auto bodyCount2 = m_world->GetBodyCount();
			//		subj[0] = fromPolygonToPath(bodies);
			//		clip[0] = createCircle(20,10,40,10);
			//		Paths solution = makeClip(clip,subj);
			//		solutions.push_back(solution[0]);
			//		m_world->DestroyBody(bodies);
			//	}
			//	bodies=nextBody;
			//	bodiesRecorridos++;
			//}
			//addSolutionsToWorld(m_world, solutions);
		}

		// Define platform
		//{
		//	b2BodyDef bd;
		//	bd.type = b2_dynamicBody;
		//	bd.position.Set(-4.0f, 5.0f);
		//	m_platform = m_world->CreateBody(&bd);
		//	m_speed = 3.0f;
		//}


	}


	void MouseDown(const b2Vec2 &p)
	{
		/*destroyTerrain(p);*/

			b2BodyDef myBodyDef;
			myBodyDef.type = b2_dynamicBody;

			b2CircleShape circleShape;
			circleShape.m_radius = 5;
			circleShape.m_p.Set(0,0);

			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &circleShape;
			myFixtureDef.density = 1;
			myFixtureDef.restitution = 0;
			myFixtureDef.friction = 0.999;
			myFixtureDef.userData = (void*)7;

			myBodyDef.position.Set(p.x, p.y);

			b2Body* body = m_world->CreateBody(&myBodyDef);
			body->SetUserData((void*)7); //explosion
			body->CreateFixture(&myFixtureDef);

	}

static Paths destroyTerrain(b2Body* terreno, b2Body* explosion)
	{
		auto aWorld= terreno->GetWorld();
		Paths subj(1), clip(1);
		Paths solutions;

		bool bug1=false;//el clip va a devolver uno o mas poligonos
		bool bug2=true;//el clip es mas grande que el poligono
		bool bug3=true;//el clip es completamente mas chico que el poligono

		subj[0] = fromPolygonToPath(terreno);
		clip[0] = createCircle(20,explosion->GetPosition().x ,explosion->GetPosition().y,5);
		isBugged(terreno,clip[0],bug1,bug2,bug3);
		Paths solution = makeClip(clip,subj);
		auto intersec = makeClipIntersec(clip,subj);

		if(bug2 && intersec.size() > 0 )
		{
			aWorld->DestroyBody(terreno);
		}
		else if(bug3)
		{
			//solutions.push_back(solution[0]);
			//aWorld->DestroyBody(bodies);
		}
		if ( bug2==false && bug3==false)
		{
			for(int j=0; j<solution.size();j++)
			{
				solutions.push_back(solution[j]);
			}
		}
	return solutions;
	}


	//void destroyTerrain(const b2Vec2 &p)
	//{


	//	Paths subj(1), clip(1);
	//	auto bodies = m_world->GetBodyList();
	//	Paths solutions;

	//	auto count = m_world->GetBodyCount();
	//	for(int bodiesRecorridos=0; bodiesRecorridos < count; bodiesRecorridos++)
	//	{
	//		auto nextBody=bodies->GetNext();
	//		void* userData=bodies->GetUserData();;
	//		bool bug1=false;//el clip va a devolver uno o mas poligonos
	//		bool bug2=true;//el clip es mas grande que el poligono
	//		bool bug3=true;//el clip es completamente mas chico que el poligono


	//		if(	(int)userData == 2)
	//		{
	//			auto bodyCount1 = m_world->GetBodyCount();
	//			subj[0] = fromPolygonToPath(bodies);
	//			clip[0] = createCircle(20,p.x,p.y,5);
	//			isBugged(bodies,clip[0],bug1,bug2,bug3);
	//			Paths solution = makeClip(clip,subj);
	//			auto intersec = makeClipIntersec(clip,subj);
	//			
	//			if(bug2 && intersec.size() > 0 )
	//			{
	//				m_world->DestroyBody(bodies);
	//			}
	//			else if(bug3)
	//			{
	//				//solutions.push_back(solution[0]);
	//				//m_world->DestroyBody(bodies);
	//			}
	//			if ( bug2==false && bug3==false)
	//			{
	//				for(int j=0; j<solution.size();j++)
	//				{
	//					solutions.push_back(solution[j]);
	//				}
	//				m_world->DestroyBody(bodies);
	//			}
	//		}
	//		bodies=nextBody;
	//	}
	//	auto bodyCount2 = m_world->GetBodyCount();
	//	addSolutionsToWorld(m_world, solutions);
	//	auto bodyCount3 = m_world->GetBodyCount();
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
		//printf("normals[0].x: %f, normals[0].y: %f",normals[0].x,normals[0].y);
		//if ( action == KEY_JUMP){
		//	bodies[0]->ApplyLinearImpulse( b2Vec2(0,FUERZA_SALTO), bodies[0]->GetWorldCenter() );
		//}

		//if ( action == KEY_LEFT){

		//	if ( normals[0].x > 0.02 && normals[0].y > 0.15){
		//		//bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
		//		bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals[0].y,VELOCIDAD*normals[0].x));
		//		action = NOTHING;
		//	}

		//	if (normals[0].x < -0.02 && normals[0].y > 0.15){
		//		//bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
		//		bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals[0].y,VELOCIDAD*normals[0].x));
		//		action = NOTHING;
		//	}
		//	if ((normals[0].x <= 0.02 || normals[0].x >= -0.02) && normals[0].y > 0.15){
		//		//printf("\nen el plano horizontal");
		//		//bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV,0), bodies[0]->GetWorldCenter() );
		//		bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD,0));
		//		action = NOTHING;
		//	}


		//}

		//if ( action == KEY_RIGHT){

		//	if ( normals[0].x > 0.02 && normals[0].y > 0.15){
		//		//bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
		//		bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals[0].y,-VELOCIDAD*normals[0].x));
		//		action = NOTHING;
		//	}

		//	if (normals[0].x < -0.02 && normals[0].y > 0.15){
		//		//bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
		//		bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals[0].y,-VELOCIDAD*normals[0].x));
		//		action = NOTHING;
		//	}
		//	if ((normals[0].x <= 0.02 || normals[0].x >= -0.02) && normals[0].y > 0.15){
		//		//printf("\nen el plano horizontal");
		//		//bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV,0), bodies[0]->GetWorldCenter() );

		//		bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD,0));
		//		action = NOTHING;
		//	}	



		//}
	}
	static void addSolutionsToWorld(b2World* m_world, Paths solutions)
	{
		for(int i=0; i< solutions.size(); i++)
		{
			float epsilon=0.1;
			int scale =15;
			int waterLevel=50;
			HandleContour hc;
			vector<b2Vec2> lista;
			pathsToVec2d(lista,solutions.at(i));
			auto result = hc.getPolygonConvex(lista, epsilon, scale);

			for(int nroDePoligono=0; nroDePoligono< result.size(); nroDePoligono++)
			{
				// AGREGAR POLIGONO A BOX2D 
				addToWorld(m_world,result[nroDePoligono]);

			}
		}

	}
static	void addToWorld(b2World* m_world, vector<b2Vec2> aPolygon)
	{
		// AGREGAR POLIGONO SOLUTION A BOX2D 
		b2Body* m_attachment;
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
		polygonShape.Set(&aPolygon[0], aPolygon.size()); //pass array to the shape

		myFixtureDef.shape = &polygonShape; //change the shape of the fixture
		m_attachment->CreateFixture(&myFixtureDef); //add a fixture to the body

		m_attachment->SetUserData((void*)2);
	}

static	void pathsToVec2d(vector<b2Vec2>& vertices, Path solution)
	{
		for(int i =0; i< solution.size();i++)
		{
			vertices.push_back(b2Vec2(solution.at(i).X,solution.at(i).Y));
		}
	}


static	Path fromPolygonToPath(b2Body* body)
	{
		b2PolygonShape* poly = (b2PolygonShape*)body->GetFixtureList()->GetShape();
		Path aPath;
		int count = poly->GetVertexCount();

		for( int i = 0; i < count; i++ ){
			b2Vec2 verts = poly->GetVertex(i);
			b2Vec2 f = body->GetWorldPoint(verts);
			aPath.push_back(IntPoint(f.x,f.y));
		}
		return aPath;
	}

static	Path createCircle(float precision,float posXCentral, float posYCentral, float radio){
		float  PI=3.14159265358979f;
		float angle=2*PI/precision;
		Path aCirclePerimeter;
		for (int i=0; i<precision; i++) {
			float posX=posXCentral+radio*cos(angle*i);
			float posY=posYCentral+radio*sin(angle*i);
			aCirclePerimeter.push_back(IntPoint(posX,posY) );
		}
		return aCirclePerimeter;
	}

static	Paths makeClip(Paths clip, Paths subj)
	{
		Paths aSolution;
		//perform difference ...
		Clipper c;
		c.AddPaths(subj, ptSubject, true);
		c.AddPaths(clip, ptClip, true);
		c.Execute(ctDifference, aSolution,pftNonZero, pftPositive  );
		return aSolution;
	}

	static Paths makeClipIntersec(Paths clip, Paths subj)
	{
		Paths aSolution;
		//perform difference ...
		Clipper c;
		c.AddPaths(subj, ptSubject, true);
		c.AddPaths(clip, ptClip, true);
		c.Execute(ctIntersection , aSolution,pftNonZero, pftNonZero  );
		return aSolution;
	}


	static bool isBugged(b2Body* body, Path aClip,bool & bug1, bool& bug2, bool & bug3)
	{
		bug1=false;//el clip va a devolver uno o mas poligonos
		bug2=true;//el clip es mas grande que el poligono
		bug3=true;//el clip es completamente mas chico que el poligono
		for(int i =0; i < aClip.size(); i++)
		{
			b2Vec2 unPunto(aClip.at(i).X,aClip.at(i).Y);
			bug3 = bug3 && body->GetFixtureList()->TestPoint(unPunto); //todos los puntos del clip estan dentro del poligono
			bug2 = bug2 && (body->GetFixtureList()->TestPoint(unPunto)==false ); //ningun punto del perimetro del clip esta dentro del poligono
		}
		bug1= !bug2 && !bug3;
		return bug1 || bug2 || bug3;
	}

	static Test* Create()
	{
		aBodyTypes= new BodyTypes;
		return aBodyTypes;
	}

	b2Body* m_platform;
	float32 m_speed;
};

#endif
