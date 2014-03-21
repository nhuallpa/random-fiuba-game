/*
 * ElementView.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */
#pragma once

#ifndef ELEMENTVIEW_H_
#define ELEMENTVIEW_H_

#include <map>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Textures.h"
#include "Screen.h"
/*
 *
 */
class ElementView {
public:
	ElementView(int type, float posX, float posY, float degree,Textures* aTexture);
	ElementView(ElementView *e);
	virtual ~ElementView();
	void render();
	float getPosX();
	float getPosY();
	float getAngle();
	void setPosX(float x);
	void setPosY(float y);
	void setAngle(float degree);
	int getType();
	void setWidth(float w);
	void setHeiht(float h);
	float getWidth();
	float getHeight();

	bool operator==(const ElementView& e)const;

private:
	float posX;
	float posY;
	float degree;
	int shapeType;
	Textures* eTexture;
	float width;
	float height;


};

#endif /* ELEMENTVIEW_H_ */
