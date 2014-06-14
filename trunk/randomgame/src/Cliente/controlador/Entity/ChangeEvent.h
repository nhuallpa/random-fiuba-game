#ifndef __CHANGEEVENT__
#define __CHANGEEVENT__



class ChangeEvent{
	public:
		ChangeEvent(void);
		~ChangeEvent(void);
		int x, y;
		int factor;
		bool stateBar,
			 coordenate;
		void setFactor(int factor);
		void setStateBar(bool stateBar);
		void setCoordenate(bool coordenate);
		bool isStateBar();
		bool isCoordenate();
};

#endif
