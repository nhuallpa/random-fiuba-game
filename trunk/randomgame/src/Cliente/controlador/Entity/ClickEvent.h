#ifndef __CLICKEVENT__
#define __CLICKEVENT__

enum Click {CLICK_LEFT,
            CLICK_RIGHT};

class ClickEvent{
	public:
		ClickEvent(void);
		~ClickEvent(void);
		int x, y;
		Click click;
};

#endif
