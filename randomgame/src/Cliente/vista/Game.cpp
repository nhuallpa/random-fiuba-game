#include "Game.h"


Game::Game(const SDLScreen & screen): m_screen(screen)
{
	m_bRunning=true;
}

Game::~Game(void)
{

}

void Game::handleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_bRunning = false;
				break;
			default:
				break;
		}
	}
}