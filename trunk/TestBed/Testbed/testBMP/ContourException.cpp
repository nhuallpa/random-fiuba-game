#include "ContourException.h"

using namespace server_model_exp;

const char* ContourExp::what() const throw() {
	return e.second.c_str();
}

