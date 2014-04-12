#include "HandleContour.h"
#include <cmath>
#include "Exceptions\ContourException.h"
#include <utility>
#include "..\..\utils\Log.h"
#include "..\..\utils\Constantes\Constantes.h"
#include <map>

#define SEGMENT 2
#define MAX_VERTEX 8

using namespace server_model_handle;
using namespace server_model_exp;

HandleContour::HandleContour(){
	_error[1001] = HC_ERROR_1;
	_error[1002] = HC_ERROR_2;
	_error[1003] = HC_ERROR_3;

}
HandleContour::~HandleContour(){}

vector<vector<vector<b2Vec2>>> HandleContour::
	getPolygonConvex(vector<vector<b2Vec2>> contour, float epsilon, int scale)
	throw (ContourExp, exception){
		vector<vector<b2Vec2>>::iterator it;
		vector<vector<vector<b2Vec2>>> result;
		vector<vector<b2Vec2>> aux;	
		try{
			for(it = contour.begin(); it != contour.end(); it++){
				aux = this->getPolygonConvex((*it), epsilon, scale);
				result.push_back(aux);
			}
		}
		catch(ContourExp ce){
			throw ce;
		}
		catch(exception e){
			Log::e(HANDLE_CONTOUR, "Contour not invalid");
			throw (-15,"Contour not invalid");
		}
		return result;
}


vector<vector<b2Vec2>> HandleContour::
	getPolygonConvex(vector<b2Vec2> contour, float epsilon, int scale)
	throw (ContourExp, exception){
	vector<vector<b2Vec2>>::iterator it;
	vector<vector<b2Vec2>> result;
	vector<b2Vec2> contourAux;
	b2Separator* sep = NULL;
	Log::i(HANDLE_CONTOUR, "============== INICIANDO HANDLE CONTOUR =============");
	try{
		if (sep->Validate(contour)) {
			Log::e(HANDLE_CONTOUR, "Contour not invalid: "+this->getErr(sep->Validate(contour)));
			//throw (new ContourExp(pair<int,string>(sep->Validate(contour),"Contour not invalid")));
		}
		contourAux = this->rdp(contour, epsilon);
		contourAux = this->mulK(contourAux, scale);
		sep = new b2Separator();
		sep->calcShapes(contourAux, result);
		contourAux.clear();
		delete sep;
		result = this->mulK(result, scale);
		result = this->valSize(result);
	}
	catch(ContourExp ce){
		throw ce;
	}
	catch(exception e){
		Log::e(HANDLE_CONTOUR, "Contour not invalid: %s",
		this->getErr(sep->Validate(contour)));
		throw (sep->Validate(contour),"Contour not invalid");
	}
	return result;
}

vector<b2Vec2> HandleContour::rdp(vector<b2Vec2> contour, float epsilon){
	vector<b2Vec2>::iterator it;
	b2Vec2 firstPoint = (*contour.begin());
	b2Vec2 lastPoint = (*(--contour.end()));
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
		it++, i++){
		aux = findPerpendicularDistance((*it),firstPoint,lastPoint);
		if(aux > distance){
			distance = aux;
			j = i;
		}
	}
	if(distance > epsilon){
		for(it = contour.begin(), i = 0;
			it != contour.end();
			it++, i++){
				if(i <= j){
					contour1.push_back((*it));
				}
				if(i >= j){
					contour2.push_back((*it));
				}
		}
		contour3 = this->rdp(contour1, epsilon);
		contour4 = this->rdp(contour2, epsilon);
		contourRDP.insert(contourRDP.end(),
			              contour3.begin(),
						  --(contour3.end()));
		contourRDP.insert(contourRDP.end(),
			              contour4.begin(),
						  contour4.end());
	}
	else{
		contourRDP.push_back(firstPoint);
		contourRDP.push_back(lastPoint);
	}
	return contourRDP;
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
	float distance = 0.0, aux = 0.0;
	vector<b2Vec2> contour1, contour2;
	vector<vector<b2Vec2>> result, 
		         contour3, contour4,
				 contourRDP;

	int i = 2, j = 0;

	if(contour.size() <= MAX_VERTEX){
		result.push_back(contour);
		return result;
	}

	for(it = contour.begin(), ++it, ++it;
		it != --(contour.end());
		it++, i++){
		aux = findPerpendicularDistance((*it),firstPoint,lastPoint);
		if(aux > distance){
			distance = aux;
			j = i;
		}
	}
	
	
	for(it = contour.begin(), i = 0;
		it != contour.end();
		it++, i++){
			if(i <= j){
				contour1.push_back((*it));
			}
			if(i >= j){
				contour2.push_back((*it));
			}
	}
	//add the firsPoint!!
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


vector<b2Vec2> HandleContour::mulK(vector<b2Vec2> contour, float scale){
	vector<b2Vec2>::iterator it;
	vector<b2Vec2> result;
	for(it = contour.begin();
	it != contour.end();
	it++){
		result.push_back(b2Vec2((*it).x*scale,(*it).y*scale));
	}
	return result;
}

vector<vector<b2Vec2>> HandleContour::mulK(vector<vector<b2Vec2>> contours, float scale){
	vector<vector<b2Vec2>>::iterator it;
	vector<vector<b2Vec2>> result;
	for(it = contours.begin(); it != contours.end(); it++){
		result.push_back(this->mulK((*it), (float) 1/scale));
	}
	return result;
}

vector<vector<b2Vec2>> HandleContour::valSize(vector<vector<b2Vec2>> contours){
	vector<vector<b2Vec2>> result, resultSplit;
	vector<vector<b2Vec2>>::iterator jt;
	for(jt = contours.begin(); jt != contours.end(); jt++){
		removeVertexThanMore(&(*jt));
		if((*jt).size() > MAX_VERTEX){
			resultSplit = this->split((*jt));
			result.insert(result.end(), resultSplit.begin(), resultSplit.end());
		}
		else{
			result.push_back((*jt));
		}
	}
	return result;
}

void HandleContour::
	removeVertexThanMore(vector<b2Vec2>* contour){
		bool isDelete = false;
		vector<b2Vec2>::iterator it;
		vector<b2Vec2>::iterator itPoint;
		map<float,vector<vector<b2Vec2>::iterator>>::iterator ft;
		map<float,vector<vector<b2Vec2>::iterator>> mx;
		map<float,vector<vector<b2Vec2>::iterator>> my;
		for(it = contour->begin(); it != contour->end(); it++){
			
			//search x
			ft = mx.find((*it).x);
			if(ft != mx.end()){
				(*ft).second.push_back(it);
				if((*ft).second.size() >= 3){
					itPoint = (*ft).second[1];
					isDelete = true;
					break;
				}
			}
			else{
				mx[(*it).x] = vector<vector<b2Vec2>::iterator>();	
				mx[(*it).x].push_back(it);
			}

			//search y
			ft = my.find((*it).y);
			if(ft != my.end()){
				(*ft).second.push_back(it);
				if((*ft).second.size() >= 3){
					itPoint = (*ft).second[1];
					isDelete = true;
					break;
				}
				
			}
			else{
				my[(*it).y] = vector<vector<b2Vec2>::iterator>();
				my[(*it).y].push_back(it);
			}

		}
		if(isDelete) 
			contour->erase(itPoint);
}

string HandleContour::getErr(int valueErr){
	 return _error[HC_OFFSET + valueErr];
}



