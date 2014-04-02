#include <iostream>
#include "ContourBmp.h"

using namespace std;


void showComponents(list< list<Position*> *>* connectedComponents, int height, int width)
{
    list< list<Position*> *>::iterator itComponent= connectedComponents->begin();
    int numeroDeComponente=1;


    while(itComponent != connectedComponents->end())
    {
		cout<<endl;
		cout<<endl;
		cout<<"**************************"<<endl;
        cout<<"Contorno de la Componente " << numeroDeComponente<<endl;
		cout<<endl;
        list<Position*> *aConnectedComponent =*itComponent;
        aConnectedComponent->sort(Position::lessPosX);

        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {

                if((*itComponent)->size() >0)
                {
                    Position* aWhitePosition = new Position(i,j);
                    if((*aWhitePosition)==(*itComponent)->front() )
                    {
                        cout<<"0";
                        (*itComponent)->pop_front();
                    }
                    else
                    {
                        cout<<"1";
                    }
                    delete aWhitePosition;
                }
                else
                {
                    cout<<"1";
                }
            }
            cout<<endl;
        }

        itComponent++;

        numeroDeComponente++;
        cout<<endl;
    }

}

int main()
{
    Bmp* aBmpFile = new Bmp("C:\\random-fiuba-game\\randomgame\\libs\\Bmp\\test1.bmp");
    ContourBmp* aContourBmp = new ContourBmp(aBmpFile);

    list< list<Position*> *>* connectedComponents =aContourBmp->getContour();

	//Mostrar por consola el Bitmap y el contorno de las componentes
	//aBmpFile->showBitmap();
	//showComponents(connectedComponents, aBmpFile->getHeight(), aBmpFile->getWidth());

	delete aContourBmp;

	//
	// do stuff with connectedComponents
	//

	ContourBmp::deleteListOfListPositions(connectedComponents);

    cout << "Neo: \"I'm in\" " << endl;
	getchar();
    return 0;
}



