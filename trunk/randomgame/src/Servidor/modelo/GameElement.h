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
#include <list>

/*
 *
 */

enum ElementType
{
	CIRCLE = 0,
	SQUARE = 1,
	PENTAGON = 2,
	TRIANGLE = 3,
	TOTAL_ELEMS = 4
};

class GameElement {
public:
	GameElement(ElementType type, float posX, float posY, int degrees);
	void render();
	ElementType getType();
	int getRotation();
	std::pair<float,float> getPosition();
	void setPosition(std::pair<float,float> p);

private:
	ElementType type;
	int degrees;
	std::pair<float,float> position;
};

#endif /* GAMEELEMENT_H_ */
