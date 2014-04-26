#ifndef __MOVEMENTEVENT__
#define __MOVEMENTEVENT__

enum Move {M_LEFT, 
	       M_RIGHT, 
		   M_UP,
		   M_UPLEFTDIAG,
		   M_UPRIGHTDIAG};

class MovementEvent{
	public:
		MovementEvent(void);
		~MovementEvent(void);
		Move move;
};

#endif
