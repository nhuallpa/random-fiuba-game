#ifndef __ACTIONEVENT__
#define __ACTIONEVENT__

enum ActionKey{SHOOT, MENU};
class ActionEvent{
	public:
		ActionEvent(void);
		~ActionEvent(void);
		ActionKey action;
};

#endif
