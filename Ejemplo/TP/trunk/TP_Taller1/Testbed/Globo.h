#ifndef Globo_H
#define Globo_H

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define MAX_VEL 4

class Globo : public Test
{
	public:
	
	
	Globo() {
		this->coeficienteRestitucion = 0.9;
		this->densidad = 0.2;
		this->posicionInicial = b2Vec2(0,10);
		this->radio = 1;
		this->cuerpo = crearCuerpo(m_world);
		

	} //do nothing, no scene yet

	void Step(Settings* settings)
	{
	    //run the default physics and rendering
	    Test::Step(settings);
	    vivir(); 
	    m_debugDraw.DrawString(5, m_textLine, "Prueba de Globo");
	    m_textLine += 15;
	}
	
	void vivir(){
		float max_vel = MAX_VEL;
		float velocidadSubida = b2Max( this->cuerpo->GetLinearVelocity().y - 0.1f, max_vel );	
		float cambioVelocidad = velocidadSubida - this->cuerpo->GetLinearVelocity().y;		
		float impulso = cambioVelocidad*this->cuerpo->GetMass();
		//Para simular el movimiento rectilineo a velocidad constante
		//si el globo no supera la velocidad maxima le doy un tiki de impulso.
		this->cuerpo->ApplyLinearImpulse(b2Vec2(0,impulso), this->cuerpo->GetWorldCenter());
		
	}
	
	b2Body* crearCuerpo(b2World* mundo) {
		b2BodyDef myBodyDef;
		//Es dinamico porque se ve sujeto a toda la fisica del juego.
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position.Set(posicionInicial.x, posicionInicial.y);
		b2Body* pelotaCuerpo = mundo->CreateBody(&myBodyDef);
		//Tiene forma de circulo porq es una pelota.
		b2CircleShape circleShape;
		circleShape.m_p.Set(0, 0);
		circleShape.m_radius = this->radio;
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &circleShape;
		myFixtureDef.density = this->densidad;
		myFixtureDef.restitution = this->coeficienteRestitucion;
		pelotaCuerpo->CreateFixture(&myFixtureDef);
		return pelotaCuerpo;
	}

	static Test* Create()
	{
	    return new Globo;
	}
	private:
	float coeficienteRestitucion;
	float densidad;
	float radio;
	b2Body* cuerpo;
	b2Vec2 posicionInicial;

};

#endif
