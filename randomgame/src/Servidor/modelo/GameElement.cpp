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

std::list<std::pair<float,float>> GameElement::getVertex(){


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