#include "Bmp.h"


Bmp::Bmp(char* path)
{    int width;
    int height;
    int row_padded;
    unsigned char* data;

 if(false==true)//validarArchivo(path))
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
 }else
 {
	  width=10;
	 height=10;
     row_padded=10;
	 data=getDefaultBmp();

 }




    aDataBmp = new DataBmp(data,row_padded,height,width);
}

bool Bmp::validarArchivo(char* path)
{
	fileBmp = fopen(path, "rb");
	if (fileBmp==NULL)
	{ 
		Log::e("Class Bmp.cpp: No existe el archivo. Se cargará el archivo bmp por default");
		fileBmp = fopen("C:\\random-fiuba-game\\randomgame\\randomgame\\image\\testDefault.bmp", "rb");
	}
	else if (!esUnBmp(path))
	{
		Log::e("Class Bmp.cpp: La extensión del archivo no es válida. Se cargará el archivo bmp por default");
		//copiar archivo por default al path
		//Cargar el archivo por default
		fileBmp = fopen("C:\\random-fiuba-game\\randomgame\\randomgame\\image\\testDefault.bmp", "rb");
	}
	if (fileBmp==NULL) //Si el archivo por default tambien es erroneo, sale.
	{
		Log::e("Class Bmp.cpp: El archivo por default no existe. Se programará uno por default de 10x10");
		return false;
	}
	return true;
}

unsigned char* Bmp::getDefaultBmp()
{
	unsigned char* defaultBmp=new unsigned char[10*3*10];
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10*3; j += 3)
        {
		if(i>=0 && i<4 && j<3 && j>=27)
		{
			defaultBmp[j+10*i]=0;
			defaultBmp[j+10*i+1]=0;
			defaultBmp[j+10*i+2]=0;

		}else
		{
			defaultBmp[i]=(char)255;
			defaultBmp[i+1]=(char)255;
			defaultBmp[i+2]=(char)255;
		}
		}
	}
	return defaultBmp;


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
