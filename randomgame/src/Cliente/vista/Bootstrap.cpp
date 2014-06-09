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
	TextManager::Instance().init(this->getScreen().getRenderer());
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
	std::string path = DEFAULT_YAML_LEVEL;
	ParserYaml* aParser = ParserYaml::getInstance(path);
	try 
		{
			TextureManager::Instance().load(aParser->getEscenarioTierra(), "eart", this->getScreen().getRenderer(), true);
		} 
		catch (GameException & e) 
		{
			Log::e(BOOT, e.what());		
		}
}

void Bootstrap::loadSprites()
{

	try 
		{
			TextureManager::Instance().load("res/images/wwalk.png", "caminar", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/wbazbak.png", "bazooka", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/wdynbak.png", "dinamita", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/wgrnbak.png", "granada", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/whgrbak.png", "holy", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/wairbak.png", "radio", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/wflyup.png", "salto", this->getScreen().getRenderer());


			SpriteConfigurator::Instance().add("caminar", 60, 60, 15, true);
			SpriteConfigurator::Instance().add("bazooka", 60, 60, 32, true);
			SpriteConfigurator::Instance().add("dinamita", 60, 60, 10, true);
			SpriteConfigurator::Instance().add("granada", 60, 60, 10, true);
			SpriteConfigurator::Instance().add("holy", 60, 60, 10, true);
			SpriteConfigurator::Instance().add("radio", 60, 60, 10, true);
			SpriteConfigurator::Instance().add("salto", 60, 60, 2, true);



			TextureManager::Instance().load("res/images/clustlet.png", "clustlet", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/circle25.png", "circle25", this->getScreen().getRenderer());			
			SpriteConfigurator::Instance().add("clustlet", 60, 60, 6, true);
			SpriteConfigurator::Instance().add("circle25", 50, 50, 8, false);

			

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
		/*TextureManager::Instance().load("res/images/grenade.1.png", "gun_1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/bazooka.1.png", "gun_2", this->getScreen().getRenderer());
		*/
		TextureManager::Instance().load("res/images/aim.png", "aim", this->getScreen().getRenderer());

		TextureManager::Instance().load("res/images/ok.png", "ok", this->getScreen().getRenderer());

		TextureManager::Instance().load("res/images/bazooka.1.1.png", "bazooka.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/bazooka.1.2.png", "bazooka.1.2", this->getScreen().getRenderer());

		TextureManager::Instance().load("res/images/grenade.1.1.png", "grenade.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/grenade.1.2.png", "grenade.1.2", this->getScreen().getRenderer());

		TextureManager::Instance().load("res/images/hgrenade.1.1.png", "hgrenade.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/hgrenade.1.2.png", "hgrenade.1.2", this->getScreen().getRenderer());
		
		TextureManager::Instance().load("res/images/donkey.1.1.png", "donkey.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/donkey.1.2.png", "donkey.1.2", this->getScreen().getRenderer());
		
		TextureManager::Instance().load("res/images/dynamite.1.1.png", "dynamite.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/dynamite.1.2.png", "dynamite.1.2", this->getScreen().getRenderer());

		TextureManager::Instance().load("res/images/airstrke.1.1.png", "airstrke.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/airstrke.1.2.png", "airstrke.1.2", this->getScreen().getRenderer());

		TextureManager::Instance().load("res/images/banana.1.1.png", "banana.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/banana.1.2.png", "banana.1.2", this->getScreen().getRenderer());

		TextureManager::Instance().load("res/images/hmissile.1.1.png", "hmissile.1.1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/hmissile.1.2.png", "hmissile.1.2", this->getScreen().getRenderer());


		//TODO: @Nahu: agrego la imagen que usas, despues la ponemos donde vos digas,
		TextureManager::Instance().load("res/images/arial.png", "arial", this->getScreen().getRenderer());

	} catch (GameException & e) 
	{
		Log::e(BOOT, e.what());		
	}
}