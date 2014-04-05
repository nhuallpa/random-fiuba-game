#include "HandleContour.h"
#include <cmath>

#define SEGMENT 2
#define MAX_VERTEX 8
using namespace server_model_handle;

HandleContour::HandleContour(){}
HandleContour::~HandleContour(){}




vector<vector<b2Vec2>> HandleContour::
	getPolygonConvex(vector<b2Vec2> contour, 
	                 float epsilon, 
					 int scale){
	vector<vector<b2Vec2>> result, resultSplit, resultEnd;
	vector<vector<b2Vec2>>::iterator jt;
	vector<b2Vec2>::iterator it;
	vector<b2Vec2> contourReduced, contourEscalade;

    b2Separator* sep = new b2Separator();
	//ESCALAR?
	for(it = contour.begin();
	it != contour.end();
	it++){
		contourEscalade.push_back(b2Vec2((*it).x*scale,(*it).y*scale));
	}


	contourReduced = this->rdp(contourEscalade, 0.5);
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
			resultEnd.push_back(vec);
		}
	}
	else {
		//lanzar excepcion
	}
		
		
		//for(it = result.begin(); it != result.end(); it++){
	//		if((*it).size() > MAX_VERTEX){
	//			resultSplit = split((*it));
	//			resultEnd.insert(resultEnd.end(), 
	//				             resultSplit.begin(), 
	//							 resultSplit.end());
	//		}
	//	}
	//	result.insert(result.end(), resultEnd.begin(), resultEnd.end());
	delete sep;
	return resultEnd;
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


/*


//vector<b2Vec2> HandleContour::change(list<b2Vec2*> contour, int scale){
//	list<b2Vec2*>::iterator it;
//	vector<b2Vec2> vec;
//	list<b2Vec2*> contour2;
//	for(it = contour2.begin();
//	it != contour2.end();
//	it++){
//		b2Vec2 b2vec;
//		b2vec.x = (*it)->x * scale;
	//	b2vec.y = (*it)->y * scale;
	//	vec.push_back(b2vec);
//	}
//	return vec;
//}

vector<vector<b2Vec2>> HandleContour::getPolygonConvex(vector<b2Vec2> contour, float epsilon, int scale){
	vector<vector<b2Vec2> >result;
    b2Separator* sep = new b2Separator();
	//ESCALAR?
	result = getPolygonConvex(contour,epsilon,sep);
	delete sep;
	return result;
}

vector<vector<b2Vec2>> HandleContour::
	getPolygonConvex(vector<b2Vec2> contour, float epsilon, b2Separator* sep){
		vector<vector<b2Vec2>>::iterator it;
		vector<vector<b2Vec2>> result, resultSplit, resultEnd;
		vector<b2Vec2*> contour2;
		vector<b2Vec2> vec;

		vec = this->rdp(contour, 0.5);
		if (sep->Validate(vec)==0) {
			sep->calcShapes(vec, result);
		}
		else {
			//lanzar excepcion
		}
		
		
		//for(it = result.begin(); it != result.end(); it++){
	//		if((*it).size() > MAX_VERTEX){
	//			resultSplit = split((*it));
	//			resultEnd.insert(resultEnd.end(), 
	//				             resultSplit.begin(), 
	//							 resultSplit.end());
	//		}
	//	}
	//	result.insert(result.end(), resultEnd.begin(), resultEnd.end());
		return result;
}



vector<vector<b2Vec2>> HandleContour::
	split(vector<b2Vec2> contour){
		vector<vector<b2Vec2>> result;
		int rest = contour.size() % MAX_VERTEX;
		int cant = (int) contour.size() / MAX_VERTEX;
		return result;
}

vector<b2Vec2> HandleContour::getItems(vector<b2Vec2>* contour, int cant){
	int i = 0;
	vector<b2Vec2>::iterator it, aux;
	vector<b2Vec2> result;
	for(it = contour->begin(); 
		(i < cant)||(it != contour->end()); it++, i++){
			result.push_back((*it));
			aux = it;
	}
	contour->erase(contour->begin(), aux);
	return result;
}

*/