/*
 * GameElement.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "GameElement.h"


GameElement::GameElement(ElementType type, float posX, float posY, int degrees){
	
	switch (type){
	case SQUARE:

		break;
	case CIRCLE:

		break;
	}
	this->type = type;
	this->degrees = degrees;
	this->position = std::make_pair(posX,posY);
}

int GameElement::getType(){
	return this->type;
}

int GameElement::getRotation(){
	return this->degrees;
}


std::pair<float,float> GameElement::getPosition(){
	return this->position;
}

void GameElement::setPosition(std::pair<float,float> p){
	this->position = p;
}
