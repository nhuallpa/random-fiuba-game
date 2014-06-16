#pragma once

#ifndef __DONKEY_VIEW_H__
#define __DONKEY_VIEW_H__

#include "..\ProjectileView.h"


class DonkeyView: public ProjectileView
{

private:
	std::string imageId;

public:
	DonkeyView(int id, std::string imageId);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~DonkeyView(void);

};

#endif /** __DONKEY_VIEW_H__ **/