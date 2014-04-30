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

Camera::~Camera(void)
{
}
