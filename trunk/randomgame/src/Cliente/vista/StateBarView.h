#pragma once
#ifndef __STATEBARVIEW_H__
#define __STATEBARVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "ViewGroup.h"
#include "time.h"
class StateBarView : public View
{
private:
	struct state{
		std::string msj;
		time_t ttime;	
	};

	std::vector <state> stateV;

	int msjs;

	void cutVect();
	
public:
	
	~StateBarView(void);

	StateBarView(int msjs);
				
	void setMsj(std::string msj);

	void draw(SDLScreen & screen);
};

#endif /** __STATEBARVIEW_H__*/