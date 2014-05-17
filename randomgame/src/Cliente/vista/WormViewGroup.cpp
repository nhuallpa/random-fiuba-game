#include "WormViewGroup.h"


WormViewGroup::WormViewGroup(int x, int y)
								: View(x, y)
{

}

WormViewGroup::~WormViewGroup(void)
{
	std::list<WormView*>::iterator it;
	for (it = views.begin(); it != views.end(); ++it) 
	{
		delete (*it);
	}
	views.clear();
	mapWorms.clear();
}

void WormViewGroup::add(WormView* aView)
{
	this->views.push_back(aView);
	this->mapWorms[aView->getId()]=aView;
}

void WormViewGroup::update()
{
	std::list<WormView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->update();
	}
}

void WormViewGroup::clean()
{
	std::list<WormView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->clean();
	}
}
	
void WormViewGroup::draw(SDLScreen & screen)
{
	std::list<WormView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->draw(screen);
	}
}

WormView* WormViewGroup::findById(int idElement)
{
	if (mapWorms.find(idElement) != mapWorms.end())
	{
		return mapWorms[idElement];
	} 
	else 
	{
		std::stringstream msg;
		msg<<"WormView: not found view by id: "<<idElement;
		throw GameException(msg.str());
	}
}