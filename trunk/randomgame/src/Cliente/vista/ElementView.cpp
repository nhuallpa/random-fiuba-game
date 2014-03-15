/*
 * ElementView.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "ElementView.h"
#include "../../utils/Constantes/Constantes.h"


bool ElementView::operator==(const ElementView& e) const {
	if ( this->degree == e.degree &&  this->posX == e.posX && this->posY == e.posY && this->shapeType == e.shapeType && this->eTexture == e.eTexture){
		return true;
	}
	return false;

}

ElementView::ElementView(ElementView *e) {
	this->degree = e->degree;
	this->posX = e->posX;
	this->posY = e->posY;
	this->width = ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first;
	this->height = ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second;
	this->shapeType = e->shapeType;
	this->eTexture = e->eTexture;
}


ElementView::~ElementView() {
	// TODO - release texture
}

ElementView::ElementView(int type, int posX, int posY, float degree,Textures* aTexture){
	this->degree = degree;
	this->posX = posX;
	this->posY = posY;
	this->shapeType = type;
	this->eTexture = aTexture;
	this->width = ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first;
	this->height = ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second;
}

void ElementView::render(){
	this->eTexture->render(this->posX, this->posY, NULL, (double)this->degree, NULL, SDL_FLIP_NONE);
}


int ElementView::getPosX(){
	return this->posX;
}


int ElementView::getPosY(){
	return this->posY;
}

int ElementView::getAngle(){
	return this->degree;
}

void ElementView::setPosX(int x){
	this->posX = x;
}


void ElementView::setPosY(int y){
	this->posY = y;
}


void ElementView::setAngle(float degree){
	this->degree = degree;
}


int ElementView::getType(){
	return this->shapeType;
}

void ElementView::setWidth(float w){
	this->width = w;
}

void ElementView::setHeiht(float h){
	this->height = h;
}

float ElementView::getWidth(){
	return this->width;
}

float ElementView::getHeight(){
	return this->height;
}





