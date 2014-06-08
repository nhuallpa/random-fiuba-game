#ifndef __COORD__
#define __COORD__
#include <list>
#include "..\Contracts\OnCoordListener.h"
#include "CoordEvent.h"
#include "..\Contracts\Notifiable.h"

using namespace std;


class Coord : public Notifiable{
	public:
		static Coord* getInstance();
		void add(OnCoordListener * obj);
		void remuve(OnCoordListener * obj);
		void notify();
		void setEvent(int x, int y);
		bool newEvent();

	private:
		Coord(void);
		~Coord(void);
		static Coord* coord;
		list<OnCoordListener*> objects;
		int x, y;
		int xp, yp;
		bool isRegistered(OnCoordListener * obj);
};

#endif