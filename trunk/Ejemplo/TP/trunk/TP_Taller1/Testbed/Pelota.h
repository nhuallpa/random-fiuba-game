#ifndef Pelota_H
#define Pelota_H

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Pelota : public Test
{
	public:
	b2Body* circulo2;
	b2Body* circulo3;
	b2Body* circuloKin;
	b2Body* nicePlataforma;
	b2Body* globoHelius;
	
	Pelota() {

		circulo2 = crearCirculoDinamico(10,20,0.5,7,2);
		circulo3 = crearCirculoDinamico(10,20,0.5,7,5);
		globoHelius = crearGloboDeHelio(40,40,0.5,0.1,1);
		circuloKin = crearCirculoKinematico(0,30,1,1,1,1);
		nicePlataforma = crearPlataforma();
		globoHelius = crearGloboDeHelio(-10,0,0.1,1,1);
		b2Body* balancin = crearBalancin();

		//Ato el globo al balancin
		b2RopeJointDef ropeJointDef;
  		ropeJointDef.bodyA = globoHelius;
  		ropeJointDef.bodyB = balancin;
  		ropeJointDef.collideConnected = true;
		ropeJointDef.maxLength=5;

		//place the bodyB anchor at the edge of the circle 
  		ropeJointDef.localAnchorB.Set(5,0);
		ropeJointDef.localAnchorA.Set(0,0);
 
		m_world->CreateJoint( &ropeJointDef );
		
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

	b2Body* crearCirculoDinamico(float x, float y, float coefRes, float dens, float radio) {	
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(x, y); //a little to the left
		b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);
		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = radio; //radius
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
		myFixtureDef.density = dens;
		myFixtureDef.restitution = coefRes;
		dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body
		return dynamicBody1;
	
	}

	b2Body* crearCirculoKinematico(float x, float y, float coefRes, float dens, float radio, float torqLineal) {
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(x, y); //a little to the left
		b2Body* kinematicBody1 = m_world->CreateBody(&myBodyDef);
		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = radio; //radius
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
		myFixtureDef.density = dens;
		myFixtureDef.restitution = coefRes;
		kinematicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body	
		kinematicBody1->SetAngularVelocity( 360 * DEGTORAD ); 
		return kinematicBody1;
	}

	b2Body* crearGloboDeHelio(float x, float y, float coefRes, float dens, float radio) {
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(x, y); //a little to the left
		b2Body* kinematicBody1 = m_world->CreateBody(&myBodyDef);
		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0); //position, relative to body position
		circleShape.m_radius = radio; //radius
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
		myFixtureDef.density = dens;
		myFixtureDef.restitution = coefRes;
		kinematicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body	
		
		return kinematicBody1;
	}

	b2Body* crearPlataforma(){
		b2BodyDef myBodyDef;
		//La plataforma es estatica porque no se ve
		//afectada por el resto de los objetos del mundo.
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(20, 20);
		myBodyDef.angle = 0;
		b2Body* cuerpoPlataforma = m_world->CreateBody(&myBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(5, 1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		cuerpoPlataforma->CreateFixture(&boxFixtureDef);

		return cuerpoPlataforma;
	}
	
	b2Body* crearBalancin(){
		//Balancin es un cuerpo de dos fixtures unidos por un joint Revolute.
		//Uno es una plataforma que gira, y la otra es un pin justo abajo.		
		
		//Plataforma
		b2FixtureDef plataforma;
		plataforma.density=1;
		plataforma.restitution=0.9;
		b2PolygonShape boxShape;
		boxShape.SetAsBox(10, 0.5);
		plataforma.shape = &boxShape;
		
		//pin es un objeto en el medio de la plataforma del balancin.
		b2FixtureDef pin;
		b2PolygonShape triangulo;
		b2Vec2 vertices[2];
		vertices[0].Set(-1,-1);
		vertices[1].Set(1,-1);
		vertices[2].Set(0,1);
		triangulo.Set(vertices,3);
		triangulo.SetAsBox(0.5,0.5);
		pin.shape=&triangulo;

		//Creo el cuerpo
		b2BodyDef defBalancin;
		defBalancin.type = b2_dynamicBody;
		defBalancin.position.Set(10, 20);
		defBalancin.angle=45*DEGTORAD;
		b2Body* balancin = m_world->CreateBody(&defBalancin);
		balancin->CreateFixture(&plataforma);
	
		b2BodyDef soporteDef;
		soporteDef.type = b2_staticBody;
		soporteDef.position.Set(balancin->GetWorldCenter().x,balancin->GetWorldCenter().y);
		b2Body* soporte = m_world->CreateBody(&soporteDef);
		soporte->CreateFixture(&pin);

		b2RevoluteJointDef revoluteJointDef;
  		revoluteJointDef.bodyA = balancin;
  		revoluteJointDef.bodyB = soporte;
  		revoluteJointDef.collideConnected = false;

		//place the bodyB anchor at the edge of the circle 
  		revoluteJointDef.localAnchorB.Set(0,1);
 
		revoluteJointDef.enableLimit = true;
  		revoluteJointDef.lowerAngle = -45 * DEGTORAD;
  		revoluteJointDef.upperAngle =  45 * DEGTORAD;
		m_world->CreateJoint( &revoluteJointDef );
		

		return balancin;
	}

	void Step(Settings* settings)
	{
	    //run the default physics and rendering
	    Test::Step(settings); 
	    float force = globoHelius->GetMass()*(-9.8);
	    float impulso = globoHelius->GetMass()*4;
	    if(globoHelius->GetLinearVelocity().y < 4)            
		globoHelius->ApplyLinearImpulse(b2Vec2(0,impulso),globoHelius->GetWorldCenter());
	    //show some text in the main screen
	    m_debugDraw.DrawString(5, m_textLine, "Prueba de pelotas");
	    m_textLine += 15;
	}

	static Test* Create()
	{
	    return new Pelota;
	}
};

#endif
