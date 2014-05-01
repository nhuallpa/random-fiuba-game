#include "Over.h"

Over* Over::over = NULL;

Over::Over(void){}

Over::~Over(void){}



Over* Over::getInstance(){
	if(!over){
		over = new Over();
	}
	return over;
}
