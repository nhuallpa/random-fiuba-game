#include "SDLScreen.h"



SDLScreen::SDLScreen() 
{
}

bool SDLScreen::init(const char* title, int xpos, int ypos, int width,
			int height, int flags)
{

	// init the window
	m_pWindow = SDL_CreateWindow(title, xpos, ypos,	width, height, flags);

	if(m_pWindow != 0) // window init success
	{
		this->height = height;
		this->width = width;
		renderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		if(renderer != 0) // renderer init success
		{

			SDL_SetRenderDrawColor(renderer,
			0,0,0,0);
		}
		else
		{

			return false; // renderer init fail
		}
	}
	else
	{
		return false; // window init fail
	}
}	

void SDLScreen::clear()
{
	SDL_RenderClear(renderer); // clear the renderer to the draw color
}	
void SDLScreen::render()
{
	SDL_RenderPresent(renderer); // draw to the screen
}	
void SDLScreen::terminate()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
SDL_Renderer* SDLScreen::getRenderer()
{
	return renderer;
}

SDLScreen::~SDLScreen(void)
{
}
