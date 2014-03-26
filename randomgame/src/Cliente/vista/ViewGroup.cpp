#include "ViewGroup.h"


ViewGroup::ViewGroup(int x, int y, int width, int height)
								: View(x, y, width, height)
{
}


ViewGroup::~ViewGroup(void)
{
}

void ViewGroup::add(View* aView)
{
	this->views.push_back(aView);
}

void ViewGroup::clean()
{
	std::list<View*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->clean();
	}
}
	
void ViewGroup::update()
{
	std::list<View*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->update();
	}
}
	
void ViewGroup::draw(SDLScreen & screen)
{
	std::list<View*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->draw(screen);
	}
}
