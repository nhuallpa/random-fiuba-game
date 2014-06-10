#include "SoundManager.h"


void SoundManager::init(){
	//SDL_Init( SDL_INIT_AUDIO);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ); 


	this->music = Mix_LoadMUS(MUSICAFONDO);
	this->fxEXPLOSION1 =  Mix_LoadWAV(EXPLOSION1);
	this->fxFIREPUNCHIMPACT =  Mix_LoadWAV(FIREPUNCHIMPACT);
	this->fxOUCH =  Mix_LoadWAV(OUCH);
	this->fxBYEBYE =  Mix_LoadWAV(BYEBYE);

	if (this->music == NULL) Log::i(SOUND,"Error al cargar %s",MUSICAFONDO);
	if (this->fxEXPLOSION1 == NULL) Log::i(SOUND,"Error al cargar %s",EXPLOSION1);
	if (this->fxFIREPUNCHIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",FIREPUNCHIMPACT);
	if (this->fxOUCH == NULL) Log::i(SOUND,"Error al cargar %s",OUCH);
	if (this->fxBYEBYE == NULL) Log::i(SOUND,"Error al cargar %s",BYEBYE);
	if (this->fxEXPLOSION2 == NULL) Log::i(SOUND,"Error al cargar %s",EXPLOSION2);
	if (this->fxEXPLOSION3 == NULL) Log::i(SOUND,"Error al cargar %s",EXPLOSION3);
	if (this->fxAIRSTRIKE == NULL) Log::i(SOUND,"Error al cargar %s",AIRSTRIKE);
	if (this->fxHOLYGRENADE == NULL) Log::i(SOUND,"Error al cargar %s",HOLYGRENADE);
	if (this->fxKAMIKAZE == NULL) Log::i(SOUND,"Error al cargar %s",KAMIKAZE);
	if (this->fxCOMMUNICATOR == NULL) Log::i(SOUND,"Error al cargar %s",COMMUNICATOR);
}

void SoundManager::playMusic(){
	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		Mix_PlayMusic( this->music, -1 );
	}
	//If music is being played
	else
	{
		//If the music is paused
		if( Mix_PausedMusic() == 1 )
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}
void SoundManager::close(){
	Mix_FreeMusic( this->music );
	Mix_FreeChunk(this->fxEXPLOSION1);
	Mix_FreeChunk(this->fxFIREPUNCHIMPACT);
	Mix_FreeChunk(this->fxOUCH);
	Mix_FreeChunk(this->fxBYEBYE);
	Mix_FreeChunk(this->fxEXPLOSION2);
	Mix_FreeChunk(this->fxEXPLOSION3);
	Mix_FreeChunk(this->fxAIRSTRIKE);
	Mix_FreeChunk(this->fxHOLYGRENADE);
	Mix_FreeChunk(this->fxKAMIKAZE);
	Mix_FreeChunk(this->fxCOMMUNICATOR);

	Mix_Quit();
}

void SoundManager::playFX(FX i){
	
	Mix_Chunk *fx;

	switch(i){
		case eEXPLOSION1:fx=this->fxEXPLOSION1;break;
		case eFIREPUNCHIMPACT:fx=this->fxFIREPUNCHIMPACT;break;
		case eOUCH:fx=this->fxOUCH;break;
		case eBYEBYE:fx=this->fxBYEBYE;break;	
		case eEXPLOSION2:fx=this->fxEXPLOSION2;break;
		case eEXPLOSION3:fx=this->fxEXPLOSION3;break;
		case eAIRSTRIKE:fx=this->fxAIRSTRIKE;break;
		case eHOLYGRENADE:fx=this->fxHOLYGRENADE;break;
		case eKAMIKAZE:fx=this->fxKAMIKAZE;break;
		case eCOMMUNICATOR:fx=this->fxCOMMUNICATOR;break;
	}
	Mix_PlayChannel(-1,fx,0);

}
void SoundManager::pEXPLOSION1(){
	this->playFX(eEXPLOSION1);

}

void SoundManager::pFIREPUNCHIMPACT(){
	 this->playFX(eFIREPUNCHIMPACT);
}

void SoundManager::pOUCH(){
	 this->playFX(eOUCH);
}

void SoundManager::pBYEBYE(){
	 this->playFX(eBYEBYE);
}

void SoundManager::pEXPLOSION2(){
	 this->playFX(eEXPLOSION2);
}

void SoundManager::pEXPLOSION3(){
	 this->playFX(eEXPLOSION3);
}
void SoundManager::pAIRSTRIKE(){
	 this->playFX(eAIRSTRIKE);
}
void SoundManager::pHOLYGRENADE(){
	 this->playFX(eHOLYGRENADE);
}
void SoundManager::pKAMIKAZE(){
	 this->playFX(eKAMIKAZE);
}
void SoundManager::pCOMMUNICATOR(){
	 this->playFX(eCOMMUNICATOR);
}