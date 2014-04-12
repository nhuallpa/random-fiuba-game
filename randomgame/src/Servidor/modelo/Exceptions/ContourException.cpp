#include "ContourException.h"

using namespace server_model_exp;

ContourExp::ContourExp(int error) : exception(), idError(error) {
	mError[0] = "Ocurrio un error del tipo 0";
}



ContourExp::~ContourExp(void)
{
}


const char* ContourExp::what(){
	return mError[idError].c_str();
}

