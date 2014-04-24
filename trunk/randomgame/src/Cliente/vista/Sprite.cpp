#include "Sprite.h"


Sprite::Sprite()
	:imageId(""), width(0), height(0), rows(0), countSleepFrame(0)
	,currentFrame(0), currentRow(0), sleepFrame(0)
{

}

Sprite::Sprite(std::string imageId, int width, int height, int rows, int countSleepFrame)
					:imageId(imageId), width(width), height(height), rows(rows), countSleepFrame(countSleepFrame)
					 ,currentFrame(0), currentRow(0), sleepFrame(0)
{
}

Sprite::Sprite(const Sprite & sprite)
	:imageId(sprite.imageId), width(sprite.width), 
	 height(sprite.height), rows(sprite.rows), 
	 countSleepFrame(sprite.countSleepFrame),
	 currentFrame(sprite.currentFrame), currentRow(sprite.currentRow), sleepFrame(sprite.sleepFrame)
		
{
}


Sprite::~Sprite(void)
{
}


void Sprite::clean()
{
	this->currentFrame=0;
	this->currentRow=0;
	this->sleepFrame=0;
}
	
void Sprite::update() 
{
	if (sleepFrame < countSleepFrame ) 
	{
		sleepFrame++;
	}
	else 
	{
		this->currentRow++;
		if (this->currentRow >= this->rows) 
		{
			this->currentRow = 0;
		}
		sleepFrame = 0;
	}
}
