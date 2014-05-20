#include "Bootstrap.h"



Bootstrap::Bootstrap(void)
{
}

void Bootstrap::init() 
{
	Log::i("Bootstrap: Iniciando");
	std::string path = DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);

	std::map<std::string,std::string> prop = Util::loadProperteries("config/client.properties");
	int w = Util::string2int(prop["ventana.ancho"]);
	int h = Util::string2int(prop["ventana.alto"]);
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		this->getScreen().init("Taller TP2", 50, 50, w, h, 0);
	} 
	FontManager::Instance().init(this->getScreen().getRenderer());

	std::map<std::string, std::string> map_images;
	map_images["sky"] = aParser->getEscenarioCielo();
	map_images["eart"] = aParser->getEscenarioTierra();

	TextureManager::Instance().init(w,h,map_images,this->getScreen().getRenderer());
	loadSprites();
	initCamera(w, h);
	this->getScreen().setCamera(&(TextureManager::Instance().getCamera()));

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
			SpriteConfigurator::Instance().add("wwalk", 60, 60, 15, 0);

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

void Bootstrap::shoutDown()
{
	FontManager::Instance().closeFonts();
	getScreen().terminate();
}
