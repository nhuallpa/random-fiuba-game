#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "GameElement.h"
#include <list>



class GameLevel {
	private:

		//TODO @future - std::list<GamePlayer*> players;
		//TODO @future - Mutex jugadores;
		//TODO @future - Mutex game elements;

		int levelHeight;
		int levelWidth;
		std::multimap<std::pair<float, float>, GameElement> entities;
		GameElement getEntity(int id);

		void destroyPlayers();
		void destroyEntities();

	public:
		GameLevel();
		virtual ~GameLevel();

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

		std::multimap<std::pair<float, float>, GameElement> getEntities();
		void addEntity(GameElement entidad);
		void removeEntity(GameElement entidad);
		void entityUpdatePosition(int tileX, int tileY, int id);
		bool posicionOcupada(float x, float y);
		bool checkMapPosition(float x, float y);
};
