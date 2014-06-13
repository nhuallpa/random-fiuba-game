#ifndef __MOVEMENTEVENT__
#define __MOVEMENTEVENT__

enum MoveEvent {M_SHEDULE, M_ANTICLOCK};

class MovementEvent{
	public:
		MovementEvent(void);
		~MovementEvent(void);
		int x, y;
		MoveEvent me;
};

#endif
