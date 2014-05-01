#include "GameController.h"
#include "..\..\utils\Log.h"

GameController::GameController(){
	m_keys = SDL_GetKeyboardState(NULL);
	quit = false;
	rg = RunGame::getInstance();
}
GameController::~GameController(){}
void GameController::request(Contract* c){
	detect();
	rg->setBind(&items);
	rg->handle(c);
	//call();
	rg->call();
}

void GameController::handleState(Contract* c){
	this->request(c);
}

void GameController::call(){
	map<LISTENER,Event>::iterator it;
	/*
	it = items.find(SL);
	if(it != items.end()){
		this->notifierS((*it).second);
		items.erase(it);
	}*/
	it = items.find(ZL);
	if(it != items.end()){
		this->notifierZ((*it).second);
		items.erase(it);
	}/*
	it = items.find(CL);
	if(it != items.end()){
		this->notifierC((*it).second);
		items.erase(it);
	}*/

}

void GameController::detect(){
	SDL_Event* ev = new SDL_Event();
	SDL_StartTextInput();
	while(SDL_PollEvent( ev ))
	{
		this->handleEvents(ev);
	}
	delete ev;
}

void GameController::handleEvents(SDL_Event* e){
	SDL_PumpEvents();
	if(this->isValidKey(e)){
		rg->execute(e, m_keys);
	}
	else if(e->type == SDL_QUIT){
		quit = true;
	}
}

bool GameController::isQuit(){
	return quit;
}


bool GameController::isValidKey(SDL_Event* e){
	return ((e->type == SDL_KEYDOWN) 
		||  (e->type == SDL_KEYUP)
		||  (e->type == SDL_MOUSEWHEEL)
		||  (e->type == SDL_MOUSEBUTTONDOWN)	);
}



void GameController::addListener(OnClickListener* c){
	//lClistener.push_back(c);
	Click* ck = Click::getInstance();
	ck->add(c);
}
void GameController::addListener(OnMovementListener* m){
	lMlistener.push_back(m);
}
void GameController::addListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	//lSlistener.push_back(s);
	o->add(s);
}
void GameController::addListener(OnZoomListener* z){
	lZlistener.push_back(z);
}
void GameController::remuveListener(OnClickListener* c){
	Click* ck = Click::getInstance();
	ck->remuve(c);
}
void GameController::remuveListener(OnMovementListener* m){
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
void GameController::remuveListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	o->remuve(s);
}
void GameController::remuveListener(OnZoomListener* z){
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


void GameController::notifier(pair<LISTENER, Event> item){
	switch(item.first){
	/*case CL: this->notifierC(item.second);
		break;*/
	case ML: this->notifierM(item.second);
		break;
	/*case SL: this->notifierS(item.second);
		break;*/
	case ZL: this->notifierZ(item.second);
		break;
	default: ;
	};
}

/*
void GameController::notifierC(Event e){
	list<OnClickListener*>::iterator it;
	ClickEvent c;
	c.x = e.x, c.y = e.y;//, c.click = (Click) e.value;
	it = lClistener.begin();
	for(; it != lClistener.end(); it++){
		(*it)->OnClick(c);
	}
}*/
void GameController::notifierM(Event e){
	list<OnMovementListener*>::iterator it;
	MovementEvent m;
	m.move = (Move)e.value;
	it = lMlistener.begin();
	for(; it != lMlistener.end(); it++){
		(*it)->OnMovement(m);
	}
}/*
void GameController::notifierS(Event e){
	list<OnScrollListener*>::iterator it;
	ScrollEvent s;
	s.xSpeed = e.x, s.ySpeed = e.y;
	it = lSlistener.begin();
	for(; it != lSlistener.end(); it++){
		(*it)->OnScroll(s);
	}
}*/
void GameController::notifierZ(Event e){
	list<OnZoomListener*>::iterator it;
	ZoomEvent z;
	z.zoom = (Zoom)e.value;
	it = lZlistener.begin();
	for(; it != lZlistener.end(); it++){
		(*it)->OnZoom(z);
	}
}






/*#include "GameController.h"

GameController::GameController() {

}

GameController::~GameController() {
}

void GameController::handleState(Contract* c){
	ctx.request(c);
}

bool GameController::isQuit(){
	return ctx.isQuit();
}


void GameController::addListener(OnClickListener* c){
	ctx.addListener(c);
}
void GameController::addListener(OnMovementListener* m){
	ctx.addListener(m);
}
void GameController::addListener(OnScrollListener* s){
	ctx.addListener(s);
}
void GameController::addListener(OnZoomListener* z){
	ctx.addListener(z);
}
void GameController::remuveListener(OnClickListener* c){
	ctx.addListener(c);
}
void GameController::remuveListener(OnMovementListener* m){
	ctx.addListener(m);
}
void GameController::remuveListener(OnScrollListener* s){
	ctx.addListener(s);
}
void GameController::remuveListener(OnZoomListener* z){
	ctx.addListener(z);
}*/