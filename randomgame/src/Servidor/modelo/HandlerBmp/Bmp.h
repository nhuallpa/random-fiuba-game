#ifndef BMP_H
#define BMP_H

#include <list>
#include "DataBmp.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Bmp
{
private:

    FILE* fileBmp;
	DataBmp* aDataBmp;

public:
    Bmp(char* path);
	bool getBit(int posX, int posY);
	void showBitmap();
	int getHeight();
	int getWidth();
	bool posValid(int posX, int posY);
	list<Position*>* getBlackPositions();
    ~Bmp();
};
#endif
