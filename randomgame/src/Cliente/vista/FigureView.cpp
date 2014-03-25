#include "FigureView.h"


FigureView::FigureView(std::string imageId, int x, int y, int width, int height)
									: View(x, y, width, height), imageId(imageId)
{

}


FigureView::~FigureView(void)
{

}

void FigureView::clean()
{

}
	
void FigureView::update() 
{

}

void FigureView::draw(SDLScreen & screen)
{
	TextureManager::Instance().draw("cuadrado",
								this->getX(),
								this->getY(),
								this->getWidth(),
								this->getHeight(), screen.getRenderer());

}