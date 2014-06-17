#include "WaterViewImg.h"
#include "TextureManager.h"


WaterViewImg* WaterViewImg::FactoryWater(int Gap, float timmerChange,bool bBackground){
	WaterViewImg* wvi = new WaterViewImg(timmerChange, bBackground);
	wvi->loadWater(Gap);
	wvi->iniView();
	wvi->iniRender();
	return wvi;
}


WaterViewImg::WaterViewImg(float timmerChange, bool bBackground):View(30,30){
	this->timmerChange = timmerChange;
	this->bBackground = bBackground;
}

WaterViewImg::~WaterViewImg(){

}

void WaterViewImg::iniView(){
	this->it = water.begin();
}

void WaterViewImg::actionWater(){

}
void WaterViewImg::iniRender(){
	this->timer.start();
	bRender = true;
}

void WaterViewImg::controlRender(){
	float seg = timer.elapsed();
	if(seg > 0.5){
		this->iniRender();
	}
}

void WaterViewImg::draw(SDLScreen & screen){
	if(bBackground){
		this->drawbackground(screen);
	}
	this->drawSurf(screen);
}

void WaterViewImg::drawSurf(SDLScreen & screen){
	if(bRender){
		it++;
		if(it == water.end()){
			this->iniView();
		}
		bRender = false;
	}
	else{
		this->controlRender();
	}
	pair<int, int> point = it->second.getPosition();
	pair<int, int> dimen = it->second.getDimension();

	TextureManager::Instance().drawFrame(
		it->first, point.first, point.second,
		dimen.first, dimen.second, 
			0, 0, screen.getRenderer(),
			false, SDL_FLIP_NONE);
}


void WaterViewImg::drawbackground(SDLScreen & screen){
	pair<int, int> point = backgroundWater.second.getPosition();
	pair<int, int> dimen = backgroundWater.second.getDimension();
	TextureManager::Instance().drawFrame(
		backgroundWater.first, point.first, point.second,
		dimen.first, dimen.second, 
			0, 0, screen.getRenderer(),
			false, SDL_FLIP_NONE);
}

void WaterViewImg::loadWater(int Gap){
	int lebel, width, height;
	pair<int, int> dimension = TextureManager::Instance().getDimension("eart");
	width = dimension.first;
	//height = dimension.second; 
	height = Util::string2int(ParserYaml::getInstance()->getEscenarioAltoP());

	int scale = ESCALA_UL2PX;
	lebel = (int)( Util::string2float(ParserYaml::getInstance()->getEscenarioAgua()) * scale);

	water.insert(pair<string,Shape>("marea_1_1", Shape(-10, height - lebel - Gap, width, 80)));
	water.insert(pair<string,Shape>("marea_1_2", Shape(-10, height - lebel - Gap, width, 80)));
	water.insert(pair<string,Shape>("marea_1_3", Shape(-10, height - lebel - Gap, width, 80)));
	water.insert(pair<string,Shape>("marea_1_4", Shape(-10, height - lebel - Gap, width, 80)));

	backgroundWater = pair<string,Shape>("FondoAgua", Shape(-10, height - lebel + 10, width, height));
}