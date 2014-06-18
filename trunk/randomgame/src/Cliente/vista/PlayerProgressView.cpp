#include "PlayerProgressView.h"


PlayerProgressView::PlayerProgressView(std::map<Player,int> * playersLife, std::map<Player,std::pair<StateConn,int>> * playersPlaying)
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
		rect.w = 0;
		rect.h = heightBarProgress - margin;

		int x = rect.x - 200;

		std::map<Player, std::pair < StateConn, int > >::iterator it;

		int indexPlayer = 0;
		for (it = this->refPlayersPlaying->begin(); it != this->refPlayersPlaying->end(); ++it)
		{
			Player aPlayer = it->first;
			std::pair<StateConn,int> value = it->second;

			rect.w = calcWidth((*this->refPlayersLife)[aPlayer]);
			rect.y = screen.getHeight() - (countOfPlayer - indexPlayer) * heightBarProgress; // apilar barras
			SDL_Color color = geColorTeam((TeamColors)value.second);
			SDL_SetRenderDrawColor(screen.getRenderer(), color.r, color.g, color.b, color.a); 
			SDL_RenderFillRect(screen.getRenderer(), &rect);
			indexPlayer++;

			labelUser.setText((std::string)aPlayer, geColorTeam((TeamColors)value.second));
			labelUser.draw(screen.getRenderer(), x, rect.y);
		}
}

SDL_Color PlayerProgressView::geColorTeam(TeamColors teamColor)
{
	SDL_Color color;
	if (teamColor == ARGENTINA) {
		color.r = 91;
		color.g = 192;
		color.b = 222;
		color.a = 255;
	} else if (teamColor == BRASIL) {
		color.r = 92;
		color.g = 184;
		color.b = 92;
		color.a = 255;
	} else if (teamColor == ALEMANIA) {
		color.r = 240;
		color.g = 173;
		color.b = 78;
		color.a = 255;
	} else if (teamColor == ESPANIA) {
		color.r = 217;
		color.g = 83;
		color.b = 79;
		color.a = 255;
	} else {
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;
	}
	return color;
}


int PlayerProgressView::calcWidth(int life) 
{
	int w=0;
	w = (int)((float)life / 4);

	if (w<0) {
		w = 0;
	}
	return  w;
}

