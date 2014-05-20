#include "Cuadrado.h"


Cuadrado::Cuadrado(ElementType type, float posX, float posY, float h, 
		float w, float masa, float angle, b2World *myWorld, GameElement *modelElement, bool fixed)
{

	//ToDo: escalar
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+(w/2), posY+(h/2) );
	this->angle = angle;
	this->masa = masa;
	this->type = type;
	this->width = w;
	this->height = h;

	b2BodyDef myBodyDef;
	myBodyDef.position.Set(posX, posY); //starting position (at center)
	myBodyDef.angle = (angle * DEGTORAD); 


	//body definition
    if (!fixed){
		myBodyDef.type = b2_dynamicBody;
	}else{
		myBodyDef.type = b2_staticBody;
	}

	b2Body* dynamicBody = this->myWorld->CreateBody(&myBodyDef);
	this->body = dynamicBody;
	this->body->SetUserData(modelElement);


	b2PolygonShape boxShape;
	
	boxShape.SetAsBox(w/2,h/2);
	//boxShape.SetAsBox(1,1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.friction = 0.99f;
	boxFixtureDef.restitution = 0;
	dynamicBody->CreateFixture(&boxFixtureDef);

	this->body->SetTransform( body->GetPosition(), angle*DEGTORAD );
	this->body->SetFixedRotation(true);
	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	//this->GetVertex();
	
	this->masa=this->body->GetMass(); //extenderlo a los otros bodies o ARREGLARLO: (ToDo ARIEL)

}



std::list<std::pair<float,float>> Cuadrado::GetVertex(){

    //Los vertices los devuelve con las coordenadas cambiadas al sistemas de SDL (0,0) arriba a la izq

	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	//Log::d("Posicion central 0,0: %.3f, %.3f", v.x, v.y);
	b2PolygonShape* poly = (b2PolygonShape*)this->body->GetFixtureList()->GetShape();
	std::list<std::pair<float,float>> vertexList;
	int count = poly->GetVertexCount();

	for( int i = 0; i < count; i++ ){
		b2Vec2 verts = poly->GetVertex(i);
		b2Vec2 f = this->body->GetWorldPoint(verts);
		//Log::d("Posicion vert %d: %.3f, %.3f",i, f.x, f.y);
		//float x = f.x + (atoi((aParser->getEscenarioAnchoU()).c_str() )/2);
		float x = f.x;
		float y = f.y;
		//Log::d("Posicion vert (Modelo) %d: %.3f, %.3f",i, x, y);		
		vertexList.push_back(std::make_pair(x,y));
	}

	return vertexList;

}

//At each step links current box2d with model data
void Cuadrado::animate(){
	//Use userdata to reflect changes in physics to model
	//ToDo @aliguo

	b2Vec2 f = this->body->GetPosition();
	//Log::d("Nueva posicion (Physics): %.3f, %.3f", f.x, f.y);

	float x = f.x;
	float y = (-1*f.y)+1000 ;
	//float y = f.y;
}

void Cuadrado::touch(Body* touchingWith, b2World* mundo) {

}

Cuadrado::~Cuadrado() {
	// Destroy from model first
	// ToDo @aliguo
}


void Cuadrado::setPosition(float x, float y,float rot){
	this->body->SetTransform(b2Vec2(x,y),rot*DEGTORAD);
	this->body->SetLinearVelocity( b2Vec2( 0, 0 ) );
	this->body->SetAngularVelocity( 0 );
	this->body->SetAwake(true);
}
