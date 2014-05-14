
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
	HEXAGON=4,
	WORM=5,
};


class GameElement {
public:
	GameElement();
	/* Constructor for Rectangule */
	GameElement(int id, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed);
	GameElement(int id, std::string playerID, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed);


	/* Constructor for Circle */
	GameElement(int id, float posX, float posY, float radius, float scale, float mass, bool isFixed);

	/* Constructor for any other polygon */
	GameElement(int id, ElementType type, float posX, float posY, float scale, float degrees, float mass, bool isFixed);

	/* Constructor for Copy */
	GameElement(const GameElement & aGameElement);
	
	ElementType getType();
	bool changed;
	void setChanged(bool b){ this->changed = b;}
	int getId();
	float getRotation();
	std::pair<float,float> getPosition();
	void setPosition(std::pair<float,float> p);
	float getWidth();
	float getHeight();
	float getMass();
	bool hasChanged();
	void setBody(void* ab);
	void setAngle(float angle);
	std::list<std::pair<float,float>> & getVertex();
	void setVertexList(std::list<std::pair<float,float>> l);
	float getRadius();
	float getScale();
	bool isFixed();

	float getRadiusScaled() {return radius * scale;}

	std::string playerID;

	std::string getPlayerID() {return this->playerID; }

	bool isGrounded(){ return this->grounded; }
	void setGrounded(bool b){ this->grounded = b; }

protected:
	int id;
	
	float ratio;
	ElementType type;
	float degrees;
	float height;
	float width;
	float mass;
	void* myBody;
	// Center position!
	std::pair<float,float> position;
	std::list<std::pair<float,float>> vertexList;
	bool grounded;
	/** Used for circule */
	float radius;

	/** The scale factor */
	float scale;

	/** True if the element is static */
	bool fixed;
};

#endif /* GAMEELEMENT_H_ */
