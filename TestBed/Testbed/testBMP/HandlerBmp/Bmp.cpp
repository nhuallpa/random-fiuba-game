#include "Bmp.h"


Bmp::Bmp(char* path)
{
    fileBmp = fopen(path, "rb");
  if (fileBmp==NULL) {

	/* Cargar el archivo por default
	//fileBmp = fopen(pathDefault, "rb");
		if (fileBmp==NULL) //Si el archivo por default tambien es erroneo, sale.
		{
			fputs ("Default Bmp File Error",stderr); exit (1);
		}
	*/
	  fputs ("File error",stderr); exit (1);
  }

  // obtain file size:
  fseek (fileBmp , 0 , SEEK_END);
  long lSize = ftell (fileBmp);
  rewind (fileBmp);


    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, fileBmp); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[width*3*row_padded];

    fread(data, sizeof(unsigned char), row_padded*height, fileBmp);
    fclose(fileBmp);

    aDataBmp = new DataBmp(data,row_padded,height,width);
}

Bmp::~Bmp()
{
    delete aDataBmp;
}

bool Bmp::getBit(int posX, int posY)
{
    return aDataBmp->getBit(posX,posY);
}
list<Position*>* Bmp::getBlackPositions()
{
    return aDataBmp->getBlackPositions();
}

bool Bmp::posValid(int posX, int posY)
{
    return aDataBmp->posValid(posX,posY);
}
int Bmp::getHeight()
{
return aDataBmp->getHeight();
}

int Bmp::getWidth()
{
    return aDataBmp->getWidth();
}

void Bmp::showBitmap()
{
    this->aDataBmp->showBitmap();
}