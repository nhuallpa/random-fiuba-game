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
	loadWaterImg();
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
			TextureManager::Instance().load("res/images/weapon/donkey.png", "donkey", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/FondoMensaje.png", "fondo_msg", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/poder.png", "poder", this->getScreen().getRenderer());
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
			//TextureManager::Instance().load(aParser->getEscenarioTierra(), "eart", this->getScreen().getRenderer(), true);
			TextureManager::Instance().loadStream(aParser->getEscenarioTierra(), "eart", this->getScreen().getRenderer());
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

			// projectiles

			TextureManager::Instance().load("res/images/weapon/clustlet.png", "bullet_default", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/weapon/airmisl.png", "bullet_airmisl", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/weapon/donkey.png", "bullet_donkey", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/weapon/dynamite.png", "bullet_dinamita", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/weapon/hgrenade.png", "bullet_holy", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/weapon/grenade.png", "bullet_granada", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/weapon/missile.png", "bullet_bazooka", this->getScreen().getRenderer());

			SpriteConfigurator::Instance().add("bullet_default", 60, 60, 6, true);
			SpriteConfigurator::Instance().add("bullet_airmisl", 60, 60, 32, true);
			//SpriteConfigurator::Instance().add("donkey", 60, 60, 32, true);  no es sprites
			SpriteConfigurator::Instance().add("bullet_dinamita", 60, 60, 129, true);
			SpriteConfigurator::Instance().add("bullet_holy", 60, 60, 32, true);
			SpriteConfigurator::Instance().add("bullet_granada", 60, 60, 32, true);
			SpriteConfigurator::Instance().add("bullet_bazooka", 60, 60, 32, true);




			// explosiones
			TextureManager::Instance().load("res/images/circle25.png", "circle25", this->getScreen().getRenderer());
			TextureManager::Instance().load("res/images/circle50.png", "circle50", this->getScreen().getRenderer());			
			TextureManager::Instance().load("res/images/circle75.png", "circle75", this->getScreen().getRenderer());			
			TextureManager::Instance().load("res/images/circle100.png", "circle100", this->getScreen().getRenderer());			
			SpriteConfigurator::Instance().add("circle25", 50, 50, 8, false);
			SpriteConfigurator::Instance().add("circle50", 100, 100, 8, false);
			SpriteConfigurator::Instance().add("circle75", 150, 150, 4, false);
			SpriteConfigurator::Instance().add("circle100", 200, 200, 4, false);

			
			// Nueves
			TextureManager::Instance().load("res/images/cloudm.png", "nuve", this->getScreen().getRenderer());
			SpriteConfigurator::Instance().add("nuve", 128, 128, 20, true);
			

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

void Bootstrap::loadWaterImg(){
	try{
		TextureManager::Instance().load("res/images/water/marea_1_1.png", "marea_1_1", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/water/marea_1_2.png", "marea_1_2", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/water/marea_1_3.png", "marea_1_3", this->getScreen().getRenderer());
		TextureManager::Instance().load("res/images/water/marea_1_4.png", "marea_1_4", this->getScreen().getRenderer());
	}
	catch (GameException & e){
		Log::e(BOOT, e.what());		
	}
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



		/*inicia el manejo del texto*/
		TextManager::Instance().init(this->getScreen().getRenderer());
		TextManager::Instance().loadFont(Arial16);
		TextManager::Instance().loadFont(Arial12);

	} catch (GameException & e) 
	{
		Log::e(BOOT, e.what());		
	}
}