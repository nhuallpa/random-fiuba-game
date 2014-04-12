#include <Box2D/Box2D.h>
#include <math.h>
#include "Cuadrado.h"
#include "../../../../utils/Log.h"

Cuadrado::Cuadrado(ElementType type, float posX, float posY, float h, 
		float w, float masa, float angle, b2World *myWorld, GameElement *modelElement)
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
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(posX+w/2, posY+h/2); //starting position (at center)
	myBodyDef.angle = (angle * DEGTORAD); 


	b2Body* dynamicBody = this->myWorld->CreateBody(&myBodyDef);
	this->body = dynamicBody;
	this->body->SetUserData(modelElement);


	b2PolygonShape boxShape;
	
	boxShape.SetAsBox(h/2,w/2);
	//boxShape.SetAsBox(1,1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);
	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	Log::d("Posicion Inicial: %.3f, %.3f", v.x, v.y);
	//this->GetVertex();
	
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	ge->setVertexList(this->GetVertex());

}



std::list<std::pair<float,float>> Cuadrado::GetVertex(){

    //Los vertices los devuelve con las coordenadas cambiadas al sistemas de SDL (0,0) arriba a la izq

	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	//Log::d("Posicion central 0,0: %.3f, %.3f", v.x, v.y);
	b2PolygonShape* poly = (b2PolygonShape*)this->body->GetFixtureList()->GetShape();
	std::list<std::pair<float,float>> vertexList;
	int count = poly->GetVertexCount();
	ParserYaml* aParser = ParserYaml::getInstance();

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
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	b2Vec2 f = this->body->GetPosition();
	//Log::d("Nueva posicion (Physics): %.3f, %.3f", f.x, f.y);

	ParserYaml* aParser = ParserYaml::getInstance();
	float x = f.x;
	float y = (-1*f.y)+atoi((aParser->getEscenarioAltoU()).c_str() );
	//float y = f.y;
	ge->setPosition(std::make_pair( x,y) );
	//Log::d("Nueva posicion (Modelo): %.3f, %.3f", x,y);
	ge->setVertexList(this->GetVertex());

}

void Cuadrado::touch(Body* touchingWith, b2World* mundo) {

}

Cuadrado::~Cuadrado() {
	// Destroy from model first
	// ToDo @aliguo
}

