
#include "Point.h"
#include <cmath>

using namespace server_model_point;


Point::Point(){ y = x = 0.0;}
Point::Point(double y, double x){this->x = x; this->y = y;}
Point::~Point(){}
double Point::distance(Point* p){
	return sqrt(p->diffY(y) + p->diffX(x));
}
double Point::diffY(double y){

	return 0.0;
}
double Point::diffX(double x){

	return 0.0;
}
