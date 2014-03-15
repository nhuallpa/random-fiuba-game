
class Point {
	int x;
};

class Rect {
	int x;
};

class Display {
	int x;
};

class Event {
	int x;
};

enum Bool {false, true};

class Widget;

class Window {
public:
				PWindow		(Display&, Rect &bounds);
void			AddWidget	(Widget &obj);
void			SetTitle	(char *title);
void			GetTitle	(char *title);
virtual	void	Show		(Bool show);
virtual	void	Hilite		(Bool hilite);
virtual	Bool	HandleEvent	(Event &event);
virtual	void	Update		(void);
virtual	Bool	Close		(void);
virtual	Bool	Print		(void);
virtual	void	MoveTo		(int h, int v);
virtual	void	ResizeTo	(Rect &newBounds);
virtual	void	UpdateCursor(void);

protected:
		Display	*display;	// display to which window draws
		Rect	bounds;		// window boundary
		Window	*next;		// next window in the list
		Widget	*widgets;	// list of window's widgets

};

class Widget {
public:

				Widget		(Window&, Rect &bounds);
				
virtual	Bool	SetCursor	(Point &pt);
virtual	void	Idle		(void);
virtual void	Draw		(void);
virtual void	Show		(Bool show);
virtual Bool	HandleEvent	(Event &event);
virtual void	MoveBy		(int h, int v);
virtual	void	ResizeBy	(int h, int v);
virtual Bool	ResizeTo	(Rect &newBounds);
virtual	void	Dim			(Bool dim);
		void	Invalidate	(void);

protected:
		Window	*window;	// window to which it belongs
		Rect	bounds;		// Widget boundary
		Bool	dimmed;		// true if widget is dimmed
		Widget	*next;		// next object in the list
};

class Menu : public Window {

};