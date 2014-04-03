#include "HandleContour.h"
#include <cmath>

#define SEGMENT 2
using namespace server_model_handle;

HandleContour::HandleContour(){}
HandleContour::~HandleContour(){}
list<b2Vec2*> HandleContour::rdp(list<b2Vec2*> contour, int epsilon){
	list<b2Vec2*>::iterator it;
	b2Vec2* firstPoint = (*contour.begin());
	b2Vec2* lastPoint = (*(--contour.end()));
	b2Vec2* splitPoint = NULL;
	float distance, aux = 0.0;
	list<b2Vec2*> contourRDP;
	list<b2Vec2*> contour1, contour2, 
		         contour3, contour4;

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

float HandleContour::findPerpendicularDistance(b2Vec2* p, b2Vec2* p1, b2Vec2* p2){
	float slope = 0.0;
	float intercept = 0.0;
	float result = 0.0;

	if(p1->x == p2->x){
		return abs(p->x - p1->x);
	}
	else{
		slope = (p2->y - p1->y) / (p2->x - p1->x);
		intercept = p1->y - (slope * p1->x);
		result = abs(slope * p->x - p->y + intercept) 
				/ sqrt(pow(slope, 2) + 1);
	}
	return result;
}



