#ifndef CONTOURBMP_H
#define CONTOURBMP_H

#include "Bmp.h"

class ContourBmp
{
    public:
        ContourBmp(Bmp* aBmpFile);
        list< list<Position*> *>* getConnectedComponents(list<Position*>* aPositionList);
        list< list<Position*> *>* getContour();
        static void deleteListOfListPositions(list< list<Position*>* >* aListOfListToDelete);
        virtual ~ContourBmp();
    protected:
    private:
        Bmp* aBmpFile;
        int getSquareValue(int pX, int pY);
        list<Position*> * getContour(list<Position*> * aConnectedComponent);
};

#endif // CONTOURBMP_H
