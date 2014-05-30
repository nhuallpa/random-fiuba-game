#pragma once
#include "../utils/Network/Socket.h"
#include "../utils/Network/Messages.h"
#include "../utils/Network/Thread.h"
#include "../utils/Network/Condition.h"
#include "../utils/Util.h"
#include "../utils/Log.h"
#include <string>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <queue>
/**
* Do all operation to server
*/
class Updater
{
private:
	std::string pl;

	// Only references 
	Socket* input;
	Socket* output;

	/** Obejtos para sincronismo entre modelo y red*/
	Mutex* m;
	Mutex* n;
	Condition* somethingToTell;
	std::vector<Playable>* localChanges;

public:
	Updater(Socket* input, 
			Socket* output,
			Mutex* m,
			Mutex* n,
			Condition* somethingToTell,
			std::vector<Playable>* localChanges);

	~Updater(void);

	void setPlayerId(std::string pl) {this->pl = pl;}

	bool doLogin();

	void addLocalMovementFromView(Playable p);

};

