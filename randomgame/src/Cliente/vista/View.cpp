#include "View.h"


View::View(int x, int y, std::string  color)
{
	this->x = x;
	this->y = y;
	this->color = color;
}


void View::clean()
{
}

void View::update()
{
}

View::~View(void)
{
}

Uint32 View::getColorCod()
{
	Uint32 colorCode = 0;
	if (this->getColor().find_first_of("#") == 0) {
		std::string hex_color = this->getColor().substr(1);
		std::istringstream buffer(hex_color);
		buffer >> std::hex >> colorCode;
		swapEndian(&colorCode);
	}
	return colorCode;
}

void View::swapEndian(Uint32 *colorCode)
{
	*colorCode=(((*colorCode)&0x000000FF)<<24) | ((((*colorCode)&0x0000FF00)>>8)<<16) | \
		 ((((*colorCode)&0x00FF0000)>>16)<<8) | (((*colorCode)&0xFF000000)>>24);
}


