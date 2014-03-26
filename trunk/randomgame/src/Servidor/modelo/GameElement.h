/*
 * GameElement.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */
#pragma once

#ifndef GAMEELEMENT_H_
#define GAMEELEMENT_H_
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <list>

/*
 *
 */

enum ElementType{
	SQUARE = 0,
	CIRCLE =1,
};


class GameElement {
public:
	GameElement(ElementType type, float posX, float posY, int degrees);
	
	int getType();
	int getRotation();
	std::pair<float,float> getPosition();
	void setPosition(std::pair<float,float> p);

private:
	int type;
	int degrees;
	std::pair<float,float> position;
};

#endif /* GAMEELEMENT_H_ */
