#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__
#include <SDL_mixer.h>
#include "../../utils/Constantes/Constantes.h"
#include <map>
#include <SDL.h>

class SoundManager
{
private:

		
	// Contains all fx sounds
	std::map<std::string, Mix_Chunk*> fx_map;

	Mix_Music* music;

public:

	static SoundManager & Instance(){
			static SoundManager theSoundManager;
			return theSoundManager;
	}

	void init();

	void play();

	void close();

};



#endif /* defined(__SOUND_MANAGER__) */