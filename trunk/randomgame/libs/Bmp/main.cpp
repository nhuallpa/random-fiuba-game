#include <iostream>
#include "ContourBmp.h"

using namespace std;


void showComponents(list< list<Position*> *>* connectedComponents)
{
    Bmp* aBmpFile= new Bmp("Untitled.bmp");
    list< list<Position*> *>::iterator itComponent= connectedComponents->begin();
    int numeroDeComponente=1;


    while(itComponent != connectedComponents->end())
    {
        cout<<"numero de componente:" << numeroDeComponente<<endl;
        list<Position*> *aConnectedComponent =*itComponent;
            cout<<"Tamanio del contorno cuando entra a mostrarse: "<<aConnectedComponent->size()<<endl;

        aConnectedComponent->sort(Position::lessPosX);

        for(int i=0; i<aBmpFile->getHeight(); i++)
        {
            for(int j=0; j<aBmpFile->getWidth(); j++)
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
    Bmp* aBmpFile = new Bmp("test1.bmp");
    ContourBmp* aContourBmp = new ContourBmp(aBmpFile);
    list< list<Position*> *>* connectedComponents =aContourBmp->getContour();
    //showComponents(connectedComponents);
	delete aContourBmp;

	//
	// do stuff with connectedComponents
	//

	ContourBmp::deleteListOfListPositions(connectedComponents);

    cout << "Neo: \"I'm in\" " << endl;
	getchar();
    return 0;
}



