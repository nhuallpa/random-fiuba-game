#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_
#include <Box2D/Box2D.h>
#include <set>
#include <utility>

typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;

class ContactListener :  public b2ContactListener {
public:
	ContactListener();


	std::set<fixturePair> m_fixturePairs;
	virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
	virtual ~ContactListener();
private:

};
 
#endif /* CONTACTLISTENER_H_ */
