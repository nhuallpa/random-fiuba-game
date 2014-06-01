#include "SoundManager.h"


void SoundManager::init(){
	SDL_Init( SDL_INIT_AUDIO);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ); 
	this->music = Mix_LoadMUS("C:/random-fiuba-game/randomgame/sounds/audio_sfx/explosion1.wav");
	
}
void SoundManager::play(){
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
}