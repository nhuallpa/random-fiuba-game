#include "WaitActivity.h"


WaitActivity::WaitActivity(SDLScreen & screen):Activity(screen)
{
	waitView = new WaitView("waitting");
	
	ViewGroup* viewGroup = new ViewGroup(0, 0, screen.getWidth(), screen.getHeight());
	viewGroup->add(waitView);
	this->setContentView(viewGroup);
}

WaitActivity::~WaitActivity(void)
{
	delete this->aView;
}

void WaitActivity::stop()
{
}

void WaitActivity::clear()
{
}

void WaitActivity::update()
{
}

void WaitActivity::setMessageView(std::string msg)
{
	waitView->setMessage(msg);
}

void WaitActivity::showMessageError(std::string msg)
{
	waitView->setMessage(msg);
}

void WaitActivity::showMessageInfo(std::string msg)
{
	waitView->setMessage(msg);
}


