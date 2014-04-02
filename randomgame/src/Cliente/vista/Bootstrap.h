#pragma once

#ifndef __BOOTSTRAP_H_
#define __BOOTSTRAP_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SDLScreen.h"
#include "TextureManager.h"
#include "../../utils/ParserYaml.h"
class Bootstrap
{
private:
	SDLScreen screen;

public:
	Bootstrap(void);

	/**Inicialize enviroment*/
	void init();

	SDLScreen & getScreen();
	
	~Bootstrap(void);
};

#endif /* defined(__BOOTSTRAP_H_) */