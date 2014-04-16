#include "ContourBmp.h"

ContourBmp::ContourBmp(Bmp* aBmpFile)
{
    this->aBmpFile=aBmpFile;
}

//Pre: sólo funciona con la premisa que las posiciones terminan siempre en el mismo x.
//Pos1:Devuelve una lista dentro de la cual, cada elemento es una lista.
//Esta última lista contiene posiciones adyacentes.(una vez usados deben ser liberados de memoria)
//Pos2: Realiza el 'delete' de la lista pasada por parámetro.(solo la lista, sus elementos no)
list< list<Position*>* >* ContourBmp::getConnectedComponents(list<Position*>* aPositionList)
{
    //Se ordena por columna de menor a mayor, así se recorren las posiciones de arriba a abajo de izq a der
    list< list<Position*>* >* aConnectedComponentsList = new list< list<Position*>* >();
    int actualColumn=-2;
    list<Position*>* aComponent;

    list<Position*>::iterator itPos=aPositionList->begin();
    while(itPos != aPositionList->end())
    {

        Position* aPosition=*itPos;

        //Si la posicion corresponde a la columna de la posicion anterior o a la siguiente columna
        //entonces pertenece a la misma componente
        if( (aPosition->getY() == actualColumn) || (aPosition->getY() == actualColumn+1) )
        {
            actualColumn=aPosition->getY();
            aComponent->push_back(new Position(aPosition));
        }
        else
        {
            actualColumn=aPosition->getY();
            aComponent = new list<Position*>();
            aComponent->push_back(new Position(aPosition));
            aConnectedComponentsList->push_back(aComponent);
        }
        itPos++;
    }
    DataBmp::deletePositionList(aPositionList);
    return aConnectedComponentsList;
}


//Pos1:Devuelve una lista dentro de la cual, cada elemento es una lista.(Liberar la memoria utilizada por este recurso)
//Esta última lista contiene el contorno de una componente conexa.(una vez usados deben ser liberados de memoria)
//Pos2: Realiza el 'delete' de la lista pasada por parámetro y las posiciones dentro de esta lista.
list< list<Position*> *>* ContourBmp::getContour()
{
    list< list<Position*>* >* contours = new list< list<Position*>* >();
    list< list<Position*>* >* connectedComponents = this->getConnectedComponents(aBmpFile->getBlackPositions());
    list< list<Position*> *>::iterator itComponent= connectedComponents->begin();
    while(itComponent != connectedComponents->end())
    {
        list<Position*> *aConnectedComponent =*itComponent;
        contours->push_back(getContour(aConnectedComponent));
        itComponent++;
    }
    deleteListOfListPositions(connectedComponents);
    return contours;
}

