#ifndef MOTOR_H_
#define MOTOR_H_


class Motor: public Test {
public:
	Motor()
	{
	    b2Body* body = crearCuerpo(-3,10,2);
            b2Body* body2 = crearSoporte(-3,10,0);
 
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.bodyA = body;
            revoluteJointDef.bodyB = body2;
            revoluteJointDef.collideConnected = false;
            revoluteJointDef.localAnchorA.Set(0,0);//the top right corner of the box
            revoluteJointDef.localAnchorB.Set(0,0);//center of the circle
            revoluteJointDef.enableMotor = true;
            revoluteJointDef.motorSpeed = 5;
            revoluteJointDef.maxMotorTorque = 5000;

            joint = (b2RevoluteJoint*) m_world->CreateJoint( &revoluteJointDef );
            body->ResetMassData();
  
            //creo un cuadrado
            b2Body* body3 = crearCuadrado(-3,20);
            //le cambio la velocidad
            setVelocidad(10);
            //cambio radio
            //setRadio(10,body,body2);
            
            
            //hago lo mismo en el otro sentido
            b2Body* body4 = crearCuerpo(5,15,2);
            b2Body* body5 = crearSoporte(5,15,0);

            revoluteJointDef.bodyA = body4;
            revoluteJointDef.bodyB = body5;
            revoluteJointDef.collideConnected = false;
            revoluteJointDef.localAnchorA.Set(0,0);//the top right corner of the box
            revoluteJointDef.localAnchorB.Set(0,0);//center of the circle
            revoluteJointDef.enableMotor = true;
            revoluteJointDef.motorSpeed = -5;
            revoluteJointDef.maxMotorTorque = 5000;

            joint = (b2RevoluteJoint*) m_world->CreateJoint( &revoluteJointDef );
            body->ResetMassData();
  
            //creo un cuadrado
            b2Body* body6 = crearCuadrado(5,30);
            
  
  
  //creo otro engranaje
  //b2Body* m_bodyC;
  //b2BodyDef bodyDef3;
  //bodyDef3.type = b2_dynamicBody;
  //bodyDef3.position.Set(1, 10);
  //circleShape.m_radius = 2;
  //fixtureDef.shape = &circleShape;
  //m_bodyC = m_world->CreateBody( &bodyDef3 );
  //m_bodyC->CreateFixture( &fixtureDef );
  
  //b2Body* body2;
  //circleShape.m_radius = 0;
  //fixtureDef.shape = &circleShape;
  //bodyDef.type = b2_staticBody;
  //bodyDef.position.Set(m_bodyC->GetPosition().x, m_bodyC->GetPosition().y);
  //body2 = m_world->CreateBody(&bodyDef);
  //body2->CreateFixture(&fixtureDef);
  
  //b2RevoluteJointDef revoluteJointDef2;
  //revoluteJointDef2.bodyA = m_bodyC;
  //revoluteJointDef2.bodyB = body2;
  //revoluteJointDef2.collideConnected = false;
  //revoluteJointDef2.localAnchorA.Set(0,0);//the top right corner of the box
  //revoluteJointDef2.localAnchorB.Set(0,0);//center of the circle
  //revoluteJointDef2.enableMotor = true;
  //revoluteJointDef2.motorSpeed = -2;
  //revoluteJointDef2.maxMotorTorque = 5000;

  //b2RevoluteJoint* joint2;
  //joint2 = (b2RevoluteJoint*) m_world->CreateJoint( &revoluteJointDef2 );
  //m_bodyC->ResetMassData();

  //b2GearJointDef gear;
  //gear.bodyA = m_bodyA;
  //gear.bodyB = m_bodyC;
  //gear.joint1 = joint;
  //gear.joint2 = joint2;
  //b2GearJoint* gearJoint;
  //gearJoint = (b2GearJoint*) m_world->CreateJoint(&gear);
  
	
	//m_wheel1 = m_world->CreateBody(&bodyDef);
  
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
	  b2PolygonShape p;
	  p.SetAsBox(1.9,1.9);
	  fixtureDef.shape = &circleShape;
	  //fixtureDef.shape = &p;
	  body = m_world->CreateBody( &bodyDef );
	  body->CreateFixture( &fixtureDef );
	  return body;
        }
        
        
        b2Body* crearCuadrado(float x, float y){
          b2Body* body;
	  b2BodyDef bodyDef;
	  bodyDef.type = b2_dynamicBody;
	  bodyDef.position.Set(x,y);
	  b2FixtureDef fixtureDef;
	  b2PolygonShape shape;
	  shape.SetAsBox(1,1);
	  fixtureDef.shape = &shape;
	  body = m_world->CreateBody( &bodyDef );
	  body->CreateFixture( &fixtureDef );
	  return body;
        }
        
	void setVelocidad(float velocidad){
	    joint->SetMotorSpeed(velocidad);
	}
	
	void setRadio(float radio,b2Body* body, b2Body* body2){
	m_world->DestroyBody(body);
	m_world->DestroyBody(body2);
	
	b2Body* cuerpo = crearCuerpo(-3,10,radio);
	b2Body* soporte = crearSoporte(-3,10,0.1);
	//joint
	  b2RevoluteJointDef revoluteJointDef;
          revoluteJointDef.bodyA = cuerpo;
          revoluteJointDef.bodyB = soporte;
          revoluteJointDef.collideConnected = false;
          revoluteJointDef.localAnchorA.Set(0,0);//the top right corner of the box
          revoluteJointDef.localAnchorB.Set(0,0);//center of the circle
          revoluteJointDef.enableMotor = true;
          revoluteJointDef.motorSpeed = 5;
          revoluteJointDef.maxMotorTorque = 5000000;

          joint = (b2RevoluteJoint*) m_world->CreateJoint( &revoluteJointDef );
          cuerpo->ResetMassData();
	

}


	void Step(Settings* settings)
	{
		m_debugDraw.DrawString(5, m_textLine, "Prueba Motor");
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new Motor();
	}

	b2Body* m_car;
	b2Body* m_wheel1;
	b2Body* m_wheel2;

	float32 m_hz;
	float32 m_zeta;
	float32 m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2RevoluteJoint* joint;
        
	
};

#endif /* MOTOR_H_ */
