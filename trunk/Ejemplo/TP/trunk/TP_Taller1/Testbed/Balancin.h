#ifndef Balancin_H
#define Balancin_H

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define DIM_SOPORTE 0.5

class Balancin : public Test
{
	public:
	
		
	Balancin() {

		this->dimensiones=b2Vec2(0.5,5);		
		this->anguloInicial=10*DEGTORAD;		
		this->posicionInicial=b2Vec2(0,20);
		this->cuerpo=crearCuerpo(m_world);
		this->soporte=crearSoporte(cuerpo, m_world);
		crearJuntura(cuerpo,soporte,m_world);
			
		b2BodyDef myBodyDef;
		b2FixtureDef myFixtureDefBorde;		
		b2EdgeShape edgeShape;
  		edgeShape.Set( b2Vec2(-15,0), b2Vec2(15,0) );
  		myFixtureDefBorde.shape = &edgeShape;
		myBodyDef.type = b2_staticBody; //change body type
		
		myBodyDef.position.Set(0,0); //middle, bottom
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);
		staticBody->CreateFixture(&myFixtureDefBorde); //add a fixture to the body

	} //do nothing, no scene yet

	b2Body* crearSoporte(b2Body* plataforma,b2World* mundo) {
		//Por ahora creo  un soporte que es un triángulo
		// estático de 1x1.
		b2FixtureDef pin;
		b2PolygonShape cuadrado;
		cuadrado.SetAsBox(DIM_SOPORTE,DIM_SOPORTE);
		pin.shape=&cuadrado;
		b2BodyDef soporteDef;
		soporteDef.type = b2_staticBody;
		soporteDef.position=plataforma->GetWorldCenter();
		b2Body* soporte = mundo->CreateBody(&soporteDef);
		soporte->CreateFixture(&pin);
		return soporte;
	}
	b2Body* crearCuerpo(b2World* mundo) {
		//Plataforma del subibaja.
		b2FixtureDef plataforma;
		plataforma.density=1;
		plataforma.restitution=0.9;
		b2PolygonShape boxShape;
		boxShape.SetAsBox(10, 0.5);
		plataforma.shape = &boxShape;
		//Creo el cuerpo
		b2BodyDef defBalancin;
		defBalancin.type = b2_dynamicBody;
		defBalancin.position.Set(posicionInicial.x, posicionInicial.y);
		defBalancin.angle=(this->anguloInicial*DEGTORAD);
		b2Body* balancin = mundo->CreateBody(&defBalancin);
		balancin->CreateFixture(&plataforma);
		return balancin;
	}

	void crearJuntura(b2Body* plataforma, b2Body* soporte, b2World* mundo) {
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = plataforma;
		revoluteJointDef.bodyB = soporte;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorB.Set(0,DIM_SOPORTE);
		revoluteJointDef.enableLimit = true;
		revoluteJointDef.lowerAngle = -45 * DEGTORAD;
		revoluteJointDef.upperAngle =  45 * DEGTORAD;
		mundo->CreateJoint( &revoluteJointDef );
	}
	void Step(Settings* settings)
	{
	    //run the default physics and rendering
	    Test::Step(settings); 
	    m_debugDraw.DrawString(5, m_textLine, "Prueba de balancin");
	    m_textLine += 15;
	}

	static Test* Create()
	{
	    return new Balancin;
	}
private:

	b2Vec2 dimensiones;
	b2Body* soporte;
	float anguloInicial;
	b2Body* cuerpo;
	b2Vec2 posicionInicial;
};

#endif
