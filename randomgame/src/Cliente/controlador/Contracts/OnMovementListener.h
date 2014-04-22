#ifndef __ONMOVEMENTLISTENER__
#define __ONMOVEMENTLISTENER__

#include "..\Entity\MovementEvent.h"

class Contract{
	public:
		void OnMovement(MovementEvent e) = 0;
};

#endif


