
// Descomentar este código para probar SDL
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Game.h"
#include "GameActivity.h"
#include "Bootstrap.h"
#include "Activity.h"

#include <cstdio>
using namespace std;

// our Game object

int main(int argc, char* argv[])
{
	Bootstrap bootstrap;
	bootstrap.init();
	Activity* currentActivity = 0;
	try {	
		Game* g_game = 0;
		g_game = new Game(bootstrap.getScreen());
		currentActivity = new GameActivity(bootstrap.getScreen());
		while(g_game->running())
		{
			g_game->handleEvents();
			currentActivity->update();
			currentActivity->render();
		}

		delete g_game;
		delete currentActivity;

	} catch (GameException & e) {
		cout<<e.what()<<endl;
	} 

	bootstrap.getScreen().terminate();

	return 0;
}

