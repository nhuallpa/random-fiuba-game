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
	WITH_WEAPON,			/* DEPRECATED */
	WITH_WEAPON_LEFT,		/* Apuntando hacia la izquierda */
	WITH_WEAPON_RIGHT,		/* Apuntando hacia la derecha */
	DO_SHOOT,				/* Disparo */
	NOT_CONNECTED,
	NOT_CONNECTED_LEFT,
	NOT_CONNECTED_RIGHT,
	MOVELESS,
	MOVELESS_RIGHT,
	MOVELESS_LEFT,
	YOUR_TURN,
	TURN_OVER,
	EXPLOSION				/* X e Y tienen el radio de la explosion en este caso */
} Movement;


typedef enum{
	PLAYING_TURN=0,
	WAITING_FOR_TURN
} Turn;


typedef enum{
	NO_WEAPON=0,
	BAZOOKA=2,
	GRANADE=4,
	HOLY=12,
	AIRATTACK=3,
	DYNAMITE=5
} WeaponId;



//If action is WITH_WEAPON then X and Y means angle of weapon.
// - Dynamite X,Y drops at worm position.
// - Air Attack X,Y means center of where the air attack is going to be dropped

typedef struct {
		int wormid;			// Worm identifier, unique
		Movement action;	// der, izq, salt
		int life;			// Worm health
		int weaponid;		// Worm Weapon elected
		float x;			// X coord
		float y;			// Y coord
		char level[15];		// YAML level (filename), path must be specified

} Playable;


typedef struct{
	float x;
	float y;
	int radio;	/* El arma define el radio */
} Explosion;


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