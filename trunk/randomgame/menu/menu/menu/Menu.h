#pragma once
#include <iostream>
#include <string>



class Menu{

public:
	static Menu & Instance(){
			static Menu theMenu;
			return theMenu;
	}
	void printOptions();
	void selectYaml();
	void initGame();
	void stopGame();
	void resetGame();
};