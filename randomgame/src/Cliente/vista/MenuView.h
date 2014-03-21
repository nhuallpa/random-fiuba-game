/*
 * MenuView.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#ifndef MENUVIEW_H_
#define MENUVIEW_H_
#include "Screen.h"
#include <map>




/*
 *
 */
class MenuView {


public:
	void render();
	void moveUp();
	void moveDown();
	void init();
	int getOffset();

private:
	std::map<int,Textures*> trMap;
	int offset;



};

#endif /* MENUVIEW_H_ */
