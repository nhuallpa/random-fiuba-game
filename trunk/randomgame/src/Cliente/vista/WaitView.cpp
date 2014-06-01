#include "WaitView.h"


WaitView::WaitView(std::string imageId)
				: View(0, 0), imageId(imageId)
{
}


WaitView::~WaitView(void)
{
}


void WaitView::clean()
{

}
	
void WaitView::update() 
{

}

void WaitView::draw(SDLScreen & screen)
{
	TextureManager::Instance().drawBackground(imageId.c_str(),
								screen.getRenderer());



	this->text.draw(screen.getRenderer(), 250,300,0, -4.2);

}

void WaitView::setMessage(std::string msg)
{
	SDL_Color color;
	color.a = 0xFF;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	this->text.setText(msg, color);
}
