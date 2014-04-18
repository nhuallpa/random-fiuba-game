
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
private:
	Context ctx;

};

#endif /* GAMECONTROLLER_H_ */
