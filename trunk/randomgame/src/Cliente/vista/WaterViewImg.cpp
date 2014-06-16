#include "WaterViewImg.h"
#include "TextureManager.h"


WaterViewImg* WaterViewImg::FactoryWater(){
	WaterViewImg* wvi = new WaterViewImg();
	wvi->loadWater();
	wvi->iniView();
	wvi->iniRender();
	return wvi;
}

WaterViewImg::WaterViewImg():View(30,30){

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



void WaterViewImg::loadWater(){
	int lebel, width, height;
	pair<int, int> dimension = TextureManager::Instance().getDimension("eart");
	width = dimension.first;
	height = dimension.second;

	int scale = ESCALA_UL2PX;
	lebel = (int)( Util::string2float(ParserYaml::getInstance()->getEscenarioAgua()) * scale);

	water.insert(pair<string,Shape>("marea_1_1", Shape(-10, height - lebel,	width, lebel)));
	water.insert(pair<string,Shape>("marea_1_2", Shape(-10, height - lebel,	width, lebel)));
	water.insert(pair<string,Shape>("marea_1_3", Shape(-10, height - lebel,	width, lebel)));
	water.insert(pair<string,Shape>("marea_1_4", Shape(-10, height - lebel,	width, lebel)));
}