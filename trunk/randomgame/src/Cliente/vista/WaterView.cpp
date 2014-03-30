#include "WaterView.h"


WaterView::WaterView(int height,std::string  color)
							: View(0, 0, color)
{
	this->setHeight(height);
}


WaterView::~WaterView(void)
{
}


void WaterView::draw(SDLScreen & screen)
{
	int x1=0;
	int y1=screen.getHeight() - this->getHeight();
	int x2 = screen.getWidth();
	int y2 = screen.getHeight();
	boxColor(screen.getRenderer(),
				x1, y1,
				x2, y2, this->getColorCod());
			
}

