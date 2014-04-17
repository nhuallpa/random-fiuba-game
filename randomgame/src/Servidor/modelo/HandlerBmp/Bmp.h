#ifndef BMP_H
#define BMP_H


#include "DataBmp.h"
#include "DataBmp24.h"
#include "DataBmp32.h"
#include "../../../utils/Log.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Bmp
{
protected:
	FILE* fileBmp;
	DataBmp* aDataBmp;
	bool validarArchivo(char* path);
	bool esUnBmp(char* path);
	void cargaDeDatosBmp24();

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
