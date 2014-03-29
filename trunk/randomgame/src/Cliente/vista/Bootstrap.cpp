#include "Bootstrap.h"



Bootstrap::Bootstrap(void)
{
}

void Bootstrap::init() 
{
	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		this->getScreen().init("Chapter 1", 50, 50, 640, 480, 0);
	} 

	std::map<std::string, std::string> map_images;
	map_images["animate"]="image/waccuse.png";
	map_images["cuadrado"]="image/cuadrado.png";
	map_images["fondo"]="image/fondo.png";
	map_images["water"]="image/water_alfa.png";

	std::map<std::string, std::string>::iterator it;

	for (it=map_images.begin(); it!=map_images.end(); ++it) {
		try 
		{
			TextureManager::Instance().load(it->second.c_str(),it->first.c_str(),this->getScreen().getRenderer());
		} catch (GameException & e) 
		{
			std::cout<<e.what()<<std::endl;
		}
	}
}

SDLScreen & Bootstrap::getScreen() 
{
	return this->screen;
}

Bootstrap::~Bootstrap(void)
{
}