//Devuelve el contorno de una componente conexa.
//Libera de memoria las posiciones que no conforman el contorno
list<Position*> * ContourBmp::getContour(list<Position*> * aConnectedComponent)
{
    list<Position*> * aContour= new list<Position*>();
    list<Position*>::iterator itPos= aConnectedComponent->begin();
    //agrego la base

    Position* aPos = (*itPos);
    int startX=aBmpFile->getHeight()-1;
    int startY=aPos->getY();
    int pX=startX;
    int pY=startY;

    int posXcontour;
    int posYcontour;

    int posPrevXcontour=-1;
    int posPrevYcontour=-1;

    int stepX;
    int stepY;

    int prevX;
    int prevY;

    bool closedLoop=false;
    while(!closedLoop)
    {


        // the core of the script is getting the 2x2 square value of each pixel
        int squareValue=getSquareValue(pX,pY);
        //cout<<"squarevalue: ";
        //cout<<squareValue<<endl;
        switch (squareValue)
        {


            /* fin

            +---+---+
            |   | 2 |
            +---+---+
            |   |   |
            +---+---+

            */
        case 2 :
            posXcontour=posPrevXcontour;
            posYcontour=posPrevYcontour;
            closedLoop=true;
            break;




            /* going UP with these cases:

            +---+---+
            |   | 2 |
            +---+---+
            |   | 8 |
            +---+---+

            */
        case 10 :
            posXcontour=pX;
            posYcontour=pY;
            stepX=-1;
            stepY=0;
            break;

            /* going DOWN with these cases:

            +---+---+   +---+---+
            |   |   |   | 1 |   |
            +---+---+   +---+---+
            | 4 |   |   | 4 |   |
            +---+---+  	+---+---+

            */
        case 4 :
            posXcontour=pX;
            posYcontour=pY-1;
            stepX=1;
            stepY=0;
            break;
        case 5 :
            posXcontour=pX;
            posYcontour=pY-1;
            stepX=1;
            stepY=0;
            break;

            /* going LEFT with these cases:

            +---+---+   +---+---+
            | 1 |   |   | 1 | 2 |
            +---+---+   +---+---+
            |   |   |   |   |   |
            +---+---+  	+---+---+

            */
        case 1 :
            posXcontour=pX-1;
            posYcontour=pY-1;
            stepX=0;
            stepY=-1;
            break;
        case 3 :
            posXcontour=pX-1;
            posYcontour=pY;
            stepX=0;
            stepY=-1;
            break;

            /* going RIGHT with these cases:

            +---+---+   +---+---+
            |   |   |   | 1 |   |
            +---+---+   +---+---+
            | 4 | 8 |   | 4 | 8 |
            +---+---+  	+---+---+

            */
        case 12 :
            posXcontour=pX;
            posYcontour=pY;
            stepX=0;
            stepY=1;
            break;

        case 13 :
            posXcontour=pX;
            posYcontour=pY;
            stepX=0;
            stepY=1;
            break;

        case 8 :
            /* special saddle point case 1:

            +---+---+
            |   |   |
            +---+---+
            |   | 8 |
            +---+---+

            go Right if there is 'Right'
            else get back DOWN

            */
            if (this->aBmpFile->posValid(pX,pY+1) && aBmpFile->getBit(pX,pY+1) ==0)
            {
                posXcontour=pX;
                posYcontour=pY;
                stepX=0;
                stepY=1;
            }
            else//Si el sig no tiene nada, entonces se forma un pico y debe volver abajo ó abajo a la derecha
            {
                if (this->aBmpFile->posValid(pX+1,pY+1) && aBmpFile->getBit(pX+1,pY+1) ==0)
                {
                posXcontour=pX;
                posYcontour=pY;
                stepX=1;
                stepY=1;
                }else
                {
                posXcontour=pX;
                posYcontour=pY;
                stepX=2;
                stepY=1;
                }

            }
            break;

        case 14 :
            /* special saddle point case 2:

            	+---+---+
            	|   | 2 |
            	+---+---+
            	| 4 | 8 |
            	+---+---+

            	go Up, unless you come from Up, then you must go right

            	*/


			if (this->aBmpFile->posValid(pX-1,pY+1) && aBmpFile->getBit(pX-1,pY+1) ==0)
			{
				if (prevX==1&&prevY==0)
				{
					posXcontour=pX;
					posYcontour=pY;
					stepX=0;
					stepY=1;
				}
				else
				{
					posXcontour=pX;
					posYcontour=pY;
					stepX=-1;
					stepY=0;
				}

			}
			else//Si el sig no tiene nada, entonces se forma un pico y debe seguir corriendo el programa
			{
				posXcontour=pX;
				posYcontour=pY;
				stepX=0;
				stepY=1;
			}
			            break;

		}

        // saving contour point
		if(squareValue==13&& !( (prevX ==1) &&(prevY ==0)) )//y viene de arriba
        {
            aContour->push_back(new Position(posXcontour, posYcontour-1));
        }
        if( (posPrevXcontour != posXcontour) || (posPrevYcontour != posYcontour))
        {

            aContour->push_back(new Position(posXcontour, posYcontour));
        }


        posPrevXcontour = posXcontour;
        posPrevYcontour = posYcontour;
        pX+=stepX;
        pY+=stepY;
        prevX=stepX;
        prevY=stepY;
        // if we returned to the first point visited, the loop has finished
        if ((pX==startX) && (pY==startY))
            closedLoop=true;

    }
    return aContour;
}


int ContourBmp::getSquareValue(int pX, int pY)
{
    /*

    checking the 2x2 pixel grid, assigning these values to each pixel, if not transparent

    +---+---+
    | 1 | 2 |
    +---+---+
    | 4 | 8 | <- current pixel (pX,pY)
    +---+---+

    */

    int squareValue=0;
    // checking upper left pixel
    if (this->aBmpFile->posValid(pX-1,pY-1) && this->aBmpFile->getBit(pX-1,pY-1)==0)
    {
        squareValue+=1;
    }
    // checking upper pixel
    if (this->aBmpFile->posValid(pX-1,pY) && this->aBmpFile->getBit(pX-1,pY)==0)
    {
        squareValue+=2;
    }
    // checking left pixel
    if (this->aBmpFile->posValid(pX,pY-1) && this->aBmpFile->getBit(pX,pY-1)==0)
    {
        squareValue+=4;
    }
    // checking the pixel itself
    if (this->aBmpFile->posValid(pX,pY) && this->aBmpFile->getBit(pX,pY)==0)
    {
        squareValue+=8;
    }

    return squareValue;
}

void ContourBmp::deleteListOfListPositions(list< list<Position*>* >* aListOfListToDelete)
{
    list< list<Position*> *>::iterator itList= aListOfListToDelete->begin();
    while(itList != aListOfListToDelete->end())
    {
        list<Position*> *aListToDelete =*itList;
        DataBmp::deletePositionList(aListToDelete);
        itList++;
    }
    delete aListOfListToDelete;
}

ContourBmp::~ContourBmp()
{
    delete this->aBmpFile;
}
