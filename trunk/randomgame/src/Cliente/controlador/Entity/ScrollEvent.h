#ifndef __SCROLLEVENT__
#define __SCROLLEVENT__

/*
 QUADRANT

 +-+----------------------------------+-+
 |1|                5                 |2|
 +-+----------------------------------+-+
 | |                                  | |
 | |                                  | |
 |7|                9                 |8|
 | |                                  | |
 | |                                  | |
 +-+----------------------------------+-+
 |3|                6                 |4|
 +-+----------------------------------+-+
*/
enum Scroll {S_QUADRANT_1, 
			 S_QUADRANT_2, 
			 S_QUADRANT_3, 
			 S_QUADRANT_4,
			 S_QUADRANT_5,
			 S_QUADRANT_6,
			 S_QUADRANT_7,
			 S_QUADRANT_8,
			 S_QUADRANT_9}; // STOP SCROLL

class ScrollEvent{
	public:
		ScrollEvent(void);
		~ScrollEvent(void);
};

#endif
