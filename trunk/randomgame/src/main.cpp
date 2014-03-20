
// Descomentar este código para probar SDL
#include <iostream>

#include "./Administrador.h"
#include "./utils/Log.h"
#include <Box2D/Box2D.h>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils/ParserYaml.h"
#include "utils/PersistYaml.h"

#include <cstdio>
using namespace std;

void persistir(){
	PersistYaml* aPersist=PersistYaml::getInstance();
	PersistYaml* aPersist2=PersistYaml::getInstance();
	aPersist->setNivelNombre("nivel1");
	aPersist->setNivelFondo("fondo.png");
	aPersist->setNivelAlto("999");
	aPersist->setNivelAncho("777");
	aPersist->setElem("circulo","12","46","90");
	aPersist->setElem("triangulo","122","462","902");
	aPersist2->escribirYaml("out.yaml");


}


int main(int argc, char* argv[]) {

	//parsear();
	std::string path = (argc > 1) ? argv[1] : DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);

	//std::cout<<"data elementos:\n\t";
	//for(unsigned i=0;i<aParser->getCantDataElem();i++){
	//	std::cout<<"nombre: "<< aParser->getDataElemNombre(i)<<"\n\t";
	//	std::cout<<"imagen: "<< aParser->getDataElemImagen(i)<<"\n\t";
	//}


	//std::cout<<"niveles:\n\t";
	//for(unsigned i=0;i<aParser->getCantNiveles();i++){
	//	std::cout<<"nombre: "<< aParser->getNivelNombre()<<"\n\t";
	//	std::cout<<"fondo: "<< aParser->getNivelFondo()<<"\n\t";
	//	std::cout<<"ancho: "<< aParser->getNivelAncho()<<"\n\t";
	//	std::cout<<"alto: "<< aParser->getNivelAlto()<<"\n\t";
	//	
	//	
	//std::cout<<"elementos:\n\t\t";
	//for(unsigned j=0;j<aParser->getCantElem(i);j++){
	//		std::cout<<"tipo: "<< aParser->getElemNombre(i,j)<<"\n\t\t";
	//		std::cout<<"x: "<< aParser->getElemX(i,j)<<"\n\t\t";
	//		std::cout<<"y: "<< aParser->getElemY(i,j)<<"\n\t\t";
	//		std::cout<<"angulo: "<< aParser->getElemAngulo(i,j)<<"\n\t\t";
	//	}
	//}




		B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	













	Administrador administrador; 
	administrador.run();

	

	return 0;
}


////Descomentar este código para probar YAML



