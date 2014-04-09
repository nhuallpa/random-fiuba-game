#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "GameElement.h"
#include <list>
#include "../../utils/ParserYaml.h"
#include "../../utils/PersistYaml.h"
//#include "../../utils/utils.h"


class GameLevel {
	private:

		//TODO @future - std::list<GamePlayer*> players;
		//TODO @future - Mutex jugadores;
		//TODO @future - Mutex game elements;

		int levelHeight;
		int levelWidth;
		float waterLevel;

		//ToDo @aliguo ID, map de gameelements
		std::map<int,GameElement> modelElements;
		std::map<int, GameElement*> entities;

		GameElement getEntity(int id);

		void destroyPlayers();


	public:
		GameLevel();
		virtual ~GameLevel();

		void destroyEntities();

		//Creates the level based on YAML parser data
		bool createLevel(GameLevel&);

		// Getters
		int getHeight();
		int getWidth();

		// Setters
		void setHeight(int h);
		void setWidth(int w);

		//TODO @future - void removePlayer(GamePlayer *jugador);
		//TODO @future - void addPlayer(GamePlayer *jugador);

		// ESTE NO VA 
		std::map<int,GameElement> getModelElements();

		std::map<int, GameElement*> getEntities();

		void addEntity(GameElement *entidad);

		void removeEntity(int id);

		//void entityUpdatePosition(int tileX, int tileY, int id);
		bool posicionOcupada(float x, float y);

		bool checkMapPosition(float x, float y);

};
