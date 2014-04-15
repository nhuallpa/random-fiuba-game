#include "Bmp.h"


Bmp::Bmp(char* path)
{    int width;
    int height;
    int row_padded;
    unsigned char* data;

 if(validarArchivo(path))
 {
	   // obtain file size:
  fseek (fileBmp , 0 , SEEK_END);
  long lSize = ftell (fileBmp);
  rewind (fileBmp);


    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, fileBmp); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];
    row_padded = (width*3 + 3) & (~3);
    data = new unsigned char[width*3*row_padded];

    fread(data, sizeof(unsigned char), row_padded*height, fileBmp);
    fclose(fileBmp);
	    aDataBmp = new DataBmp(data,row_padded,height,width);
 }else
 {
	 aDataBmp=NULL;

		 try
  {
    throw 20;
  }
  catch (int e)
  {
    throw 20;
  }


 }





}

bool Bmp::validarArchivo(char* path)
{
	fileBmp = fopen(path, "rb");
	if (fileBmp==NULL)
	{ 
		Log::e("Class Bmp.cpp: No existe el archivo. Se cargará un bmp por default");
		return false;
	}
	else if (!esUnBmp(path))
	{
		Log::e("Class Bmp.cpp: La extensión del archivo no es válida. Se cargará un bmp por default");
		return false;

	}
	return true;
}


bool Bmp::esUnBmp(char* path)
{
	int longitudPath= strlen(path);
	bool valido= 
		(path[longitudPath-4]=='.' &&
		path[longitudPath-3]=='b' &&
		path[longitudPath-2]=='m' &&
		path[longitudPath-1]=='p');
	return valido;
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
