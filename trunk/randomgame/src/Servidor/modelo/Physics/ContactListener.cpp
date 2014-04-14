#include "ContactListener.h"
#include "Body.h"

ContactListener::ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//This assumes every sensor fixture is fluid, and will interact
	//with every dynamic body.
	if ( fixtureA->IsSensor() &&
		fixtureB->GetBody()->GetType() == b2_dynamicBody )
	m_fixturePairs.insert( std::make_pair(fixtureA, fixtureB) );
	else if ( fixtureB->IsSensor() &&
			fixtureA->GetBody()->GetType() == b2_dynamicBody )
	m_fixturePairs.insert( std::make_pair(fixtureB, fixtureA) );

}


void ContactListener::EndContact(b2Contact* contact) {

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//This check should be the same as for BeginContact, but here
	//we remove the fixture pair
	if ( fixtureA->IsSensor() &&
		fixtureB->GetBody()->GetType() == b2_dynamicBody )
	m_fixturePairs.erase( std::make_pair(fixtureA, fixtureB) );
	else if ( fixtureB->IsSensor() &&
			fixtureA->GetBody()->GetType() == b2_dynamicBody )
	m_fixturePairs.erase( std::make_pair(fixtureB, fixtureA) );

}


ContactListener::~ContactListener() {
}

