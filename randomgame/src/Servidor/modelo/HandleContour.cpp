#include "HandleContour.h"
#include <cmath>

#define SEGMENT 2
#define MAX_VERTEX 8
using namespace server_model_handle;

HandleContour::HandleContour(){}
HandleContour::~HandleContour(){}




vector<vector<b2Vec2>> HandleContour::
	getPolygonConvex(vector<b2Vec2> contour, float epsilon, int scale){

	vector<vector<b2Vec2>> result, resultSplit, aux;
	vector<vector<b2Vec2>>::iterator jt;
	vector<b2Vec2>::iterator it;
	vector<b2Vec2> contourReduced, contourEscalade;
    b2Separator* sep = NULL;


	
	contourReduced = this->rdp(contour, epsilon);



	for(it = contourReduced.begin();
	it != contourReduced.end();
	it++){
		contourEscalade.push_back(b2Vec2((*it).x*scale,(*it).y*scale));
	}
	contourReduced.clear();

	sep = new b2Separator();
	if (sep->Validate(contourEscalade)==0) {
		sep->calcShapes(contourEscalade, result);
		
		contourEscalade.clear();

		for(jt = result.begin();
		jt != result.end();
		jt++){
			vector<b2Vec2> vec;
			contourEscalade = (*jt);
			for(it = contourEscalade.begin();
			it != contourEscalade.end();
			it++){
				vec.push_back(b2Vec2((*it).x/scale,(*it).y/scale));
			}
			aux.push_back(vec);
		}
	}
	else {
		//lanzar excepcion
	}
	
	result.clear();
		
	for(jt = aux.begin(); jt != aux.end(); jt++){
		if((*jt).size() > MAX_VERTEX){
			resultSplit = this->split((*jt));
			result.insert(result.end(), resultSplit.begin(), resultSplit.end());
		}
		else{
			result.push_back((*jt));
		}
	}
	delete sep;
	return result;
}

vector<b2Vec2> HandleContour::rdp(vector<b2Vec2> contour, float epsilon){
	vector<b2Vec2>::iterator it;
	b2Vec2 firstPoint = (*contour.begin());
	b2Vec2 lastPoint = (*(--contour.end()));
	b2Vec2 splitPoint;
	float distance = 0.0, aux = 0.0;
	vector<b2Vec2> contourRDP;
	vector<b2Vec2> contour1, contour2, 
		         contour3, contour4;
	int i = 1, j = 0;

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
			j = i;
		}
		i++;
	}
		i = 0;
	if(distance > epsilon){
		for(it = contour.begin();
			it != contour.end();
			it++){
				if(i <= j){
					contour1.push_back((*it));
				}
				if(i >= j){
					contour2.push_back((*it));
				}
				i++;
		}
		contour3 = this->rdp(contour1, epsilon);
		contour4 = this->rdp(contour2, epsilon);
		contourRDP.insert(contourRDP.end(),
			              contour3.begin(),
						  --(contour3.end()));
		contourRDP.insert(contourRDP.end(),
			              contour4.begin(),
						  contour4.end());
		
		return contourRDP;
	}
	else{
		contourRDP.push_back(firstPoint);
		contourRDP.push_back(lastPoint);
		return contourRDP;
	}
	return contour;
	//debo lanzar una excepcion
}

float HandleContour::findPerpendicularDistance(b2Vec2 p, b2Vec2 p1, b2Vec2 p2){
	float slope = 0.0;
	float intercept = 0.0;
	float result = 0.0;

	if(p1.x == p2.x){
		return abs(p.x - p1.x);
	}
	else{
		slope = (p2.y - p1.y) / (p2.x - p1.x);
		intercept = p1.y - (slope * p1.x);
		result = abs(slope * p.x - p.y + intercept) 
				/ sqrt(pow(slope, 2) + 1);
	}
	return result;
}



vector<vector<b2Vec2>> HandleContour::split(vector<b2Vec2> contour){
	vector<b2Vec2>::iterator it;
	b2Vec2 firstPoint = (*contour.begin());
	b2Vec2 lastPoint = (*(--contour.end()));
	b2Vec2 splitPoint;
	float distance = 0.0, aux = 0.0;
	vector<b2Vec2> contour1, contour2;
	vector<vector<b2Vec2>> result, 
		         contour3, contour4,
				 contourRDP;

	int i = 1, j = 0;

	if(contour.size() <= MAX_VERTEX){
		result.push_back(contour);
		return result;
	}

	for(it = ++(contour.begin());
		it != --(contour.end());
		it++){
		aux = findPerpendicularDistance((*it),firstPoint,lastPoint);
		if(aux > distance){
			distance = aux;
			splitPoint = (*it);
			j = i;
		}
		i++;
	}
		i = 0;
	
	
	for(it = contour.begin();
		it != contour.end();
		it++){
			if(i <= j){
				contour1.push_back((*it));
			}
			if(i >= j){
				contour2.push_back((*it));
			}
			i++;
	}
	//agrego uno mas!
	contour2.push_back(firstPoint);

	contour3 = this->split(contour1);
	contour4 = this->split(contour2);
	contourRDP.insert(contourRDP.end(),
			            contour3.begin(),
						contour3.end());
	contourRDP.insert(contourRDP.end(),
			            contour4.begin(),
						contour4.end());
		
	return contourRDP;
}



/*


vector<vector<b2Vec2>> HandleContour::
	getPolygonConvex(vector<b2Vec2> contour, float epsilon, int scale){

	vector<vector<b2Vec2>> result, resultSplit, aux;
	vector<vector<b2Vec2>>::iterator jt;
	vector<b2Vec2>::iterator it;
	vector<b2Vec2> contourReduced, contourEscalade;
    b2Separator* sep = NULL;

	for(it = contour.begin();
	it != contour.end();
	it++){
		contourEscalade.push_back(b2Vec2((*it).x*scale,(*it).y*scale));
	}

	sep = new b2Separator();
	contourReduced = this->rdp(contourEscalade, epsilon);
	if (sep->Validate(contourReduced)==0) {
		sep->calcShapes(contourReduced, result);
		
		for(jt = result.begin();
		jt != result.end();
		jt++){
			vector<b2Vec2> vec;
			contourEscalade = (*jt);
			for(it = contourEscalade.begin();
			it != contourEscalade.end();
			it++){
				vec.push_back(b2Vec2((*it).x/scale,(*it).y/scale));
			}
			aux.push_back(vec);
		}
	}
	else {
		//lanzar excepcion
	}
	
	result.clear();
		
	for(jt = aux.begin(); jt != aux.end(); jt++){
		if((*jt).size() > MAX_VERTEX){
			resultSplit = this->split((*jt));
			result.insert(result.end(), resultSplit.begin(), resultSplit.end());
		}
		else{
			result.push_back((*jt));
		}
	}
	delete sep;
	return result;
}
*/

