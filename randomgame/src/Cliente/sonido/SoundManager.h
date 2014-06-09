#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__
#include <SDL_mixer.h>
#include "../../utils/Constantes/Constantes.h"
#include <map>
#include <SDL.h>
#include "../../utils/Log.h"

enum FX {eEXPLOSION1,
         eFIREPUNCHIMPACT,
         eOUCH,
         eBYEBYE,
         };

class SoundManager
{
private:

	

	Mix_Chunk* fxEXPLOSION1;
	Mix_Chunk* fxFIREPUNCHIMPACT;
	Mix_Chunk* fxOUCH;
	Mix_Chunk* fxBYEBYE;

	Mix_Music* music;

	void playFX(FX);

public:

	static SoundManager & Instance(){
			static SoundManager theSoundManager;
			return theSoundManager;
	}

	void init();

	

	void close();

	/*musica de fondo*/
	void playMusic();

	/*FX*/
	void pEXPLOSION1();
	void pFIREPUNCHIMPACT();
	void pOUCH();
	void pBYEBYE();


};



#endif /* defined(__SOUND_MANAGER__) */