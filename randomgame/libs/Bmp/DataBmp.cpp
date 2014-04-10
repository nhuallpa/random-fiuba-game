#include "DataBmp.h"
#include <iostream>
#include "Position.h"

//El constructor de la clase recibe:
//data: el bloque de datos del archivo bmp Pre:el tamanio debe ser de minimo width*3*row_padded
//row_padded: el tama�o de las filas guardadas en el bloque
//height y width sacada del archivo .bmp.
//Pos1: Instancia 3 listas a saber
// -whitePositions: contiene las posiciones blancas (bool=true=1) del bitmap (y las corregidas por ser de color)
// -blackPositions: contiene las posiciones negras (bool=false=0) del bitmap (y las corregidas por ser de color)
// -invalidPixels: contiene las posiciones que no son negras ni blancas del bitmap.
//Pos2: Instancia una matriz de bool, con valores false y luego carga los datos del bitmap en ella:
// -Pixels Blancos: bool=true=1
// -Pixels Negros: bool=false=0
DataBmp::DataBmp(unsigned char* data,int row_padded, int height,int width)
{
    this->height=height;
    this->width=width;
    whitePositions = new list<Position*> ();
    blackPositions = new list<Position*> ();
    invalidPixels = new list<PixelBmp*>();

    //Se inicializa el bitmap con bool de valor falso(apagado =black)
    bitmap = new vector<vector<bool>*>();
    vector<vector<bool>*>* row = bitmap;
    vector<bool>* column;
    for(int i=0; i<height; i++)
    {
        row->push_back(new vector<bool>());
       /* column=(*row)[i];
        for(int j=0; j<width; j++)
        {
            column->push_back(false);
        }*/

    }

    this->loadMatrix(data,row_padded,height,width);


}

//Pre:el tamanio de DATA debe ser de minimo width*3*row_padded
//Se lee la data con los bits de colores. Se sabe que la informacion esta organizada de la siguiente manera:
//++++++++++++++++
//+blue+green+red+ y esto ocupa 24 bits por p�xel. y a su vez, cada fila tiene un tamanio de row_padded bytes
//++++++++++++++++
//Todo bit blanco o negro se ingresa al atributo 'bitmap', y a las listas de color seg�n corresponda
//Si el bit es de color, se lo agrega a la lista de pixeles invalidos. Al final de la lectura de DATA se corrigen estos
//p�xeles en el bitmap y en las listas de p�xeles blancos y negros. (no se eliminan de la lista de invalidos)
/***Chequear que no queden "cuevas"***/
void DataBmp::loadMatrix(unsigned char* data,int row_padded, int height,int width)
{
    unsigned char tmp;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j+(row_padded*i)];
            data[j+(row_padded*i)] = data[j+(row_padded*i)+2];
            data[j+(row_padded*i)+2] = tmp;


            //carga de bits a la matriz
            int red=(int)data[j+(row_padded*i)];
            int green=(int)data[j +row_padded*i + 1];
            int blue=(int)data[j +row_padded*i + 2];
            unsigned int val=colorVal(red,green,blue);
            if(val==3) //tiene color
            {
                PixelBmp* aInvalidPixel = new PixelBmp(new Position(height-1-i,j/3), new ColorRgb(red,green,blue,255));
                invalidPixels->push_back(aInvalidPixel);
				(*bitmap)[height-1-i]->push_back(false);
				///***********************
				//Avisar en el log el color encontrado
            }
            else //blanco o negro
            {
					if( (val==1) || (posValid(height-i, j/3) && getBit(height-i,j/3)==true) )//Si el bit debajo es blanco, pongo un blanco
					{
					(*bitmap)[height-1-i]->push_back(true);
                    setWhitePosition(height-1-i,j/3);

					}else //negro
					{
					(*bitmap)[height-1-i]->push_back(false);
                    setBlackPosition(height-1-i,j/3);

					}
	
               //setBit(height-1-i,j/3,val);
            }
        }
    }
    //evaluar lista de bits invalidos
    resetInvalidPixels();
}

//Resuelve los p�xels de color
void DataBmp::resetInvalidPixels()
{
    list<PixelBmp*>* aPixelList = this->getInvalidPixels();
    list<PixelBmp*>::iterator itPixels = aPixelList->begin();

    while(itPixels != aPixelList->end())
    {
        int posXInvalido=(*itPixels)->getPosition()->getX();
        int posYInvalido=(*itPixels)->getPosition()->getY();

        if(posXInvalido == 0) //borde superior pongo color blanco
        {
            setBit(posXInvalido,posYInvalido,1); //blanco
            setWhitePosition(posXInvalido,posYInvalido);
        }
        else //if(posXInvalido == this->height-1) //en el medio pongo el mismo que el de arriba
        {
            bool val=getBit(posXInvalido-1,posYInvalido);
            if(val)
            {
                setWhitePosition(posXInvalido,posYInvalido);
            }
            else
            {
                setBlackPosition(posXInvalido,posYInvalido);
            }
            setBit(posXInvalido,posYInvalido,val);
        }/*
        else
        {
            setBit(posXInvalido,posYInvalido,getBit(posXInvalido-1,posYInvalido)); //pongo el mismo que el de arriba
        }*/
        itPixels++;
    }
    this->deletePixelList(aPixelList);
}


//Pos:
// return 0:black
// return 1:white
// return 3:color
unsigned int DataBmp::colorVal(int red, int green, int blue)
{
    if(red==0 && green==0 && blue==0)
    {
        return 0;
    }
    else if(red==255 && green==255 && blue==255)
    {
        return 1;
    }
    else
    {
        return 3;
    }
}

