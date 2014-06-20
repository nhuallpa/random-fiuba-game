#include "Camera.h"


Camera::Camera(void)
{
	this->box.w = 50;
	this->box.h = 50;
	this->box.x = 0;
	this->box.y = 0;
	this->scale = 1.0f;
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
	Log::d("Camera::OnScroll CENTER on x: %d Y:%d", this->box.x, this->box.y);
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
		Log::d("Camera::setFocus CENTER on x: %d Y:%d", xNew, yNew);
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
		Log::d("Camera::setFocus FOCUS_BOTOOM_CENTER on x: %d Y:%d", xNew, yNew);
	}
	
}


Camera::~Camera(void)
{
}


void Camera::OnZoom(ZoomEvent e)
{
	Log::d(" Camara Zoom ");
	SDL_Rect newViewPort;
	float nextScale = this->scale + (0.01 * e.y);
	if (nextScale > 0.5 && nextScale <= 3) 
	{
		int w_new = (int)(700.0f * 1/nextScale);   // nuevo ancho manual
		int h_new = (int)(400.0f * 1/nextScale);   // nuevo alto manual
		newViewPort.w = w_new;
		newViewPort.h = h_new;
		Log::t(" Camara view port ancho: %d		alto: %d  scale: %f", newViewPort.w, newViewPort.h, nextScale);
		

		int camaraBootom = newViewPort.h + this->getY();
		int camaraRight = newViewPort.w + this->getX();
		if (camaraBootom <= this->getHeightScenario() &&
			camaraRight <= this->getWidthScenario())
		{
			this->setH(newViewPort.h);
			this->setW(newViewPort.w);
			this->scale = nextScale;
		}
	}	
}