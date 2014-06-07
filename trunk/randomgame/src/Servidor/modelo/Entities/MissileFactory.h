
#ifndef MISSILEFACTORY_H_
#define MISSILEFACTORY_H_
#include "Missile.h"
#include "MissileBazooka.h"
#include "MissileGrenade.h"
#include "../../../utils/Util.h"
#include <iostream>

class MissileFactory{

private:
	MissileFactory();
	static MissileFactory* pInstance;
public:
	~MissileFactory();
	static MissileFactory* getInstance();
	Missile* getMissile(int weaponId, int elementId);

};

#endif