//Devuelve una copia de la lista de posiciones blancas ordenada por filas. Se debe liberar la memoria despues de utilizar la lista
list<Position*>* DataBmp::getWhitePositions()
{
    list<Position*>* aWhitePositionsList = new list<Position*>();
    whitePositions->sort(Position::lessPosX);
    list<Position*>::iterator itList = whitePositions->begin();

    while(itList != whitePositions->end())
    {
        Position* aPositionToCopy = *itList;
        Position* newPosition = new Position(aPositionToCopy->getX(), aPositionToCopy->getY() );
        aWhitePositionsList->push_back(newPosition);
        itList++;
    }
    return aWhitePositionsList;
}

//Devuelve una copia de la lista de posiciones negras ordenada por filas. Se debe liberar la memoria despues de utilizar la lista
list<Position*>* DataBmp::getBlackPositions()
{
    list<Position*>* aBlackPositionsList = new list<Position*>();
    blackPositions->sort(Position::lessPosY);
    list<Position*>::iterator itList = blackPositions->begin();

    while(itList != blackPositions->end())
    {
        Position* aPositionToCopy = *itList;
        Position* newPosition = new Position(aPositionToCopy->getX(), aPositionToCopy->getY() );
        aBlackPositionsList->push_back(newPosition);
        itList++;
    }
    return aBlackPositionsList;
}

//Devuelve una copia de la lista de P�xels invalidos ordenada por columnas. Se debe liberar la memoria despues de utilizar la lista
list<PixelBmp*>* DataBmp::getInvalidPixels()
{
    list<PixelBmp*>* aPixelList = new list<PixelBmp*>();
    invalidPixels->sort(PixelBmp::lessPosY);
    list<PixelBmp*>::iterator itPixel = invalidPixels->begin();

    while(itPixel != invalidPixels->end())
    {
        PixelBmp* aPixelToCopy = *itPixel;
        Position* aPositionToCopy =aPixelToCopy->getPosition();
        ColorBmp* aColorToCopy =aPixelToCopy->getColor();
        PixelBmp* newPixel = new PixelBmp(new Position(aPositionToCopy), new ColorBmp(aColorToCopy) );
        aPixelList->push_back(newPixel);
        itPixel++;
    }
    return aPixelList;
}

//Se instancia y se agrega una nueva posicion en la lista de posiciones blancas
void DataBmp::setWhitePosition(int posX,int posY)
{
    Position* aPosition = new Position(posX,posY);
    this->whitePositions->push_back(aPosition);
}

//Se instancia y se agrega una nueva posicion en la lista de posiciones negras
void DataBmp::setBlackPosition(int posX,int posY)
{
    Position* aPosition = new Position(posX,posY);
    this->blackPositions->push_back(aPosition);
}

//Pos: Se devuelve "False" en caso que las posiciones esten fuera del rango width y height
bool DataBmp::setBit(int posX, int posY, bool color)
{
    if(posValid(posX,posY))
    {
        vector<vector<bool>*>* fila = bitmap;
        vector<bool>* columna =(*fila)[posX];
        (*columna).at(posY)=color;
        return true;
    }
    else
    {
        return false;
    }
}

//Pre: las posiciones deben ser validas (no fuera del rango de ancho y alto del bitmap)
bool DataBmp::getBit(int posX, int posY)
{
    vector<vector<bool>*>* fila = bitmap;
    vector<bool>* columna =(*fila)[posX];
    return (*columna).at(posY);
}

int DataBmp::getHeight()
{
    return this->height;
}

int DataBmp::getWidth()
{
    return this->width;
}

//Chequea que los valores se encuentren dentro del alto y ancho del bitmap
bool DataBmp::posValid(int posX, int posY)
{
    return (posX>=0 && posX<height && posY>=0 && posY<width);
}

//Libera la memoria dentro de un vector de vectores bool
void DataBmp::deleteMatrix(vector<vector<bool>*>* aBitmap)
{
    vector<vector<bool>*>* row = aBitmap;

    for(int i=0; i<this->height; i++)
    {
        vector<bool>* rowToDel = (*row)[i];
        delete rowToDel;
    }

    delete aBitmap;
}

//Libera la memoria de una lista de posiciones
void DataBmp::deletePositionList(list<Position*> * aListToDelete)
{
    list<Position*>::iterator itList = aListToDelete->begin();

    while(itList != aListToDelete->end())
    {
        Position* aPositionToDelete = *itList;
        delete aPositionToDelete;
        itList++;
    }
    delete aListToDelete;
}

//Libera la memoria de una lista de P�xeles, liberando as� las posiciones y los colores del P�xel
void DataBmp::deletePixelList(list<PixelBmp*> * aListToDelete)
{
    list<PixelBmp*>::iterator itList = aListToDelete->begin();

    while(itList != aListToDelete->end())
    {
        PixelBmp* aPixelToDelete = *itList;
        delete aPixelToDelete;
        itList++;
    }
    delete aListToDelete;
}

//Muestra el valor del bitmap
//0:Black
//1:White
void DataBmp::showBitmap()
{
		cout<<endl;
		cout<<endl;
		cout<<"***********"<<endl;
        cout<<"Archivo BMP" <<endl;
		cout<<endl;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            cout<<getBit(i,j);
        }
        cout<<endl;
    }
}

DataBmp::~DataBmp()
{
    deleteMatrix(bitmap);
    deletePixelList(invalidPixels);
    deletePositionList(whitePositions);
    deletePositionList(blackPositions);
}