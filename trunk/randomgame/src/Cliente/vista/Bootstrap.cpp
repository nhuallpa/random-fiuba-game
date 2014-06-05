#include "Bootstrap.h"
#include "../sonido/SoundManager.h"



Bootstrap::Bootstrap(void)
{
}

void Bootstrap::init() 
{
	Log::i("Bootstrap: Iniciando");

	SoundManager::Instance().init();
	SoundManager::Instance().playMusic();

	std::map<std::string,std::string> prop = Util::loadProperteries("config/client.properties");
	int w = Util::string2int(prop["ventana.ancho"]);
	int h = Util::string2int(prop["ventana.alto"]);
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		this->getScreen().init("Fiuba Worms", 50, 50, w, h, 0);
	} 
	FontManager::Instance().init(this->getScreen().getRenderer());
	TextureManager::Instance().init(w,h);

	loadWait();

	// despues de que el server dija comienze el juego
	loadConfigGame();

}

void Bootstrap::loadConfigGame() 
{
	Log::i("Bootstrap: Iniciando");
	std::string path = DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);

	std::map<std::string, std::string> map_images;
	map_images["sky"] = aParser->getEscenarioCielo();

	TextureManager::Instance().loadImages(map_images, this->getScreen().getRenderer());
	loadSprites();
	loadEart();
	// a a partir de aca tengo las dimensiones del terreno
	loadMenuWeapon();
	initCamera(this->getScreen().getWidth(), this->getScreen().getHeight());
	this->getScreen().setCamera(&(TextureManager::Instance().getCamera()));
	std::pair<int, int> dimensionScenario = TextureManager::Instance().getDimension("eart");
	//this->getScreen().createTarget(dimensionScenario.first, dimensionScenario.second);
	//this->getScreen().createTarget(this->getScreen().getWidth(), this->getScreen().getHeight());

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

void Bootstrap::loadWait()
{
	try 
		{
			TextureManager::Instance().load("res/images/watting.jpg", "waitting", this->getScreen().getRenderer());
		} 
		catch (GameException & e) 
		{
			Log::e(BOOT, e.what());		
		}
}

void Bootstrap::loadEart()
{
	// todo: levantar la configuracion de los sprite del yaml
	std::string path = DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);
	try 
		{
			TextureManager::Instance().loadStream(aParser->getEscenarioTierra(), "eart", this->getScreen().getRenderer());
		} 
		catch (GameException & e) 
		{
			Log::e(BOOT, e.what());		
		}
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
	SoundManager::Instance().close();

}

void Bootstrap::loadMenuWeapon(){
	try {
		TextureManager::Instance().load("res/images/MenuWeapon.png", "MenuWeapon", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/grenade.1.png", "gun_1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/bazooka.1.png", "gun_2", this->getScreen().getRenderer());
	} catch (GameException & e) 
	{
		Log::e(BOOT, e.what());		
	}
}