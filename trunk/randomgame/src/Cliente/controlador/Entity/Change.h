#ifndef __CHANGE__
#define __CHANGE__
#include <list>
#include "..\Contracts\OnChangeListener.h"
#include "ChangeEvent.h"
#include "..\Contracts\Notifiable.h"

using namespace std;


class Change : public Notifiable{
	public:
		static Change* getInstance();
		void add(OnChangeListener * obj);
		void remuve(OnChangeListener * obj);
		void notify();
		void setEvent(int x, int y);
		bool newEvent();

	private:
		Change(void);
		~Change(void);
		static Change* change;
		list<OnChangeListener*> objects;
		int x, y;
		int xp, yp;
		bool isRegistered(OnChangeListener * obj);
};

#endif