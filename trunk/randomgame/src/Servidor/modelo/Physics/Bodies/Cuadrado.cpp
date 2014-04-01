#include <Box2D/Box2D.h>
#include <math.h>
#include "Cuadrado.h"
#include "../../../../utils/Log.h"

Cuadrado::Cuadrado(ElementType type, int posX, int posY, float h, 
		float w, float masa, float angle, b2World *myWorld, GameElement *modelElement)
{
	this->myWorld = myWorld;
	this->center = b2Vec2( posX+(w/2), posY+(h/2) );
	this->angle = angle;
	this->masa = masa;
	this->type = type;
	this->width = w;
	this->height = h;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(posX+w/2, posY+h/2); //starting position (at center)
	myBodyDef.angle = (angle * DEGTORAD); 


	b2Body* dynamicBody = this->myWorld->CreateBody(&myBodyDef);
	this->body = dynamicBody;
	this->body->SetUserData(modelElement);


	b2PolygonShape boxShape;
	
	boxShape.SetAsBox(h,w);
	//boxShape.SetAsBox(1,1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);
	b2Vec2 v = this->body->GetPosition();

	Log::d("Posicion Inicial: %.3f, %.3f", v.x, v.y);

}


void Cuadrado::GetVertex(){

	
    //verts now contains world co-ords of all the verts
	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	Log::d("Posicion central 0,0: %.3f, %.3f", v.x, v.y);

	b2PolygonShape* poly = (b2PolygonShape*)this->body->GetFixtureList()->GetShape();

	b2Vec2 verts = poly->GetVertex(0);
	b2Vec2 f = this->body->GetWorldPoint(verts);
	Log::d("Posicion vert 0: %.3f, %.3f", f.x, f.y);

	verts = poly->GetVertex(1);
	f = this->body->GetWorldPoint(verts);
	Log::d("Posicion vert 1: %.3f, %.3f", f.x, f.y);

	verts = poly->GetVertex(2);
	f = this->body->GetWorldPoint(verts);
	Log::d("Posicion vert 2: %.3f, %.3f", f.x, f.y);

	verts = poly->GetVertex(3);
	f = this->body->GetWorldPoint(verts);
	Log::d("Posicion vert 3: %.3f, %.3f", f.x, f.y);



}

//At each step links current box2d with model data
void Cuadrado::animate(){
	//Use userdata to reflect changes in physics to model
	//ToDo @aliguo
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	b2Vec2 v = this->body->GetPosition();
	Log::d("Nueva posicion (Physics): %.3f, %.3f", v.x, v.y);
	ge->setPosition(std::make_pair( (v.x * 50.0f) , (v.y * 50.0f) ) );
	Log::d("Nueva posicion (Modelo): %.3f, %.3f", (v.x * 50.0f), (v.y * 50.0f));
	this->GetVertex();

}

void Cuadrado::touch(Body* touchingWith, b2World* mundo) {

}

Cuadrado::~Cuadrado() {
	// Destroy from model first
	// ToDo @aliguo
}

