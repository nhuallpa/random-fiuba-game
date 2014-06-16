#include "Camera.h"


Camera::Camera(void)
{
	this->box.w = 50;
	this->box.h = 50;
	this->box.x = 0;
	this->box.y = 0;
}

void Camera::setDimension(int w, int h) 
{
	this->box.w = w;
	this->box.h = h;
}
void Camera::setPosition(int x, int y)
{
	this->box.x = x;
	this->box.y = y;
}

void Camera::OnScroll(ScrollEvent e) {
	if ( (this->box.x + e.xSpeed) > 0 && 
		 (this->box.x + this->box.w + e.xSpeed) < this->getWidthScenario()) 
	{
		this->box.x += e.xSpeed;
	}
	
	if ( (this->box.y + e.ySpeed) > 0 &&
		(this->box.y + this->box.h + e.ySpeed) < this->getHeightScenario())
	{
		this->box.y += e.ySpeed;
	}
}

void Camera::setFocus(tFocus tipo, int dest_w, int dest_h)
{
	if (tipo == FOCUS_CENTER) {
		int xNew = (int)(((float)dest_w / 2) - ((float)this->getW() / 2));
		if (xNew<0) {
			xNew = 0;
		}
		int yNew = (int)(((float)dest_h / 2) - ((float)this->getH() / 2));
		if (yNew < 0) {
			yNew = 0;
		}
		this->setPosition(xNew, yNew);
	} 
	else if (tipo == FOCUS_BOTOOM_CENTER) 
	{
		int xNew = (int)(((float)dest_w / 2) - ((float)this->getW() / 2));
		if (xNew<0) {
			xNew = 0;
		}
		int yNew = dest_h  - this->getH();
		if (yNew < 0) {
			yNew = 0;
		}
		this->setPosition(xNew, yNew);
	}
}


Camera::~Camera(void)
{
}
