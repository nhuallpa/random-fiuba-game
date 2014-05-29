#pragma once

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include <SDL.h>
#include "RunGame.h"
#include "Contracts\OnClickListener.h"
#include "Contracts\OnMovementListener.h"
#include "Contracts\OnScrollListener.h"
#include "Contracts\OnZoomListener.h"

class GameController{
	public:
		GameController(void);
		~GameController(void);
		void handlerEvent();
		bool isQuit();
		void destroy();
		void addListener(OnClickListener* c);
		void addListener(OnMovementListener* m);
		void addListener(OnScrollListener* s);
		void addListener(OnZoomListener* z);
		void remuveListener(OnClickListener* c);
		void remuveListener(OnMovementListener* m);
		void remuveListener(OnScrollListener* s);
		void remuveListener(OnZoomListener* z);
	private:
		RunGame* rg;
};

#endif 
