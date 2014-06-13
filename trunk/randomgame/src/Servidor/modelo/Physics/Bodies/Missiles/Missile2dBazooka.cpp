#include "Missile2dBazooka.h"

Missile2dBazooka::Missile2dBazooka()
{

}

Missile2dBazooka::Missile2dBazooka(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement)
{
	
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+(BULLET_RADIUS/2), posY+(BULLET_RADIUS/2) );
	
	/* Importantisimo! lo seteo como weapon!! */
	this->type = type;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2FixtureDef myFixtureDef;
   
	b2CircleShape circleShape;
	circleShape.m_radius = BULLET_RADIUS;
	circleShape.m_p.Set(0,0);

	myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
	myFixtureDef.friction = 0.01;
	myFixtureDef.restitution = 0;
	myFixtureDef.userData = (void*)UD_MISSIL;
	myBodyDef.position.Set(posX, posY);
    b2Body* body = this->myWorld->CreateBody(&myBodyDef);

	body->CreateFixture(&myFixtureDef);

	body->SetTransform( body->GetPosition(), 0.0 );
	body->SetFixedRotation(false);

	this->body = body;
	this->body->SetUserData(modelElement);


	//Valor de la explosión
	this->explosion.radio=30;
	//impulso inicial
	this->body->ApplyLinearImpulse( b2Vec2 (30, 30 ),this->body->GetWorldCenter() );

}

Missile2dBazooka::~Missile2dBazooka(){}



void Missile2dBazooka::animate( float time ){

	//Use userdata to reflect changes in physics to model
	GameElement* myWeapon = static_cast<GameElement*>(this->body->GetUserData());

	if ( static_cast<Missile*>(myWeapon)->hasDelayedExplosion() ){
		static_cast<Missile*>(myWeapon)->updateExplode( time );
	}

	if ( static_cast<Missile*>(myWeapon)->hasExploded() ){
		myWeapon->setAction(EXPLOSION);
	} else{

		if ( myWeapon->myLastAction == CREATE_MISSIL ){
			myWeapon->setAction(CREATE_MISSIL);
			myWeapon->myLastAction = MISSIL_FLYING;
		}else{
			myWeapon->setAction(MISSIL_FLYING);
		}

	}

	//Actualizo la posicion
	b2Vec2 f = this->body->GetPosition();
	myWeapon->setPosition(std::make_pair( f.x,f.y) );
	myWeapon->changed = true;

	//Actualizo tiempo restante
	myWeapon->setLife( static_cast<Missile*>(myWeapon)->remainingTime(time) );


}