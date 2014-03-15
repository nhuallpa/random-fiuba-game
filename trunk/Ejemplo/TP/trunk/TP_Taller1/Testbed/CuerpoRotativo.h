#ifndef MOTOR_H_
#define MOTOR_H_

#define RADIO_SOPORTE 0.1
#define DENSIDAD 1
#define MOTOR_SPEED 5 
#define MAX_TORQUE 10


class Motor: public Test {
public:
	Motor()
	{
		float motorSpeed = 5;
		float maxTorque = 10; 	    
  		crearCuerpoRotativo(b2Vec2(0,10), m_world, 0, 2, true, true);
	}
	
	
	void crearCuerpoRotativo(b2Vec2 posInicial,
			b2World* mundo, float angulo, float radio,
			bool sentidoAntihorario, bool isMotor) {
		// TODO Auto-generated constructor stub
		this->posicion = posInicial;
		this->angulo = angulo;
		this->radio = radio;
		this->cuerpo = crearCuerpo(mundo);
		this->soporte = crearSoporte(mundo);
		this->sentidoAntihorario = sentidoAntihorario;
		this->mundo = mundo;
		float motorSpeed = MOTOR_SPEED;
		float maxTorque = MAX_TORQUE;
		if (sentidoAntihorario){
			  this->rJoint = crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
					  isMotor, (-1)*motorSpeed, maxTorque);
		}else{
			this->rJoint = crearRevoluteJoint(mundo,this->soporte, this->cuerpo,
							  isMotor, motorSpeed, maxTorque);
		}

	}

	b2Body* crearCuerpo(b2World* mundo){
		  b2Body* body;
		  b2BodyDef bodyDef;
		  bodyDef.type = b2_dynamicBody;
		  bodyDef.position.Set(this->posicion.x, this->posicion.y);
		  b2FixtureDef fixtureDef;
		  fixtureDef.density = DENSIDAD;
		  b2CircleShape circleShape;
		  circleShape.m_radius = radio;
		  fixtureDef.shape = &circleShape;
		  body = mundo->CreateBody( &bodyDef );
		  body->CreateFixture( &fixtureDef );
		  return body;
	}

	b2Body* crearSoporte(b2World* mundo){
		  b2Body* body;
		  b2BodyDef bodyDef;
		  bodyDef.type = b2_staticBody;
		  bodyDef.position.Set(cuerpo->GetPosition().x, cuerpo->GetPosition().y);
		  b2FixtureDef fixtureDef;
		  b2CircleShape circleShape;
		  circleShape.m_radius = RADIO_SOPORTE;
		  fixtureDef.shape = &circleShape;
		  body = mundo->CreateBody( &bodyDef );
		  body->CreateFixture( &fixtureDef );
		  return body;
	}

	b2Joint* getJointAlSoporte(){
		return rJoint;
	}


	//PARTE DE JOINT MAKER
	b2GearJoint* crearGearJoint(b2World* mundo, b2Body* bodyA, b2Body* bodyB,
			b2Joint* jointA, b2Joint* jointb, float ratio) {
		b2GearJointDef gearJointDef;
		gearJointDef.bodyA = bodyA;
		gearJointDef.bodyB = bodyB;
		gearJointDef.joint1 = jointA;
		gearJointDef.joint2 = jointb;
		gearJointDef.ratio = ratio;
		//No sé si este casteo es necesario.
		b2GearJoint* engranaje = (b2GearJoint*) mundo->CreateJoint( &gearJointDef );
		return engranaje;

	}

	b2RevoluteJoint* crearRevoluteJoint(b2World* mundo, b2Body* soporte,
		b2Body* cuerpo, bool habilitarMotor, float velocidadMotor, float maxTorque) {
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = soporte;
		revoluteJointDef.bodyB = cuerpo;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorA.Set(0,0);
		revoluteJointDef.localAnchorB.Set(0,0);
		revoluteJointDef.enableMotor = habilitarMotor;
		revoluteJointDef.motorSpeed = velocidadMotor;
		revoluteJointDef.maxMotorTorque = maxTorque;
		//No sé si este casteo es necesario.
		b2RevoluteJoint* joint = (b2RevoluteJoint*) mundo->CreateJoint( &revoluteJointDef );
		return joint;

	}
	//FIN PARTE DE JOINT MAKER

	void setRadio(float radio){
		return;
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

	b2Vec2 posicion;
	float angulo;
	float radio;
	b2Body* cuerpo;
	b2Body* soporte;
	bool sentidoAntihorario;
	b2World* mundo;
	b2RevoluteJoint* rJoint;
    
	
};

#endif /* MOTOR_H_ */
