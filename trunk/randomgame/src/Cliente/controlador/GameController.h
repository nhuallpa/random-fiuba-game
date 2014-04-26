
#pragma once

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "Contracts\Contract.h"
#include "Context.h"

class GameController {
public:
	void handleState(Contract* c);
	bool isQuit();
	GameController();
	~GameController();
	void addListener(OnClickListener* c);
	void addListener(OnMovementListener* m);
	void addListener(OnScrollListener* s);
	void addListener(OnZoomListener* z);
	void remuveListener(OnClickListener* c);
	void remuveListener(OnMovementListener* m);
	void remuveListener(OnScrollListener* s);
	void remuveListener(OnZoomListener* z);
private:
	Context ctx;

};

#endif /* GAMECONTROLLER_H_ */
