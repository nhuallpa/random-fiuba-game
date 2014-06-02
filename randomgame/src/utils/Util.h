#pragma once

#ifndef _UTIL_H_
#define _UTIL_H_

#include "ParserYaml.h"
#include <map>
#include <stdlib.h>

typedef std::string Player;

#define DYNAMITE_TIMEOUT 5
#define GRANADE_TIMEOUT 3

enum StateConn {CONNECTED, DISCONNECTED, RECONNECTED, WAITING_TURN};
enum GameState {STARTED, WAITING_PLAYERS, OVER, WIN};

typedef enum{
	NEW_PLAYER=0,
	EXISTING_PLAYER,
	PLAYER_NOT_ALLOWED,
	PLAYER_ALLOWED
} PlayerAccounting;



typedef enum{
	MOVE_RIGHT=0,
	MOVE_LEFT,
	JUMP,
	JUMP_LEFT,
	JUMP_RIGHT,
	INIT_PLACEMENT,
	MOVE_STOP,
	DEAD,
	WITH_WEAPON,
	NOT_CONNECTED,
	NOT_CONNECTED_LEFT,
	NOT_CONNECTED_RIGHT,
	MOVELESS,
	MOVELESS_RIGHT,
	MOVELESS_LEFT
} Movement;


typedef enum{
	YOUR_TURN=0,
	WAITING_FOR_TURN,
	TURN_OVER
} Turn;


typedef enum{
	BAZOOKA=2,
	GRANADE=4,
	HOLY=12,
	AIRATTACK=3,
	DYNAMITE=5
} Weapons;



//If action is WITH_WEAPON then X and Y means angle of weapon.
// - Dynamite X,Y drops at worm position.
// - Air Attack X,Y means center of where the air attack is going to be dropped

typedef struct {
		int wormid;			// Worm identifier, unique
		Movement action;	// der, izq, salt
		int state;			//selected or not
		//int weaponid;		
		float x;				// X,Y alreaded passed to view coords.
		float y;				//
		char level[15];		// YAML level (filename), path must be specified

} Playable;



struct s_point{
	int x;
	int y;
};
typedef struct s_point tPoint;

class Util
{
public:
	Util(void);
	~Util(void);


	/**
	* Valid int
	* @param number a string int
	* @return true if str has a integer. 
	*/
	static bool esUnsInt(std::string str);

	/**
	* Convert std::string to int
	* @param number a string int
	* @return int 
	*/
	static int string2int(std::string number);


	/**
	* @DEPRECATE !!!!!!!!!!!!!!!!!!!!!!!!!
	* Get the scale factor in both axis x and y
	* @return std::pair<float,float> a pair of scale factor
	*/
	static std::pair<float,float> getTransformFromU2PX();


	/**
	* Convert std::string to float
	* @param number a string float
	* @return float
	*/
	static float string2float(std::string number);

	/**
	* Convert std::string witch value could be "no" or "si" to bool type
	* @param  a string value "si" or "no"
	* @return true if sino has a "si"
	*/
	static bool string2bool(std::string sino);


	/**
	* Convert std::string witch value could be "no" or "si" to bool type
	* @param  a string value "si" or "no"
	* @return true if sino has a "si"
	*/
	static std::string int2string(int number);
	


	/**
	* * @DEPRECATE !!!!!!!!!!!!!!!!!!!!!!!!! or change
	* Convert a coordinate x y to coordinate in SDL system reference
	* @param x Value of axis x in domain
	* @param y Value of axis y in domain
	* @return aPoint in SLD system reference
	*/
	static tPoint convertPointUL2PXSDL(float x, float y);



	/**
	* Property loader
	* @param file
	* @return map that contains the properties retrived from file
	*/
	static std::map<std::string, std::string> Util::loadProperteries(std::string str);



	static int getRandom(int min, int max);

	static std::string actionString(Movement action);


};



#endif