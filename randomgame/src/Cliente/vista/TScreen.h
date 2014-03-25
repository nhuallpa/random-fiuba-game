#pragma once

#ifndef __T_SCREEN_H_
#define __T_SCREEN_H_

class TScreen
{
public:
	TScreen(void);

	/*** Inicialize the screen*/
	virtual bool init(const char* title, int xpos, int ypos, int width,
			int height, int flags) = 0;
	/*** Clear the screen*/
	virtual void clear() = 0;
	/*** Apply render to screen*/
	virtual void render() = 0;
	/*** Shut down screen*/
	virtual void terminate() = 0;

	~TScreen(void);
};

#endif /* defined(__T_SCREEN_H_) */