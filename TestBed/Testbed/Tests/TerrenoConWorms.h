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

//agregado por Bauti
#include <cstdio>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\TerrainProcessor.h"
#include "C:\random-fiuba-game\TestBed\src\Servidor\modelo\Physics\Bodies\Worm\Worm2d.h"

//using namespace server_model_handle;
using namespace std;


//fin agregado por bauti

#ifndef BODY_TYPES_H
#define BODY_TYPES_H
class BodyTypes;

	b2Vec2 normals[3];

class MyContactListener : public b2ContactListener
  {

	

    void BeginContact(b2Contact* contact) {
  
      //check if fixture A is body (2)
      b2WorldManifold worldManifold;

	  if ( (int)(contact->GetFixtureA()->GetUserData()) == 2 ){  
		contact->GetWorldManifold(&worldManifold);
		normals[0].x = worldManifold.normal.x;
		normals[0].y = worldManifold.normal.y;
	  }
        
  
      //check if fixture B was the body
      if ( (int)(contact->GetFixtureB()->GetUserData()) == 2 ){
		contact->GetWorldManifold(&worldManifold);
		normals[0].x = worldManifold.normal.x;
		normals[0].y = worldManifold.normal.y;
	  }
        
    } //Begin Contact - END
  

    void EndContact(b2Contact* contact) {
  
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

			//Create Bodies
            b2BodyDef myBodyDef;
            myBodyDef.type = b2_dynamicBody;
         
            b2PolygonShape polygonShape;
            b2Vec2 vertices[6];
            for (int i = 0; i < 6; i++) {
                float angle = -i/6.0 * 360 * DEGTORAD;
                vertices[i].Set(sinf(angle)+40, cosf(angle)+60);
            }
            polygonShape.Set(vertices, 6);
            b2FixtureDef myFixtureDef;
            myFixtureDef.shape = &polygonShape;
            myFixtureDef.density = 1;
			myFixtureDef.restitution = 0;
			myFixtureDef.friction = 0.999;
			myFixtureDef.userData = (void*)2;

			//for (int i = 0; i < 3; i++) {
			//	myBodyDef.position.Set(i*10, 60);
			//	bodies[i] = m_world->CreateBody(&myBodyDef);
			//	bodies[i]->CreateFixture(&myFixtureDef);
			//	bodies[i]->SetFixedRotation(true);
			//}

			myBodyDef.position.Set(10, 60);
			bodies[0] = m_world->CreateBody(&myBodyDef);
			bodies[0]->CreateFixture(&myFixtureDef);
			bodies[0]->SetFixedRotation(true);


			Worm2d* gus = new Worm2d(WORM,
					25,
					100,
					MODEL_WORM_HEIGHT,
					MODEL_WORM_WIDTH,
					30,
					0,
					m_world,
					NULL,
					false
					);



			//Create terrain
			char* path="C:\\random-fiuba-game\\randomgame\\randomgame-server\\res\\images\\terrain5.png";
			float epsilon=2.5;
			int scale =100;
			int waterLevel=50;
			TerrainProcessor* aTerrainProcessor = new TerrainProcessor(m_world,path,epsilon, scale,waterLevel);
			

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
