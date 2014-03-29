#pragma once
#ifndef __CIRCLE_VIEW_H_
#define __CIRCLE_VIEW_H_

#include "FigureView.h"
class CircleView : 	public FigureView
{
private:
	int radio;

	

public:
	CircleView(int x, int y, int radio, Uint32 color, int rotation);

	int getRadio() {return radio;}
	void setRadio(int radio) {this->radio = radio;}

	void draw(SDLScreen & screen);

	~CircleView(void);
};

#endif /** __CIRCLE_VIEW_H_ */

