#include "GameController.h"
#include "..\..\utils\Log.h"

GameController::GameController(){
	m_keys = SDL_GetKeyboardState(NULL);
	quit = false;
	rg = RunGame::getInstance();
}
GameController::~GameController(){}

void GameController::handlerEvent(){
	addListFromSDL();
	rg->handle();
	rg->call();
}

void GameController::addListFromSDL(){
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
	Click* ck = Click::getInstance();
	ck->add(c);
}
void GameController::addListener(OnMovementListener* m){
	Move* mv = Move::getInstance();
	mv->add(m);
}
void GameController::addListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	o->add(s);
}
void GameController::addListener(OnZoomListener* z){
	Zoom* zm = Zoom::getInstance();
	zm->add(z);
}
void GameController::remuveListener(OnClickListener* c){
	Click* ck = Click::getInstance();
	ck->remuve(c);
}
void GameController::remuveListener(OnMovementListener* m){
	Move* mv = Move::getInstance();
	mv->remuve(m);
}
void GameController::remuveListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	o->remuve(s);
}
void GameController::remuveListener(OnZoomListener* z){
	Zoom* zm = Zoom::getInstance();
	zm->remuve(z);
}
