#ifndef __ONMOVEMENTLISTENER__
#define __ONMOVEMENTLISTENER__

#include "..\Entity\MovementEvent.h"

class OnMovementListener{
	public:
		virtual ~OnMovementListener() {}
		virtual void OnMovement(MovementEvent e) = 0;
};

#endif


