#include <Box2D/Box2D.h>
#include <math.h>
#include "Triangulo.h"
#include "../../../../utils/Log.h"

Triangle::Triangle(	ElementType type, float posX, float posY, float angle, float scale, 
				float masa, b2World *myWorld, GameElement* modelElement, bool fixed)
{


	this->myWorld = myWorld;
	this->center = b2Vec2( posX, posY);
	this->angle = angle;
	this->masa = masa;
	this->type = type;
	this->angle = angle;


	b2BodyDef myBodyDef;

	if (!fixed){
		myBodyDef.type = b2_dynamicBody;
	}else{
		myBodyDef.type = b2_staticBody;
	}
	myBodyDef.position.Set(posX, posY); //starting position (at center)


	b2Body* dynamicBody = this->myWorld->CreateBody(&myBodyDef);
	this->body = dynamicBody;
	this->body->SetUserData(modelElement);

	b2Vec2 *vertices;

	b2PolygonShape  triangleShape;
	vertices = new b2Vec2[3];
	vertices[0] = b2Vec2( (posX - 0.5*scale), (posY - 0,43*scale));
	vertices[1] = b2Vec2( (posX + 0.5*scale), (posY - 0,43*scale));
	vertices[2] = b2Vec2( posX, (posY + 0,43*scale));
	triangleShape.Set(vertices,3);
	
	b2FixtureDef triangleFixtureDef;
	triangleFixtureDef.shape = &triangleShape;
	triangleFixtureDef.density = 1;
	dynamicBody->CreateFixture(&triangleFixtureDef);
	
	dynamicBody->SetTransform( dynamicBody->GetPosition(), angle*DEGTORAD );

	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	Log::d("Posicion Inicial: %.3f, %.3f", v.x, v.y);
	//this->GetVertex();

}



//At each step links current box2d with model data
void Triangle::animate(){
	//Use userdata to reflect changes in physics to model
	//ToDo @aliguo
	GameElement* ge = static_cast<GameElement*>(this->body->GetUserData());
	b2Vec2 f = this->body->GetPosition();
	Log::d("Nueva posicion (Physics): %.3f, %.3f", f.x, f.y);

	ParserYaml* aParser = ParserYaml::getInstance();
	float x = f.x;
	//float y = (-1*f.y)+atoi((aParser->getEscenarioAltoU()).c_str() );
	float y = f.y;
	ge->setPosition(std::make_pair( x,y) );
	Log::d("Nueva posicion (Modelo): %.3f, %.3f", x,y);


}


std::list<std::pair<float,float>> Triangle::GetVertex(){

    //verts now contains world co-ords of all the verts
	b2Vec2 v = this->body->GetWorldPoint(b2Vec2( 0,0));
	Log::d("Posicion central 0,0: %.3f, %.3f", v.x, v.y);
	b2PolygonShape* poly = (b2PolygonShape*)this->body->GetFixtureList()->GetShape();
	std::list<std::pair<float,float>> vertexList;
	int count = poly->GetVertexCount();
	ParserYaml* aParser = ParserYaml::getInstance();

	for( int i = 0; i < count; i++ ){
		b2Vec2 verts = poly->GetVertex(i);
		b2Vec2 f = this->body->GetWorldPoint(verts);
		Log::d("Posicion vert %d: %.3f, %.3f",i, f.x, f.y);
		//float x = f.x + (atoi((aParser->getEscenarioAnchoU()).c_str() )/2);
		float x = f.x;
		float y = (-1*f.y)+atoi((aParser->getEscenarioAltoU()).c_str() );
		//float y = f.y;
		Log::d("Posicion vert (Modelo) %d: %.3f, %.3f",i, x, y);		
		vertexList.push_back(std::make_pair(x,y));
	}

	return vertexList;

}


void Triangle::touch(Body* touchingWith, b2World* mundo) {

}

Triangle::~Triangle() {
	// Destroy from model first
	// ToDo @aliguo
}


