#include "FigureView.h"


FigureView::FigureView(int x, int y, Uint32 color, int rotation) : View(x, y, color)
{
	this->mRotation = rotation;
}


FigureView::~FigureView(void)
{

}
