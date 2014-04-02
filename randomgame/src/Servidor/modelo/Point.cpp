
#include "Point.h"
//#include <cmath>

using namespace server_model_point;


Point::Point(){ y = x = 0.0;}
Point::Point(float y, float x){this->x = x; this->y = y;}
Point::~Point(){}
float Point::getY(){ return y; }
float Point::getX(){ return x; }

