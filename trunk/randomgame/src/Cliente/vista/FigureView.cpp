#include "FigureView.h"


FigureView::FigureView(std::string imageId, int x, int y)
									: View(x, y, 0, 0), imageId(imageId)
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
	/*TextureManager::Instance().draw(this->imageId,
								this->getX(),
								this->getY(),
								screen.getRenderer());
*/
	

}