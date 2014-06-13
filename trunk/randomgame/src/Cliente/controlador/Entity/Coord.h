#ifndef __COORD__
#define __COORD__
#include <list>
#include "..\Contracts\OnChangeListener.h"
#include "ChangeEvent.h"
#include "..\Contracts\Notifiable.h"

using namespace std;


class Coord : public Notifiable{
	public:
		static Coord* getInstance();
		void add(OnChangeListener * obj);
		void remuve(OnChangeListener * obj);
		void notify();
		void setEvent(int x, int y);
		bool newEvent();

	private:
		Coord(void);
		~Coord(void);
		static Coord* coord;
		list<OnChangeListener*> objects;
		int x, y;
		int xp, yp;
		bool isRegistered(OnChangeListener * obj);
};

#endif