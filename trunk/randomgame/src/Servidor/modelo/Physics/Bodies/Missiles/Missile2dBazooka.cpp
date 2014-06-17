#include "Missile2dBazooka.h"

Missile2dBazooka::Missile2dBazooka()
{

}

Missile2dBazooka::Missile2dBazooka(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement)
{
	this->myWorld = myWorld;
	

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
	float angx = cosf(angle_x  * PI / 180.0);
	float angy = sinf(angle_y  * PI / 180.0);

	if ( angx < 0 ){
		myBodyDef.position.Set(posX - 2.0f, posY);
		this->setPosition(posX - 2.0f, posY,0);
	}else if ( angx > 0){
		myBodyDef.position.Set(posX + 2.0f, posY);
		this->setPosition(posX + 2.0f, posY,0);
	}else{
		myBodyDef.position.Set(posX, posY + 2.0f);
		this->setPosition(posX , posY + 2.0f,0);
	}

	//myBodyDef.position.Set(posX, posY);
    b2Body* body = this->myWorld->CreateBody(&myBodyDef);

	body->CreateFixture(&myFixtureDef);
	body->SetBullet(true);

	printf("\nCreating weapon at: %f, %f",posX,posY);
	//body->SetTransform( body->GetPosition(), 0.0 );
	body->SetFixedRotation(false);

	this->body = body;
	this->body->SetUserData(modelElement);
		
	//impulso inicial

	float factor_x = angx*fuerzaDisparo*SHOOT_POWER*BAZOOKA_X_FACTOR;
	float  factor_y = angy*fuerzaDisparo*SHOOT_POWER;
	printf("\nAngle x,y: %f, %f \nFuerza: %f \nFactor <X,Y>: %f,%f",angle_x,angle_y,fuerzaDisparo,factor_x,factor_y);

	this->body->ApplyLinearImpulse( b2Vec2(factor_x, factor_y ),this->body->GetWorldCenter() );
	
	modelElement->myLastAction = CREATE_MISSIL;
	modelElement->setAlive(true);

	/* Defino radio de explosion */
	this->explosion.radio = EXPLODE_RSMALL;
	
	printf("\nMisil de bazooka Impulsado");
}

Missile2dBazooka::~Missile2dBazooka(){}



void Missile2dBazooka::animate( float time ){

	//Use userdata to reflect changes in physics to model
	GameElement* myWeapon = static_cast<GameElement*>(this->body->GetUserData());

	if ( myWeapon->myLastAction == CREATE_MISSIL ){
		myWeapon->setAction(CREATE_MISSIL);
		myWeapon->myLastAction = MISSIL_FLYING;
	}else{
		myWeapon->setAction(MISSIL_FLYING);
	}

	//Actualizo la posicion
	b2Vec2 f = this->body->GetPosition();
	myWeapon->setPosition(std::make_pair( f.x,f.y) );
	myWeapon->changed = true;


}

void Missile2dBazooka::explode( ){



}