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
		 eEXPLOSION2,
		 eEXPLOSION3,
		 eAIRSTRIKE,
		 eHOLYGRENADE,
		 eKAMIKAZE,
		 eCOMMUNICATOR,

         };

class SoundManager
{
private:

	

	Mix_Chunk* fxEXPLOSION1;
	Mix_Chunk* fxFIREPUNCHIMPACT;
	Mix_Chunk* fxOUCH;
	Mix_Chunk* fxBYEBYE;

	Mix_Chunk* fxEXPLOSION2;
	Mix_Chunk* fxEXPLOSION3;
	Mix_Chunk* fxAIRSTRIKE;
	Mix_Chunk* fxHOLYGRENADE;
	Mix_Chunk* fxKAMIKAZE;
	Mix_Chunk* fxCOMMUNICATOR;


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
	
	void pEXPLOSION2();
	void pEXPLOSION3();
	void pAIRSTRIKE();
	void pHOLYGRENADE();
	void pKAMIKAZE();
	void pCOMMUNICATOR();



};



#endif /* defined(__SOUND_MANAGER__) */