
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

using namespace std;



#ifndef WORMSTDES_H
#define WORMSTDES_H

#define FUERZA_MOV 150
#define FUERZA_SALTO 85
#define VELOCIDAD 10

class WormsTDest;

        b2Vec2 normals2[3];

class MyContactListener2 : public b2ContactListener
  {

        

    void BeginContact(b2Contact* contact) {
  
      //check if fixture A is body (2)
      b2WorldManifold worldManifold;

          if ( (int)(contact->GetFixtureA()->GetUserData()) == 3 ){  
                contact->GetWorldManifold(&worldManifold);
                normals2[0].x = worldManifold.normal.x;
                normals2[0].y = worldManifold.normal.y;
                contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0,0));
          }
        
  
      //check if fixture B was the body
      if ( (int)(contact->GetFixtureB()->GetUserData()) == 3 ){
                contact->GetWorldManifold(&worldManifold);
                normals2[0].x = worldManifold.normal.x;
                normals2[0].y = worldManifold.normal.y;
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


class WormsTDest : public Test
{
public:

        b2Body* bodies[3];

        MyContactListener2 myContactListenerInstance;
        keyAction action;

        WormsTDest()
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




                        //Create terrain
                        char* path="C:\\random-fiuba-game\\randomgame\\randomgame-server\\res\\images\\terrain3.png";
                        float epsilon=5;
                        int scale =15;
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
                //printf("normals2[0].x: %f, normals2[0].y: %f",normals2[0].x,normals2[0].y);
                if ( action == KEY_JUMP){
                        bodies[0]->ApplyLinearImpulse( b2Vec2(0,FUERZA_SALTO), bodies[0]->GetWorldCenter() );
                }

                if ( action == KEY_LEFT){
                        
                        if ( normals2[0].x > 0.02 && normals2[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals2[0].y,VELOCIDAD*normals2[0].x));
                                action = NOTHING;
                        }

                        if (normals2[0].x < -0.02 && normals2[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV*normals[0].y,FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD*normals2[0].y,VELOCIDAD*normals2[0].x));
                                action = NOTHING;
                        }
                        if ((normals2[0].x <= 0.02 || normals[0].x >= -0.02) && normals2[0].y > 0.15){
                                //printf("\nen el plano horizontal");
                                //bodies[0]->ApplyForce( b2Vec2(-FUERZA_MOV,0), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(-VELOCIDAD,0));
                                action = NOTHING;
                        }
                        

                }

                if ( action == KEY_RIGHT){
                        
                        if ( normals2[0].x > 0.02 && normals2[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals2[0].y,-VELOCIDAD*normals2[0].x));
                                action = NOTHING;
                        }

                        if (normals2[0].x < -0.02 && normals2[0].y > 0.15){
                                //bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV*normals[0].y,-FUERZA_MOV*normals[0].x), bodies[0]->GetWorldCenter() );
                                bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD*normals2[0].y,-VELOCIDAD*normals2[0].x));
                                action = NOTHING;
                        }
                        if ((normals2[0].x <= 0.02 || normals2[0].x >= -0.02) && normals2[0].y > 0.15){
                                //printf("\nen el plano horizontal");
                                //bodies[0]->ApplyForce( b2Vec2(FUERZA_MOV,0), bodies[0]->GetWorldCenter() );
                                
                                bodies[0]->SetLinearVelocity( b2Vec2(VELOCIDAD,0));
                                action = NOTHING;
                        }       



                }
        }


        static Test* Create()
        {
                return new WormsTDest;
        }


        b2Body* m_attachment;
        b2Body* m_platform;
        float32 m_speed;
};

#endif