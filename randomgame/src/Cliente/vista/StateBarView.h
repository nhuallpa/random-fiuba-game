#pragma once
#ifndef __STATEBARVIEW_H__
#define __STATEBARVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "ViewGroup.h"
#include "TextView.h"
#include "time.h"
class StateBarView : public View
{
private:
	struct state{
		std::string msj;
		int j;
	};

	std::vector <state> stateV;

	int i;

	void cutVect();

	std::string msj;

	TextView label;
	
public:
	int j;
	SDL_Color color;

	~StateBarView(void);

	StateBarView();
				
	void setMsj(std::string msj);

	void draw(SDLScreen & screen);

	static StateBarView & Instance(){
			static StateBarView theStateBarView;
			return theStateBarView;
	}
};

#endif /** __STATEBARVIEW_H__*/