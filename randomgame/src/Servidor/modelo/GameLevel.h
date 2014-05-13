#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "GameElement.h"
#include <list>
#include "../../utils/ParserYaml.h"
#include "../../utils/PersistYaml.h"
#include "../../utils/Util.h"
#include "TerrainProcessor.h"
//#include "../../utils/utils.h"
#include "GamePlayer.h"
#include "Exceptions\PlayerException.h"

using namespace server_model_exp;

class GameLevel {
	private:

		std::map<string, GamePlayer*> players;//TODO @future - std::list<GamePlayer*> players;
		int amountUser;//TODO @future - Mutex jugadores;
		int amountWorms;
		int idUnique;
		

		void addUserIntoLevel(string user)
			throw(PlayerExp);
		
		//TODO @future - Mutex game elements;

		int levelHeight;
		int levelWidth;
		float waterLevel;

		//ToDo @aliguo ID, map de gameelements
		std::map<int,GameElement> modelElements;
		std::map<int, GameElement*> entities;
		TerrainProcessor* aTerrainProcessor;
		GameElement getEntity(int id);

		bool validElementPosition(int id);
		void destroyPlayers();


	public:
		GameLevel();
		virtual ~GameLevel();

		void destroyEntities();
		void updateElementPosition(int pos, int id, float x, float y, float angle);

		//Creates the level based on YAML parser data
		bool createLevel(GameLevel*);

		// Getters
		int getHeight();
		int getWidth();
		TerrainProcessor* getTerrain();

		// Setters
		void setHeight(int h);
		void setWidth(int w);
		void setTerrain(TerrainProcessor* aTerrainProcessor);

		//TODO @future - void removePlayer(GamePlayer *jugador);
		void addPlayer(string user, GamePlayer *pg);//TODO @future - void addPlayer(GamePlayer *jugador);
		GamePlayer *getPlayer(string user);
		// ESTE NO VA 
		std::map<int,GameElement> getModelElements();

		std::map<int, GameElement*> getEntities();

		void addEntity(GameElement *entidad);

		void removeEntity(int id);

		void setWaterLevel(float waterLevel){ this->waterLevel = waterLevel;};
		float getWaterLevel(){ return this->waterLevel;};


		//void entityUpdatePosition(int tileX, int tileY, int id);
		bool posicionOcupada(float x, float y);

		bool checkMapPosition(float x, float y);

		bool acceptPlayer(std::string playerID);

		void disconnectPlayer(std::string playerID);
		StateConn getPlayerStatus(std::string playerId);

};
