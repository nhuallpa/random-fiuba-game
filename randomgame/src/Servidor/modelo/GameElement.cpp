#include "GameElement.h"


GameElement::GameElement(int id, ElementType type, float posX, float posY, int degrees, int h, int w, float mass){
	
	this->id = id;
	this->changed = false;
	this->type = type;
	this->degrees = degrees;
	this->position = std::make_pair(posX,posY);
	this->height = h;
	this->width = w;
	this->mass = mass;
}

GameElement::GameElement(int id, float posX, float posY, float radius, float scale, float mass, bool fixed)
{
	this->id = id;
	this->changed = false;
	this->type = CIRCLE;
	this->position = std::make_pair(posX,posY);
	this->mass = mass;
	this->radius = radius;
	this->scale = scale;
	this->fixed = fixed;
}

GameElement::GameElement(const GameElement & aGameElement):
					id(aGameElement.id), changed(aGameElement.changed), 
					ratio(aGameElement.ratio), type(aGameElement.type),
					position(aGameElement.position), height(aGameElement.type), 
					mass(aGameElement.type), myBody(aGameElement.myBody),
					degrees(aGameElement.degrees), vertexList(aGameElement.vertexList),
					radius(aGameElement.radius), scale(aGameElement.scale),
					fixed(aGameElement.fixed)
{
}


void GameElement::setVertexList(std::list<std::pair<float,float>> l){
	this->vertexList = l;
}

void GameElement::setBody(void* ab){
	Log::d("Guardando: %p",ab); 
	this->myBody = ab;
}

int GameElement::getId(){
	return this->id;
}

std::list<std::pair<float,float>> & GameElement::getVertex(){
	return this->vertexList;
}

ElementType GameElement::getType(){
	return this->type;
}

int GameElement::getRotation(){
	return this->degrees;
}

int GameElement::getHeight(){
	return this->height;
}

float GameElement::getMass(){
	return this->mass;
}

int GameElement::getWidth(){
	return this->width;
}

std::pair<float,float> GameElement::getPosition(){
	return this->position;
}

void GameElement::setPosition(std::pair<float,float> p){
	this->position = p;
}

bool GameElement::hasChanged(){
	return this->changed;
}

float GameElement::getRadius()
{
	return this->radius;
}

float GameElement::getScale()
{
	return this->scale;
}

bool GameElement::isFixed()
{
	return this->fixed;
}