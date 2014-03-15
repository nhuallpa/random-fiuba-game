#ifndef CINTA_H_
#define CINTA_H_


class Cinta: public Test {
public:
	Cinta()
	{		
	
	        b2Body* ground = NULL;
		{
			b2BodyDef bd;
			//ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			//ground->CreateFixture(&shape, 0.0f);
		}	
 

    b2Body* body = crearCuerpo(-3,10,2);
    b2Body* body2 = crearSoporte(-3,10,0);
    b2Body* body3 = crearCuerpo(2,10,2);
    b2Body* body4 = crearSoporte(2,10,0);
    b2Body* body5 = crearCuerpo(7,10,2);
    b2Body* body6 = crearSoporte(7,10,0);
   
    //los q tiene enable motor igual a false
    b2Body* body7 = crearCuerpo(-3,20,2);
    b2Body* body8 = crearSoporte(-3,20,0);
    b2Body* body9 = crearCuerpo(2,20,2);
    b2Body* body10 = crearSoporte(2,20,0);
    b2Body* body11 = crearCuerpo(7,20,2);
    b2Body* body12 = crearSoporte(7,20,0);
    
    b2RevoluteJoint* joint1 = crearJuntura(body,body2);
    b2RevoluteJoint* joint2 = crearJuntura(body3,body4);
    b2RevoluteJoint* joint3 = crearJuntura(body5,body6);
    
    b2RevoluteJoint* joint4 = crearJuntura(body7,body8);
    b2RevoluteJoint* joint5 = crearJuntura(body9,body10);
    b2RevoluteJoint* joint6 = crearJuntura(body11,body12);
    
    b2GearJointDef gear;
    gear.bodyA = body;
    gear.bodyB = body3;
    gear.joint1 = joint1;
    gear.joint2 = joint2;
    joint1->EnableMotor(true);
    joint2->EnableMotor(true);
    b2GearJoint* gearJoint;
    gearJoint = (b2GearJoint*) m_world->CreateJoint(&gear);
    
    //uno el otro engranaje
    gear.bodyA = body3;
    gear.bodyB = body5;
    gear.joint1 = joint2;
    gear.joint2 = joint3;
    joint2->EnableMotor(true);
    joint3->EnableMotor(true);
    gearJoint = (b2GearJoint*) m_world->CreateJoint(&gear);
	}
	
	b2Body* crearCuerpo(float x, float y, float radio){
	  b2Body* body;
	  b2BodyDef bodyDef;
	  bodyDef.type = b2_dynamicBody;
	  bodyDef.position.Set(x,y);
	  b2FixtureDef fixtureDef;
	  fixtureDef.density = 1;
	  b2CircleShape circleShape;
	  circleShape.m_radius = radio;
	  fixtureDef.shape = &circleShape;
	  body = m_world->CreateBody( &bodyDef );
	  body->CreateFixture( &fixtureDef );
	  return body;
        }
        
        b2Body* crearSoporte(float x, float y, float radio){
	  b2Body* body;
	  b2BodyDef bodyDef;
	  bodyDef.type = b2_staticBody;
	  bodyDef.position.Set(x,y);
	  b2FixtureDef fixtureDef;
	  b2CircleShape circleShape;
	  circleShape.m_radius = radio;
	  fixtureDef.shape = &circleShape;
	  body = m_world->CreateBody( &bodyDef );
	  body->CreateFixture( &fixtureDef );
	  return body;
        }
        
        b2Body* crearPlataforma() {
		b2FixtureDef plataforma;
		plataforma.density=1;
		plataforma.restitution=0.9;
		b2PolygonShape boxShape;
		boxShape.SetAsBox(10, 2.5);
		plataforma.shape = &boxShape;
		//Creo el cuerpo
		b2BodyDef def;
		def.type = b2_staticBody;
		def.position.Set(10, 10);
		b2Body* body = m_world->CreateBody(&def);
		body->CreateFixture(&plataforma);
		return body;
	}
	
	b2RevoluteJoint* crearJuntura(b2Body* plataforma, b2Body* soporte) {
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = plataforma;
		revoluteJointDef.bodyB = soporte;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorB.Set(0,0);
		revoluteJointDef.enableMotor = false;
                revoluteJointDef.motorSpeed = 5;
                revoluteJointDef.maxMotorTorque = 5000;
		return (b2RevoluteJoint*) m_world->CreateJoint( &revoluteJointDef );
	}	

	void Step(Settings* settings)
	{
		m_debugDraw.DrawString(5, m_textLine, "Prueba cinta");

		Test::Step(settings);
	}

	static Test* Create()
	{
		return new Cinta();
	}

        
        
	
};

#endif /* CINTA_H_ */
