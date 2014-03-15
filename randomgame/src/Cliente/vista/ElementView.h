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
	ElementView(int type, int posX, int posY, float degree,Textures* aTexture);
	ElementView(ElementView *e);
	virtual ~ElementView();
	void render();
	int getPosX();
	int getPosY();
	int getAngle();
	void setPosX(int x);
	void setPosY(int y);
	void setAngle(float degree);
	int getType();
	void setWidth(float w);
	void setHeiht(float h);
	float getWidth();
	float getHeight();

	bool operator==(const ElementView& e)const;

private:
	int posX;
	int posY;
	float degree;
	int shapeType;
	Textures* eTexture;
	float width;
	float height;


};

#endif /* ELEMENTVIEW_H_ */
