#include "Event.h"
#include <exception>

using namespace std;
using namespace client_controller_event;


Event::Event(void)
{
}


Event::~Event(void)
{
}

void Event::execute(SDL_Event* e, const Uint8* keys) 
	throw (int, bad_exception){
	throw (1,"Method not implmented");
}

void Event::updateStates()
	throw (int, bad_exception){
	throw (1,"Method not implmented");
}
/*
void destroy()
	throw (int, bad_exception){
	throw (1,"Method not implmented");
}
*/