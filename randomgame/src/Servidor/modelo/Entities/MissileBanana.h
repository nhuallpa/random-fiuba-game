
#ifndef MISSILEBANANA_H_
#define MISSILEBANANA_H_
#include "Missile.h"
#include <iostream>

class MissileBanana: public Missile{

	public:
		MissileBanana();
		~MissileBanana();
		MissileBanana(int id);
};

#endif