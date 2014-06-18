#include "Menu.h"


void Menu::printOptions(){
	char option;
	std::cout << "<y> Seleccionar YAML\n";
	std::cout << "<i> Seleccionar INICIAR JUEGO\n";
	std::cout << "<s> Seleccionar DETENET JUEGO\n";
	std::cout << "<r> Seleccionar REINICIAR JUEGO\n";
	
	std::cin >> option;
	switch (option){
		case 'y':this->selectYaml();break;
		case 'i':this->initGame();break; 
		case 's':this->stopGame();break; 
		case 'r':this->resetGame();break;
		default: std::cout << "Opcion Incorrecta\n";
	}
	
}
void Menu::selectYaml(){
	std::cout << "Ingrese el directorio del archivo YAML\n";

	std::string mystr;
	getline (std::cin, mystr);
	std::cout << "YAML:" << mystr << "\n";

}
void Menu::initGame(){
	std::cout << "JUEGO INICIADO\n";
}
void Menu::stopGame(){
	std::cout << "JUEGO DETENIDO\n";
}
void Menu::resetGame(){
	std::cout << "JUEGO REINICIADO\n";
}