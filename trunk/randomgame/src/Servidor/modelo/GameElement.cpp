#include "GameElement.h"


GameElement::GameElement(ElementType type, float posX, float posY, int degrees, int h, int w, float mass){
	
	this->type = type;
	this->degrees = degrees;
	this->position = std::make_pair(posX,posY);
	this->height = h;
	this->width = w;
	this->mass = mass;
}


void getVertex(){
	
}

int GameElement::getType(){
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
