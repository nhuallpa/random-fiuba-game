#include "HandleContour.h"
#include <cmath>

#define SEGMENT 2
using namespace server_model_handle;

HandleContour::HandleContour(){}
HandleContour::~HandleContour(){}
list<Point*> HandleContour::rdp(list<Point*> contour, int epsilon){
	list<Point*>::iterator it;
	Point* firstPoint = (*contour.begin());
	Point* lastPoint = (*contour.end());
	Point* splitPoint = NULL;
	float distance = 0.0;
	float aux = 0.0;
	list<Point*> contourRDP;
	list<Point*> contour1;
	list<Point*> contour2;
	list<Point*> contour3;
	list<Point*> contour4;

	if(contour.size() <= SEGMENT){
		return contour;
	}

	for(it = ++(contour.begin());
		it != --(contour.end());
		it++){
		aux = findPerpendicularDistance((*it),firstPoint,lastPoint);
		if(aux > distance){
			distance = aux;
			splitPoint = (*it);
		}
	}

	if(distance > epsilon){
		for(it = contour.begin();
			it != contour.end();
			it++){
				if((*it) <= splitPoint){
					contour1.push_back((*it));
				}
				if((*it) >= splitPoint){
					contour2.push_back((*it));
				}
		}
		contour3 = this->rdp(contour1, epsilon);
		contour4 = this->rdp(contour2, epsilon);
		contourRDP.insert(contourRDP.end(),
			              contour3.begin(),
						  --(contour3.end()));
		contourRDP.splice(contourRDP.end(), contour4);
		return contourRDP;
	}
	else{
		contourRDP.push_back(firstPoint);
		contourRDP.push_back(lastPoint);
		return contourRDP;
	}
	return contour;
}

float HandleContour::findPerpendicularDistance(Point* p, Point* p1, Point* p2){
	float slope = 0.0;
	float intercept = 0.0;
	float result = 0.0;

	if(p1->getX() == p2->getX()){
		return abs(p->getX() - p1->getX());
	}
	else{
		slope = (p2->getY() - p1->getY()) / (p2->getX() - p1->getX());
		intercept = p1->getY() - (slope * p1->getX());
		result = abs(slope * p->getX() - p->getY() + intercept) 
				/ sqrt(pow(slope, 2) + 1);
	}
	return result;
}
