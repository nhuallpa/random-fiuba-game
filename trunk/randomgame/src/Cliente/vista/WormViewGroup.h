#pragma once

#ifndef __FIGURE_VIEW_GROUP_H__
#define __FIGURE_VIEW_GROUP_H__
#include <list>
#include "WormView.h"
class WormViewGroup : public View
{
private:
	std::map<int, WormView*> mapWorms;

	std::list<WormView*> views;

public:
	WormViewGroup(int x, int y);

	/**
	* Find a figure view by id
	* @return aFigureView 
	*/
	WormView* findById(int idElement);

	/**
	* Add a view
	*/
	void add(WormView* aView);

	/**
	* Clean every view
	*/
	void clean();
	
	/**
	* Update every wormView
	*/
	void update();

	/**
	* Draw each view
	*/
	void draw(SDLScreen & screen);

	~WormViewGroup(void);
};


#endif /** __FIGURE_VIEW_GROUP_H__ */