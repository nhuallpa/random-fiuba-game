#ifndef WORM_H_
#define WORM_H_

#include "../GameElement.h"
#include "../Physics/Bodies/Worm/Worm2d.h"

using namespace std;

class Worm : public GameElement{

protected:
int life;
bool jumping;
bool jumpingRight;
bool jumpingLeft;
bool movingRight;
bool movingLeft;
bool selected;
bool stopped;
bool alive;


public:
	Worm();
//Worm(int id, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed);
Worm(int id, std::string playerID, ElementType type, float posX, float posY, float degrees, float h, float w, float mass, bool isFixed);
int getLife();
void setLife(int newLife);
void addLife(int moreLife);
void subLife(int lessLife);
void setAlive(bool b){ this->alive = b;}

void stop();
void jump();
void jumpRight();
void jumpLeft();
void moveLeft();
void moveRight();
void stopMoving();

bool isSelected();
bool isJumping();
bool isJumpingRight(){ return this->jumpingRight; }
bool isJumpingLeft(){ return this->jumpingLeft; }
bool isMovingRight();
bool isMovingLeft();
bool isStopped();
bool isAlive() { return this->alive;}



void select();
void deselect();
virtual ~Worm();



};


#endif
