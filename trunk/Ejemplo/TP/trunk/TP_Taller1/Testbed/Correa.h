#ifndef Correa_H_
#define Correa_H_

#define RADIO_SOPORTE 0.1
#define DENSIDAD 1
#define MOTOR_SPEED_ 500
#define MAX_TORQUE_ 500


class Correa: public Test {
public:
	Correa()
	{
		float motorSpeed = 5;
		float maxTorque = 10;     
		//MOTOR
  		b2Body* motor = crearCuerpo(m_world, b2Vec2(0,10), 5);
		b2Body* soporteMotor = crearSoporte(m_world, motor);
		b2Joint* rJointMotor = crearRevoluteJoint(m_world,soporteMotor, motor,
							  true, MOTOR_SPEED_, MAX_TORQUE_);		
		//ENGRANAJE
		b2Body* engranaje = crearCuerpo(m_world, b2Vec2(0,20), 3);
		b2Body* soporteEngranaje1 = crearSoporte(m_world, engranaje);
		b2Joint* rJointEngranaje1 = crearRevoluteJoint(m_world,soporteEngranaje1, engranaje,
							  false, MOTOR_SPEED_, MAX_TORQUE_);

		//OTRO ENGRANAJE
		b2Body* engranaje2 = crearCuerpo(m_world, b2Vec2(10,20), 3);
		b2Body* soporteEngranaje2 = crearSoporte(m_world, engranaje2);
		b2Joint* rJointEngranaje2 = crearRevoluteJoint(m_world,soporteEngranaje2, engranaje2,
							  false, MOTOR_SPEED_, MAX_TORQUE_);
	
		//CORREA MOTOR - ENGRANAJE1
		putCorrea(m_world, soporteMotor, soporteEngranaje1, rJointMotor, rJointEngranaje1, 1);
		//CORREA DE ENGRANAJE1 A ENGRANAJE2
		putCorrea(m_world, soporteEngranaje1, soporteEngranaje2, rJointEngranaje1, rJointEngranaje2, 1);
	}

	b2Joint* putCorrea(b2World* mundo, b2Body* cuerpo1, b2Body* cuerpo2,
		b2Joint* joint1, b2Joint* joint2, float ratio){

		crearGearJoint(mundo, cuerpo1,cuerpo2,joint1,joint2,ratio);
	}


	//PARTE DE CUERPOROTATIVO
	b2Body* crearCuerpo(b2World* mundo, b2Vec2 posicion, float radio){
		  b2Body* body;
		  b2BodyDef bodyDef;
		  bodyDef.type = b2_dynamicBody;
		  bodyDef.position.Set(posicion.x, posicion.y);
		  b2FixtureDef fixtureDef;
		  fixtureDef.density = DENSIDAD;
		  b2CircleShape circleShape;
		  circleShape.m_radius = radio;
		  fixtureDef.shape = &circleShape;
		  body = mundo->CreateBody( &bodyDef );
		  body->CreateFixture( &fixtureDef );
		  return body;
	}

	b2Body* crearSoporte(b2World* mundo, b2Body* cuerpo){
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
	//FIN PARTE CUERPOROTATIVO

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
		return new Correa();
	}
	
};

#endif /* MOTOR_H_ */
