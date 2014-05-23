#include "SDLScreen.h"



SDLScreen::SDLScreen() 
{
	this->scale = 1;
}

void SDLScreen::init(const char* title, int xpos, int ypos, int width,
			int height, int flags)
{
	this->title.append(title);
	// init the window
	m_pWindow = SDL_CreateWindow(title, xpos, ypos,	width, height, flags);

	if(m_pWindow != 0) // window init success
	{
		this->height = height;
		this->width = width;
		renderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_TARGETTEXTURE);
			if(renderer != 0) // renderer init success
		{

			SDL_SetRenderDrawColor(renderer,
			0,0,0,0);

			SDL_RenderSetScale(renderer, this->scale, this->scale);			
		}
		else
		{

			//return false; // renderer init fail
		}
	}
	else
	{
		//return false; // window init fail
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
	TTF_Quit();
	SDL_Quit();
}

void SDLScreen::setState(std::string string_state)
{
	std::stringstream caption;

	caption<<this->title<<" - Estado: "<<string_state;
	SDL_SetWindowTitle(m_pWindow, caption.str().c_str());
}

SDL_Renderer* SDLScreen::getRenderer()
{
	return renderer;
}

SDLScreen::~SDLScreen(void)
{
}

void SDLScreen::OnZoom(ZoomEvent e)
{
	SDL_Rect newViewPort;
	float nextScale = this->scale + (0.01 * e.y);
	if (nextScale > 0.5 && nextScale <= 3) 
	{
		SDL_RenderSetScale(renderer, nextScale, nextScale);
		SDL_RenderGetViewport(renderer, &newViewPort);

		//todo: pasar a camera
		int camaraBootom = newViewPort.h + this->refCam->getY();
		int camaraRight = newViewPort.w + this->refCam->getX();
		if (camaraBootom <= this->refCam->getHeightScenario() &&
			camaraRight <= this->refCam->getWidthScenario())
		{
			this->refCam->setH(newViewPort.h);
			this->refCam->setW(newViewPort.w);
			this->scale = nextScale;
		}
		else
		{
			SDL_RenderSetScale(renderer, this->scale, this->scale);
		}
		
	}
	
}