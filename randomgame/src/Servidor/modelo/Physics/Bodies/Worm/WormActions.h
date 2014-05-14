#ifndef WORMACTIONS_H_
#define WORMACTIONS_H_
#include "Worm2d.h"

using namespace std;

class Worm2d;
class WormActions{

protected:
Worm2d* aWorm2d;
float deltaMovement;

public:
WormActions(Worm2d* worm2d);
void jump();
void moveLeft();
void moveRight();
virtual ~WormActions();

};


#endif
