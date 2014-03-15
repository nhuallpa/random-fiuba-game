/*
 * Sprites.h
 *
 *  Created on: 15/09/2013
 *      Author: ALiguori
 */

#pragma once

#ifndef SPRITES_H_
#define SPRITES_H_

#include "Screen.h"
#include <list>
#include <string>
#include <map>


/*
 *
 */
class Sprites {
private:
	int sWidth;
	int sHeigth;
	static Sprites *instance;
	std::map<int,Textures*> sTexturesMap;


public:

	static Sprites *getInstance();
	virtual ~Sprites();

	void addSprite(int type, std::string spritePath);
	Textures* getSprite(int type);
	std::map<int,Textures*>* getSpriteMap();


};

#endif /* SPRITES_H_ */
