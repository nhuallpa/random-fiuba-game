#ifndef __ACTION__
#define __ACTION__
#include <list>
#include "..\Contracts\OnActionListener.h"
#include "ActionEvent.h"
#include "..\Contracts\Notifiable.h"

using namespace std;


class Action : public Notifiable{
	public:
		static Action* getInstance();
		void add(OnActionListener * obj);
		void remuve(OnActionListener * obj);
		void notify();
		void setEvent(ActionKey a);
		void setLastEvent(ActionKey a);
		bool newEvent();

	private:
		Action(void);
		~Action(void);
		static Action* action;
		list<OnActionListener*> objects;
		ActionKey a, last;
};

#endif