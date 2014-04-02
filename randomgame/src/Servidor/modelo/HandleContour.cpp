#include "HandleContour.h"
#include <cmath>

#define SEGMENT 2
using namespace server_model_handle;

HandleContour::HandleContour(){}
HandleContour::~HandleContour(){}
list<Point*> HandleContour::rdp(list<Point*> contour, int epsilon){
	list<Point*>::iterator it;
	Point* firstPoint = (*contour.begin());
	Point* lastPoint = (*(--contour.end()));
	Point* splitPoint = NULL;
	float distance, aux = 0.0;
	list<Point*> contourRDP;
	list<Point*> contour1, contour2, 
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
/*

int HandleContour::Validate(list<b2Vec2*> l){ 
	list<b2Vec2*>::iterator it, jt, it2, jt2, it3;
	int ret = 0;
	float d = 0.0;
	bool fl, fl2 = false;

	for(it = l.begin();
		it != l.end();
		it++){
			it2 = (it != --(l.end())) ? it2 = it, ++it2 : l.begin();
			it3 = (it != l.begin()) ? it3 = it, --it3 : --(l.end());
			fl= false;
			for(jt = l.begin();
				jt != l.end();
				jt++){
					if (((jt != it) && jt != it2)) {
						if(!fl){
							d = this->det((*it)->x, (*it)->y, 
								(*it2)->x, (*it2)->y,
								(*jt)->x, (*jt)->y
								);
							if(d > 0){ fl = true; }
						}
						if(jt != it3){
							jt2 = (jt != --(l.end())) ? jt2 = jt, ++jt2 : l.begin();
							if(this->hitSegment((*it)->x, (*it)->y,
												(*it2)->x, (*it2)->y,
												(*jt)->x, (*jt)->y,
												(*jt2)->x, (*jt2)->y	)){
								ret = 1;
							}
						}
					}
			}
			if (! fl) {
				fl2 = true;
            }
		}
        if (fl2) {
            if ((ret==1))
                ret=3;
            else 
                ret=2;
        }
	return ret; 
}

float HandleContour::det(float x1,float y1,
						 float x2,float y2,
						 float x3,float y3){ 
	
	return x1*y2+x2*y3+x3*y1-y1*x2-y2*x3-y3*x1;
}

b2Vec2* HandleContour::hitSegment(float x1,float y1,
								 float x2,float y2,
								 float x3,float y3,
								 float x4,float y4){
    float t1, t2, t3, t4, t5, t6, t7, a, px, py = 0.0;
	bool b1, b2 = false;
	t1 = x3 - x1,
	t2 = y3 - y1;
	t3 = x2 - x1;
	t4 = y2 - y1;
	t5 = x4 - x3;
	t6 = y4 - y3;
	t7 = t4 * t5 - t3 * t6;
 
    a = (((t5*t2)-t6*t1)/t7);
    px = x1 + a * t3;
	py = y1 + a * t4;
    b1 = isOnSegment(px,py,x1,y1,x2,y2);
    b2 = isOnSegment(px,py,x3,y3,x4,y4);
 
    if ((b1 && b2)) {
		//TODO: ES MUY POSIBLE DE QUE QUEDE MEMORIA COLGADA
        return new b2Vec2(px,py);
    }
    return NULL;
}

bool HandleContour::isOnSegment(float px,float py,
								float x1,float y1,
								float x2,float y2){
	bool b1, b2;
	b1 = ((((x1+0.1)>=px)&&px>=x2-0.1)||(((x1-0.1)<=px)&&px<=x2+0.1));
    b2 =((((y1+0.1)>=py)&&py>=y2-0.1)||(((y1-0.1)<=py)&&py<=y2+0.1));
    return ((b1&&b2)&&isOnLine(px,py,x1,y1,x2,y2));
}

bool HandleContour::isOnLine(float px,float py,
							 float x1,float y1,
							 float x2,float y2){
	float a, possibleY, diff;
	if ((((x2-x1)>0.1)||x1-x2>0.1)) {
		a = (y2-y1)/(x2-x1);
		possibleY = a*(px-x1)+y1;
		diff = (possibleY>py) ? possibleY - py : py - possibleY;
        return (diff<0.1);
    }
    return (((px-x1)<0.1)||x1-px<0.1);
}

list<b2Vec2*> HandleContour::calcShapes(list<b2Vec2*> l){
    list<b2Vec2*> vec, vec1, vec2, figsVec, queue;
    list<b2Vec2*>::iterator it, jt, it1, it2, jt2, it3;
	int i, n, j, j1, j2, k, h;
    float d, t, dx, dy, minLen;
    int i1,i2,i3;
	b2Vec2 p1, p2, p3, v1,v2, v, hitV;
    bool isConvex;

	queue.splice(queue.end(),l);
	while(queue.size()){
		vec.push_back(*(queue.begin()));
		isConvex = true;
		for(it = l.begin(); it != l.end(); it++){
			
			//i1=i;
   //         i2=(i<n-1)?i+1:i+1-n;
   //         i3=(i<n-2)?i+2:i+2-n;
			
			it1 = it;					//TODO: REEMPLACE i+1-n por l.begin()
			it2 = (it != --(l.end())) ? it2 = it, ++it2 : l.begin();
			it3 = (it != --(--(l.end()))) ? it3 = it, ++(++it3) : --(l.end());
		}
	}
	return figsVec;
}
*/

