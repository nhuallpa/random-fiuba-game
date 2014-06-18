#include "PlayerProgressView.h"


PlayerProgressView::PlayerProgressView(std::map<Player,int>* playersLife, std::map<Player,std::pair<StateConn,int>>* playersPlaying)
	: View(0, 0), refPlayersLife(playersLife), refPlayersPlaying(playersPlaying)
{

}


PlayerProgressView::~PlayerProgressView(void)
{
}

void PlayerProgressView::update()
{

}


void PlayerProgressView::clean()
{

}

void PlayerProgressView::draw(SDLScreen & screen){
	
		int margin = 5;
		int countOfPlayer = 5;
		int heightBarProgress = 15;
		SDL_Rect rect;
		rect.x = screen.getWidth() / 2;
		rect.y = screen.getHeight() - countOfPlayer * heightBarProgress;
		rect.w = 100;
		rect.h = heightBarProgress - margin;

		TextureManager::Instance().drawBox(screen.getRenderer(), 
														rect.x, 
														rect.y, 
														rect.x + rect.w,
														rect.y + rect.h, 
														COLOR_ROJO_ALFA);
		rect.y = screen.getHeight() - (countOfPlayer - 1) * heightBarProgress;
		TextureManager::Instance().drawBox(screen.getRenderer(), 
														rect.x, 
														rect.y, 
														rect.x + rect.w,
														rect.y + rect.h, 
														COLOR_AMARILLO_ALFA);

		rect.y = screen.getHeight() - (countOfPlayer - 2) * heightBarProgress;
		TextureManager::Instance().drawBox(screen.getRenderer(), 
														rect.x, 
														rect.y, 
														rect.x + rect.w,
														rect.y + rect.h, 
														COLOR_VERDE_ALFA);

		rect.y = screen.getHeight() - (countOfPlayer - 3) * heightBarProgress;
		TextureManager::Instance().drawBox(screen.getRenderer(), 
														rect.x, 
														rect.y, 
														rect.x + rect.w,
														rect.y + rect.h, 
														COLOR_AZUL_ALFA);
}