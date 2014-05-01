#ifndef __MOVE__
#define __MOVE__
#include <list>
#include "../Contracts/OnMovementListener.h"
#include "MovementEvent.h"
#include "../Contracts/Notifiable.h"

using namespace std;


class Move : public Notifiable{
	public:
		static Move* getInstance();
		void add(OnMovementListener* obj);
		void remuve(OnMovementListener* obj);
		void notify();
		//void setEvent(int y);

	private:
		Move(void);
		~Move(void);
		static Move* move;
		list<OnMovementListener*> objects;
		//int y;
};

#endif
