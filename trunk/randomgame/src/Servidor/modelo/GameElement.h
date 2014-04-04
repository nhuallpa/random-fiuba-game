/*
 * GameElement.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */
#pragma once

#ifndef GAMEELEMENT_H_
#define GAMEELEMENT_H_
#include "../../utils/ParserYaml.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <list>

/*
 *
 */

enum ElementType{
	SQUARE=0,
	CIRCLE=1,
	TRIANGLE=2,
	PENTA=3,
};


class GameElement {
public:
	GameElement(int id, ElementType type, float posX, float posY, int degrees, int h, int w, float mass);
	
	ElementType getType();
	int getId();
	int getRotation();
	std::pair<float,float> getPosition();
	void setPosition(std::pair<float,float> p);
	int getWidth();
	int getHeight();
	float getMass();
	bool hasChanged();
	void setBody(void* ab);
	std::list<std::pair<float,float>> getVertex();
	void setVertexList(std::list<std::pair<float,float>> l);


private:
	int id;
	bool changed;
	float ratio;
	ElementType type;
	int degrees;
	int height;
	int width;
	float mass;
	void* myBody;
	// Center position!
	std::pair<float,float> position;
	std::list<std::pair<float,float>> vertexList;
};

#endif /* GAMEELEMENT_H_ */
