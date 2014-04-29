#include "Context.h"
#include "WithOutBehavior.h"
#include "..\..\utils\Log.h"

Context::Context(){
	m_keys = SDL_GetKeyboardState(NULL);
	quit = false;
	state = WithOutBeHavior::getInstance();
}
Context::~Context(){}
void Context::request(Contract* c){
	detect();
	state->setBind(&items);
	state->handle(c);
	call();
}

void Context::call(){
	map<LISTENER,Event>::iterator it;
	
	it = items.find(SL);
	if(it != items.end()){
		this->notifierS((*it).second);
		items.erase(it);
	}
	it = items.find(ZL);
	if(it != items.end()){
		this->notifierZ((*it).second);
		items.erase(it);
	}
	it = items.find(CL);
	if(it != items.end()){
		this->notifierC((*it).second);
		items.erase(it);
	}

}

void Context::detect(){
	SDL_Event* ev = new SDL_Event();
	SDL_StartTextInput();
	while(SDL_PollEvent( ev ))
	{
		this->handleEvents(ev);
	}
	delete ev;
}

void Context::handleEvents(SDL_Event* e){
	SDL_PumpEvents();
	if(this->isValidKey(e)){
		state = state->execute(e, m_keys);
	}
	else if(e->type == SDL_QUIT){
		quit = true;
	}
}

bool Context::isQuit(){
	return quit;
}


bool Context::isValidKey(SDL_Event* e){
	return ((e->type == SDL_KEYDOWN) 
		||  (e->type == SDL_KEYUP)
		||  (e->type == SDL_MOUSEWHEEL)
		||  (e->type == SDL_MOUSEBUTTONDOWN)	);
}



void Context::addListener(OnClickListener* c){
	lClistener.push_back(c);
}
void Context::addListener(OnMovementListener* m){
	lMlistener.push_back(m);
}
void Context::addListener(OnScrollListener* s){
	lSlistener.push_back(s);
}
void Context::addListener(OnZoomListener* z){
	lZlistener.push_back(z);
}
void Context::remuveListener(OnClickListener* c){
	list<OnClickListener*>::iterator it;
	list<OnClickListener*>::iterator itDrop;
	it = lClistener.begin();
	itDrop = lClistener.end();
	for(; it != lClistener.end(); it++){
		if((*it) == c){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lClistener.end()){
		lClistener.erase(itDrop);
	}
}
void Context::remuveListener(OnMovementListener* m){
	list<OnMovementListener*>::iterator it;
	list<OnMovementListener*>::iterator itDrop;
	it = lMlistener.begin();
	itDrop = lMlistener.end();
	for(; it != lMlistener.end(); it++){
		if((*it) == m){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lMlistener.end()){
		lMlistener.erase(itDrop);
	}
}
void Context::remuveListener(OnScrollListener* s){
	list<OnScrollListener*>::iterator it;
	list<OnScrollListener*>::iterator itDrop;
	it = lSlistener.begin();
	itDrop = lSlistener.end();
	for(; it != lSlistener.end(); it++){
		if((*it) == s){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lSlistener.end()){
		lSlistener.erase(itDrop);
	}
}
void Context::remuveListener(OnZoomListener* z){
	list<OnZoomListener*>::iterator it;
	list<OnZoomListener*>::iterator itDrop;
	it = lZlistener.begin();
	itDrop = lZlistener.end();
	for(; it != lZlistener.end(); it++){
		if((*it) == z){
			itDrop = it;
			break;
		}
	}
	if(itDrop != lZlistener.end()){
		lZlistener.erase(itDrop);
	}
}


void Context::notifier(pair<LISTENER, Event> item){
	switch(item.first){
	case CL: this->notifierC(item.second);
		break;
	case ML: this->notifierM(item.second);
		break;
	case SL: this->notifierS(item.second);
		break;
	case ZL: this->notifierZ(item.second);
		break;
	default: ;
	};
}


void Context::notifierC(Event e){
	list<OnClickListener*>::iterator it;
	ClickEvent c;
	c.x = e.x, c.y = e.y, c.click = (Click) e.value;
	it = lClistener.begin();
	for(; it != lClistener.end(); it++){
		(*it)->OnClick(c);
	}
}
void Context::notifierM(Event e){
	list<OnMovementListener*>::iterator it;
	MovementEvent m;
	m.move = (Move)e.value;
	it = lMlistener.begin();
	for(; it != lMlistener.end(); it++){
		(*it)->OnMovement(m);
	}
}
void Context::notifierS(Event e){
	list<OnScrollListener*>::iterator it;
	ScrollEvent s;
	s.xSpeed = e.x, s.ySpeed = e.y;
	it = lSlistener.begin();
	for(; it != lSlistener.end(); it++){
		(*it)->OnScroll(s);
	}
}
void Context::notifierZ(Event e){
	list<OnZoomListener*>::iterator it;
	ZoomEvent z;
	z.zoom = (Zoom)e.value;
	it = lZlistener.begin();
	for(; it != lZlistener.end(); it++){
		(*it)->OnZoom(z);
	}
}
