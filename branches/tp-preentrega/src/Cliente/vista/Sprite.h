#pragma once

#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <string>
class Sprite
{

	std::string imageId;
	int width;
	int height;
	int rows;
	int currentFrame;
	int currentRow;
	int sleepFrame;
	int countSleepFrame;

public:

	Sprite();

	/**
	* @param imageId			The image key stored in texture manager
	* @param width				Width of frame
	* @param height				Height of frame
	* @param rows				Count of rows in the sprite
	* @param countSleepFrame	Times to wait in each frame
	* 
	**/
	Sprite(std::string imageId, int width, int height, int rows, int countSleepFrame);

	Sprite(const Sprite & sprite);
									
	void clean();
	
	void update();

	~Sprite(void);

	void setImageId(std::string imageId) {this->imageId = imageId;}
	void setWidth(int width) {this->width = width;}
	void setHeight(int height) {this->height = height;}
	void setRows(int rows) {this->rows = rows;}
	void setCurrentFrame(int currentFrame) {this->currentFrame = currentFrame;}
	void setCurrentRow(int currentRow) {this->currentRow = currentRow;}
	void setSleepFrame(int sleepFrame) {this->sleepFrame = sleepFrame;}
	void setCountSleepFrame(int countSleepFrame) {this->countSleepFrame = countSleepFrame;}
	
	std::string getImageId() {return this->imageId;}
	int getWidth() {return this->width;}
	int getHeight() {return this->height;}
	int getRows() {return this->rows;}
	int getCurrentFrame() {return this->currentFrame;}
	int getCurrentRow() {return this->currentRow;}
	int getSleepFrame() {return this->sleepFrame;}
	int getCountSleepFrame() {return this->countSleepFrame;}
	
};



#endif /** __SPRITE_H__ **/