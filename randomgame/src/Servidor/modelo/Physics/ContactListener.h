#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_
#include <Box2D/Box2D.h>

class ContactListener :  public b2ContactListener {
public:
	ContactListener();
	void BeginContact(b2Contact* contact);
	virtual ~ContactListener();
};
 
#endif /* CONTACTLISTENER_H_ */
