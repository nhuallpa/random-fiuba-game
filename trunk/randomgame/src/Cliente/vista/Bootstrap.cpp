#include "Bootstrap.h"



Bootstrap::Bootstrap(void)
{
}

void Bootstrap::init() 
{
	// attempt to initialize SDL
	ParserYaml* aParser = ParserYaml::getInstance();

	int w = atoi(aParser->getEscenarioAnchoP().c_str());
	int h = atoi(aParser->getEscenarioAltoP().c_str());
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		this->getScreen().init("Chapter 1", 50, 50, w, h, 0);
	} 

	std::map<std::string, std::string> map_images;
	map_images["sky"] = aParser->getEscenarioCielo();

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
