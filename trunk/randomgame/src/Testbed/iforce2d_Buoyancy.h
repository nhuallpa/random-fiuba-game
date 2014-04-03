/*
* Author: Chris Campbell - www.iforce2d.net
*
* Copyright (c) 2006-2011 Erin Catto http://www.box2d.org
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

#ifndef IFORCE2D_BUOYANCY_H
#define IFORCE2D_BUOYANCY_H

#include "iforce2d_Buoyancy_functions.h"

class iforce2d_Buoyancy : public Test
{
public:
    iforce2d_Buoyancy()
    {
        //include dumped world data
        b2Vec2 g(0.000000000000000e+00f, -1.000000000000000e+01f);
m_world->SetGravity(g);
b2Body** bodies = (b2Body**)b2Alloc(18 * sizeof(b2Body*));
b2Joint** joints = (b2Joint**)b2Alloc(0 * sizeof(b2Joint*));
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-1.015610504150391e+01f, 1.752653121948242e+00f);
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
  bodies[0] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(1.000000000000000e+00f, -1.000000000000000e+00f);
    vs[1].Set(1.000000000000000e+00f, 1.000000000000000e+00f);
    vs[2].Set(-1.000000000000000e+00f, 1.000000000000000e+00f);
    vs[3].Set(-1.000000000000000e+00f, -1.000000000000000e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[0]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(0);
  bd.position.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
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
  bodies[1] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.000000000000000e+01f, -5.000000000000000e-01f);
    vs[1].Set(2.000000000000000e+01f, 5.000000000000000e-01f);
    vs[2].Set(-5.485061645507812e+01f, 5.000000000000000e-01f);
    vs[3].Set(-5.485061645507812e+01f, -5.000000000000000e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[1]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-2.811175155639648e+01f, 3.515510559082031e+01f);
  bd.angle = -7.853981852531433e-01f;
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
  bodies[2] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 4.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(9.294319152832031e-02f, -1.000000000000000e+00f);
    vs[1].Set(9.294319152832031e-02f, 1.000000000000000e+00f);
    vs[2].Set(-9.816074371337891e-02f, 1.000000000000000e+00f);
    vs[3].Set(-9.816074371337891e-02f, -1.000000000000000e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[2]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(1.343957805633545e+01f, 1.412565040588379e+01f);
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
  bodies[3] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(1.000000000000000e+00f, 0.000000000000000e+00f);
    vs[1].Set(7.071059942245483e-01f, 7.071075439453125e-01f);
    vs[2].Set(0.000000000000000e+00f, 1.000000000000000e+00f);
    vs[3].Set(-7.071059942245483e-01f, 7.071075439453125e-01f);
    vs[4].Set(-1.000000000000000e+00f, 0.000000000000000e+00f);
    vs[5].Set(-7.071059942245483e-01f, -7.071075439453125e-01f);
    vs[6].Set(0.000000000000000e+00f, -1.000000000000000e+00f);
    vs[7].Set(7.071080207824707e-01f, -7.071075439453125e-01f);
    shape.Set(vs, 8);

    fd.shape = &shape;

    bodies[3]->CreateFixture(&fd);
  }
}
/*{
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
  bodies[4] = m_world->CreateBody(&bd);

  {
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
    vs[0].Set(-5.544052124023438e-01f, -1.515119433403015e+00f);
    vs[1].Set(-5.544052124023438e-01f, 7.516476631164551e+00f);
    vs[2].Set(-4.341683959960938e+01f, 7.516476631164551e+00f);
    vs[3].Set(-4.341683959960938e+01f, -1.515119433403015e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[4]->CreateFixture(&fd);
  }
}*/
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-2.586175537109375e+01f, 3.515510559082031e+01f);
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
  bodies[5] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 4.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(9.294319152832031e-02f, -1.000000000000000e+00f);
    vs[1].Set(9.294319152832031e-02f, 1.000000000000000e+00f);
    vs[2].Set(-9.816074371337891e-02f, 1.000000000000000e+00f);
    vs[3].Set(-9.816074371337891e-02f, -1.000000000000000e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[5]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-2.373113632202148e+01f, 3.515510177612305e+01f);
  bd.angle = 1.570796370506287e+00f;
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
  bodies[6] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 4.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(9.294319152832031e-02f, -1.000000000000000e+00f);
    vs[1].Set(9.294319152832031e-02f, 1.000000000000000e+00f);
    vs[2].Set(-9.816074371337891e-02f, 1.000000000000000e+00f);
    vs[3].Set(-9.816074371337891e-02f, -1.000000000000000e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[6]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(0);
  bd.position.Set(2.000000000000000e+01f, 1.999999809265137e+01f);
  bd.angle = -1.570796370506287e+00f;
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
  bodies[7] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.000000000000000e+01f, -5.000000000000000e-01f);
    vs[1].Set(2.000000000000000e+01f, 5.000000000000000e-01f);
    vs[2].Set(-2.000000000000000e+01f, 5.000000000000000e-01f);
    vs[3].Set(-2.000000000000000e+01f, -5.000000000000000e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[7]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(1.332015132904053e+01f, 2.823232650756836e+00f);
  bd.angle = -3.126464605331421e+00f;
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
  bodies[8] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(5.458000659942627e+00f, 1.932244658470154e+00f);
    vs[1].Set(4.231588363647461e+00f, 1.035382747650146e+00f);
    vs[2].Set(4.136718273162842e+00f, -1.974030256271362e+00f);
    vs[3].Set(5.366768836975098e+00f, -2.028761625289917e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[8]->CreateFixture(&fd);
  }
  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(5.458000659942627e+00f, 1.932244658470154e+00f);
    vs[1].Set(-5.803962707519531e+00f, 2.050609827041626e+00f);
    vs[2].Set(-4.514650821685791e+00f, 1.105765700340271e+00f);
    vs[3].Set(4.231588363647461e+00f, 1.035382747650146e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[8]->CreateFixture(&fd);
  }
  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(-4.514650821685791e+00f, 1.105765700340271e+00f);
    vs[1].Set(-5.803962707519531e+00f, 2.050609827041626e+00f);
    vs[2].Set(-5.854610443115234e+00f, -1.812623858451843e+00f);
    vs[3].Set(-4.601483821868896e+00f, -1.712271928787231e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[8]->CreateFixture(&fd);
  }
  {
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
    vs[0].Set(4.919295787811279e+00f, 1.530433893203735e+00f);
    vs[1].Set(-5.178795337677002e+00f, 1.683210015296936e+00f);
    vs[2].Set(-5.225200653076172e+00f, -1.384050726890564e+00f);
    vs[3].Set(4.872890472412109e+00f, -1.536840081214905e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[8]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-5.409978389739990e+00f, 1.763031005859375e+00f);
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
  bodies[9] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 2.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(1.000000000000000e+00f, -1.000000000000000e+00f);
    vs[1].Set(1.000000000000000e+00f, 1.000000000000000e+00f);
    vs[2].Set(-1.000000000000000e+00f, 1.000000000000000e+00f);
    vs[3].Set(-1.000000000000000e+00f, -1.000000000000000e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[9]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-6.527210474014282e-01f, 2.409656524658203e+00f);
  bd.angle = 3.141592741012573e+00f;
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
  bodies[10] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(9.797759056091309e-01f, -2.595954895019531e+00f);
    vs[1].Set(9.797759056091309e-01f, 1.404045104980469e+00f);
    vs[2].Set(-1.020224094390869e+00f, 1.404045104980469e+00f);
    vs[3].Set(-1.020224094390869e+00f, -5.959548950195312e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[10]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-4.322952270507812e+01f, 1.334864711761475e+01f);
  bd.angle = 3.824857473373413e-01f;
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
  bodies[11] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.595919609069824e+00f, -1.319291234016418e+00f);
    vs[1].Set(-2.777174711227417e+00f, 9.063234329223633e-01f);
    vs[2].Set(-1.861940383911133e+00f, -4.768543243408203e-01f);
    vs[3].Set(-1.460509777069092e+00f, -1.000003814697266e+00f);
    vs[4].Set(-9.373636245727539e-01f, -1.401435852050781e+00f);
    vs[5].Set(-3.281402587890625e-01f, -1.653779983520508e+00f);
    vs[6].Set(3.256297111511230e-01f, -1.739847183227539e+00f);
    vs[7].Set(9.794044494628906e-01f, -1.653779983520508e+00f);
    shape.Set(vs, 8);

    fd.shape = &shape;

    bodies[11]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(1.292107200622559e+01f, 9.424398422241211e+00f);
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
  bodies[12] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(1.000000000000000e+00f, 0.000000000000000e+00f);
    vs[1].Set(7.071059942245483e-01f, 7.071075439453125e-01f);
    vs[2].Set(0.000000000000000e+00f, 1.000000000000000e+00f);
    vs[3].Set(-7.071059942245483e-01f, 7.071075439453125e-01f);
    vs[4].Set(-1.000000000000000e+00f, 0.000000000000000e+00f);
    vs[5].Set(-7.071059942245483e-01f, -7.071075439453125e-01f);
    vs[6].Set(0.000000000000000e+00f, -1.000000000000000e+00f);
    vs[7].Set(7.071080207824707e-01f, -7.071075439453125e-01f);
    shape.Set(vs, 8);

    fd.shape = &shape;

    bodies[12]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(0);
  bd.position.Set(-2.000000000000000e+01f, 2.000000000000000e+01f);
  bd.angle = -1.570796370506287e+00f;
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
  bodies[13] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.000000190734863e+01f, -3.535061645507812e+01f);
    vs[1].Set(2.000000190734863e+01f, -3.435061645507812e+01f);
    vs[2].Set(-1.999999809265137e+01f, -3.435061645507812e+01f);
    vs[3].Set(-1.999999809265137e+01f, -3.535061645507812e+01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[13]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(6.069438457489014e+00f, 3.902924537658691e+00f);
  bd.angle = 1.570796370506287e+00f;
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
  bodies[14] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(3.146587848663330e+00f, 5.416240692138672e-01f);
    vs[1].Set(1.722242832183838e+00f, -4.027786254882812e-01f);
    vs[2].Set(1.737724781036377e+00f, -1.532964706420898e+00f);
    vs[3].Set(3.115623950958252e+00f, -1.532964706420898e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[14]->CreateFixture(&fd);
  }
  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(3.146587848663330e+00f, 5.416240692138672e-01f);
    vs[1].Set(-3.167480945587158e+00f, 5.974674224853516e-01f);
    vs[2].Set(-1.167480945587158e+00f, -4.182605743408203e-01f);
    vs[3].Set(1.722242832183838e+00f, -4.027786254882812e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[14]->CreateFixture(&fd);
  }
  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(-1.167480945587158e+00f, -1.402532577514648e+00f);
    vs[1].Set(-1.167480945587158e+00f, -4.182605743408203e-01f);
    vs[2].Set(-3.167480945587158e+00f, 5.974674224853516e-01f);
    vs[3].Set(-3.167480945587158e+00f, -1.402532577514648e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[14]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(-7.782896041870117e+00f, 1.825901985168457e+00f);
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
  bodies[15] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.500000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(1.000000000000000e+00f, -1.000000000000000e+00f);
    vs[1].Set(1.000000000000000e+00f, 1.000000000000000e+00f);
    vs[2].Set(-1.000000000000000e+00f, 1.000000000000000e+00f);
    vs[3].Set(-1.000000000000000e+00f, -1.000000000000000e+00f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[15]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(0);
  bd.position.Set(0.000000000000000e+00f, 4.000000000000000e+01f);
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
  bodies[16] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.000000000000000e+01f, -5.000000000000000e-01f);
    vs[1].Set(2.000000000000000e+01f, 5.000000000000000e-01f);
    vs[2].Set(-5.485061645507812e+01f, 5.000000000000000e-01f);
    vs[3].Set(-5.485061645507812e+01f, -5.000000000000000e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[16]->CreateFixture(&fd);
  }
}
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(8.500895500183105e-01f, 2.240486145019531e+00f);
  bd.angle = 3.141592741012573e+00f;
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
  bodies[17] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(-5.787930488586426e-01f, 1.404045104980469e+00f);
    vs[1].Set(-1.020224094390869e+00f, 1.404045104980469e+00f);
    vs[2].Set(-1.020224094390869e+00f, -5.959548950195312e-01f);
    vs[3].Set(-5.787935256958008e-01f, -4.697570800781250e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[17]->CreateFixture(&fd);
  }
  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(1.554737567901611e+00f, -3.189464569091797e+00f);
    vs[1].Set(1.554737567901611e+00f, -2.628318786621094e+00f);
    vs[2].Set(-5.787935256958008e-01f, -4.697570800781250e-01f);
    vs[3].Set(-1.020224094390869e+00f, -5.959548950195312e-01f);
    shape.Set(vs, 4);

    fd.shape = &shape;

    bodies[17]->CreateFixture(&fd);
  }
}
b2Free(joints);
b2Free(bodies);
joints = NULL;
bodies = NULL;





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
        Test::Step(settings);

        //go through all buoyancy fixture pairs and apply necessary forces
        std::set<fixturePair>::iterator it = m_fixturePairs.begin();
        std::set<fixturePair>::iterator end = m_fixturePairs.end();
        while (it != end) {

            //fixtureA is the fluid
            b2Fixture* fixtureA = it->first;
            b2Fixture* fixtureB = it->second;

            float density = fixtureA->GetDensity();

            std::vector<b2Vec2> intersectionPoints;
            if ( findIntersectionOfFixtures(fixtureA, fixtureB, intersectionPoints) ) {

                //find centroid
                float area = 0;
                b2Vec2 centroid = ComputeCentroid( intersectionPoints, area);

                //apply buoyancy force
                float displacedMass = fixtureA->GetDensity() * area;
                b2Vec2 gravity( 0, -10 );
                b2Vec2 buoyancyForce = displacedMass * -gravity;
                fixtureB->GetBody()->ApplyForce( buoyancyForce, centroid );

                /*
                //simple drag
                //find relative velocity between object and fluid
                b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( centroid ) -
                        fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( centroid );
                float vel = velDir.Normalize();

                float dragMod = 1;//adjust as desired
                float dragMag = fixtureA->GetDensity() * vel * vel;
                b2Vec2 dragForce = dragMod * dragMag * -velDir;
                fixtureB->GetBody()->ApplyForce( dragForce, centroid );
                float angularDrag = area * -fixtureB->GetBody()->GetAngularVelocity();
                fixtureB->GetBody()->ApplyTorque( angularDrag );
                */

                //apply complex drag
                float dragMod = 0.25f;//adjust as desired
                float liftMod = 0.25f;//adjust as desired
                float maxDrag = 2000;//adjust as desired
                float maxLift = 500;//adjust as desired
                for (int i = 0; i < intersectionPoints.size(); i++) {
                    b2Vec2 v0 = intersectionPoints[i];
                    b2Vec2 v1 = intersectionPoints[(i+1)%intersectionPoints.size()];
                    b2Vec2 midPoint = 0.5f * (v0+v1);

                    //find relative velocity between object and fluid at edge midpoint
                    b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( midPoint ) -
                            fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( midPoint );
                    float vel = velDir.Normalize();

                    b2Vec2 edge = v1 - v0;
                    float edgeLength = edge.Normalize();
                    b2Vec2 normal = b2Cross(-1,edge);
                    float dragDot = b2Dot(normal, velDir);
                    if ( dragDot < 0 )
                        continue;//normal points backwards - this is not a leading edge

                    //apply drag
                    float dragMag = dragDot * dragMod * edgeLength * density * vel * vel;
                    dragMag = b2Min( dragMag, maxDrag );
                    b2Vec2 dragForce = dragMag * -velDir;
                    fixtureB->GetBody()->ApplyForce( dragForce, midPoint );

                    //apply lift
                    float liftDot = b2Dot(edge, velDir);
                    float liftMag =  dragDot * liftDot * liftMod * edgeLength * density * vel * vel;
                    liftMag = b2Min( liftMag, maxLift );
                    b2Vec2 liftDir = b2Cross(1,velDir);
                    b2Vec2 liftForce = liftMag * liftDir;
                    fixtureB->GetBody()->ApplyForce( liftForce, midPoint );
                }

                //draw debug info
                glColor3f(0,1,1);
                glLineWidth(2);
                glBegin(GL_LINE_LOOP);
                for (int i = 0; i < intersectionPoints.size(); i++)
                    glVertex2f( intersectionPoints[i].x, intersectionPoints[i].y );
                glEnd();
                glLineWidth(1);
                /*
                //line showing buoyancy force
                if ( area > 0 ) {
                    glBegin(GL_LINES);
                    glVertex2f( centroid.x, centroid.y );
                    glVertex2f( centroid.x, centroid.y + area );
                    glEnd();
                }*/
            }

            ++it;
        }
    }

    static Test* Create()
    {
        return new iforce2d_Buoyancy;
    }

    std::set<fixturePair> m_fixturePairs;
};

#endif









