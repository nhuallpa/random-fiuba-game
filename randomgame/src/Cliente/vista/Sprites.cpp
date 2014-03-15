/*
 * Sprites.cpp
 *
 *  Created on: 15/09/2013
 *      Author: ALiguori
 */

#include "Sprites.h"

Sprites *Sprites::instance = NULL;

Sprites::~Sprites() {
	// TODO Auto-generated destructor stub
	std::cout << "destroyed" << std::endl;
}

Sprites *Sprites::getInstance() {
if(instance == NULL)
    instance = new Sprites();

return instance;
}


void Sprites::addSprite(int type, std::string sPath){
	this->sTexturesMap[type] = new Textures();
	this->sTexturesMap[type]->setRenderer(Screen::getInstance()->getRenderer());
	if( !this->sTexturesMap[type]->loadFromFile(sPath) )
	{
		std::cout << "Failed to load sprite texture!\n" << std::endl;
	}
}

Textures* Sprites::getSprite(int type){
	//std::cout << "sprite renderer: " << this->sTexturesMap[type].getRenderer() << std::endl;
	return this->sTexturesMap[type];
}

std::map<int,Textures*>* Sprites::getSpriteMap(){
	return &this->sTexturesMap;
}



