#include <iostream>
#include "Menu.h"


int main(int argc, char* argv[]) {
	while(1)
		Menu::Instance().printOptions();
	//std::cout << "hola";

	return 0;
}