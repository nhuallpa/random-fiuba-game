#pragma once
#ifndef __FIGURE_VIEW_H_
#define __FIGURE_VIEW_H_
#include "View.h"
#include "TextureManager.h"

class FigureView : 	public View
{
private:
	int mRotation;
public:
	int getRotation() {return mRotation;}
	void setRotation(int rotation) {mRotation = rotation;}
	FigureView(int x, int y, std::string  color, int rotation);
	~FigureView(void);


};

struct s_point{
	int x;
	int y;
};
typedef struct s_point tPoint;

#endif /* defined(__FIGURE_VIEW_H_) */

