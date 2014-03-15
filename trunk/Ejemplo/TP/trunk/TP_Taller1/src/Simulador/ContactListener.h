/*
 * ContactListener.h
 *
 *  Created on: Nov 20, 2013
 *      Author: lucia
 */

#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_
#include <Box2D/Box2D.h>

namespace simulador {

class ContactListener :  public b2ContactListener {
public:
	ContactListener();
	void BeginContact(b2Contact* contact);
	virtual ~ContactListener();
private:
	void resolverContactosHuevo(b2Contact* contact);
};

} /* namespace simulador */
#endif /* CONTACTLISTENER_H_ */
