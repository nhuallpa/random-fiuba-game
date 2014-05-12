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

	

	void cutVect();
	
public:
	
	int i;

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