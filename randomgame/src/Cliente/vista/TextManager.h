#ifndef __TEXT_MANAGER__
#define __TEXT_MANAGER__
#include <SDL_mixer.h>
#include "../../utils/Constantes/Constantes.h"
#include <map>
#include <SDL.h>
#include "../../utils/Log.h"
#include "TextureManager.h"

class TextManager{
private:
	SDL_Renderer * renderer;
	struct stFont{
		std::string idFont;
		int ancho, alto;
		int anchoLetra, altoLetra;
	};
	std::map<std::string, stFont> font_map;
	stFont font;
public:

	static TextManager & Instance(){
			static TextManager theTextManager;
			return theTextManager;
	}

	void init(SDL_Renderer * renderer);
	void loadFont(std::string path,std::string idFont,int h,int w,int letterH,int letterW);
	void wLetter(std::string idFont,int x, int y, char lett);




};




#endif /* defined(__TEXT_MANAGER__) */