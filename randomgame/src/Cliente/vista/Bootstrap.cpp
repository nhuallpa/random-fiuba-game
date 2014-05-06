#include "Bootstrap.h"



Bootstrap::Bootstrap(void)
{
}

void Bootstrap::init() 
{
	
	ParserYaml* aParser = ParserYaml::getInstance();

	int w = atoi(aParser->getEscenarioAnchoP().c_str());
	int h = atoi(aParser->getEscenarioAltoP().c_str());
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		this->getScreen().init("Taller TP2", 50, 50, w, h, 0);
	} 

	std::map<std::string, std::string> map_images;
	map_images["sky"] = aParser->getEscenarioCielo();
	map_images["eart"] = aParser->getEscenarioTierra();

	std::map<std::string, std::string>::iterator it;
	for (it=map_images.begin(); it!=map_images.end(); ++it) {
		try 
		{
			TextureManager::Instance().load(it->second.c_str(), it->first.c_str(), this->getScreen().getRenderer());
		} catch (GameException & e) 
		{
			Log::e(BOOT, e.what());		
		}
	}

	loadSprites();
	initCamera(w, h);

}


void Bootstrap::initCamera(int w, int h) 
{
	std::pair<int, int> dimensionScenario = TextureManager::Instance().getDimension("eart");
	Camera & cam = TextureManager::Instance().getCamera();
	cam.setPosition(0, 0);
	cam.setDimension(w, h);
	cam.setWidthScenario(dimensionScenario.first);
	cam.setHeightScenario(dimensionScenario.second);
}

void Bootstrap::loadSprites()
{
	// todo: levantar la configuracion de los sprite del yaml
	try 
		{
			
			TextureManager::Instance().load("res/images/wwalk.png", "wwalk", this->getScreen().getRenderer());
			SpriteConfigurator::Instance().add("wwalk", 60, 60, 15, 1);

		} catch (GameException & e) 
		{
			Log::e(BOOT, e.what());		
		}
	


}

SDLScreen & Bootstrap::getScreen() 
{
	return this->screen;
}

Bootstrap::~Bootstrap(void)
{
}
