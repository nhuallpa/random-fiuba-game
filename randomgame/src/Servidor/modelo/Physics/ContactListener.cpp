#include "ContactListener.h"
#include "Body.h"

ContactListener::ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//This assumes every sensor fixture is fluid, and will interact
	//with every dynamic body.
	if ( fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.insert( std::make_pair(fixtureA, fixtureB) );
		return;
	}
	else if ( fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.insert( std::make_pair(fixtureB, fixtureA) );
		return;
	}
	
	b2WorldManifold worldManifold;

	//If My body (B) is touching the floor (A) (somewhere)
	if ( fixtureB->GetBody()->GetType() == b2_dynamicBody && ((int)fixtureA->GetUserData() == UD_TERRAIN || fixtureA->GetBody()->GetType() == b2_dynamicBody)){
		//printf("\nSetted has GROUNDED");
		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->addGrounded();
		
		contact->GetWorldManifold(&worldManifold);

		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
		return;
	}
	if ( fixtureA->GetBody()->GetType() == b2_dynamicBody && ( (int)fixtureB->GetUserData() == UD_TERRAIN  || fixtureB->GetBody()->GetType() == b2_dynamicBody) ){
		static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->addGrounded();
		
		contact->GetWorldManifold(&worldManifold);

		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setNormalForce(worldManifold.normal.x,worldManifold.normal.y);
		return;
	}

	// Contacto de misiles
	if ( fixtureB->GetUserData() == (void*)UD_MISSIL && ((int)fixtureA->GetUserData() == UD_TERRAIN || fixtureA->GetBody()->GetType() == b2_dynamicBody)){
		// Si no explota por tiempo (mejor preguntar por hasDelayedExplosion )
		if ( static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->getWeaponId() != GRENADE )
			static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->setExploded(true);
		
		return;
	}
	if ( fixtureA->GetUserData() == (void*)UD_MISSIL && ( (int)fixtureB->GetUserData() == UD_TERRAIN  || fixtureB->GetBody()->GetType() == b2_dynamicBody) ){
		if ( static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->getWeaponId() != GRENADE )
			static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->setExploded(true);
		return;
	}



}


void ContactListener::EndContact(b2Contact* contact) {

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//This check should be the same as for BeginContact, but here
	//we remove the fixture pair
	if ( fixtureA->IsSensor() &&
		fixtureB->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.erase( std::make_pair(fixtureA, fixtureB) );
		return;
	}
	else if ( fixtureB->IsSensor() &&
			fixtureA->GetBody()->GetType() == b2_dynamicBody ){
		m_fixturePairs.erase( std::make_pair(fixtureB, fixtureA) );
		return;
	}

	//If My body (B) is touching the floor (A) (somewhere)
	if ( fixtureB->GetBody()->GetType() == b2_dynamicBody && ((int)fixtureA->GetUserData() == UD_TERRAIN || fixtureA->GetBody()->GetType() == b2_dynamicBody)){
		//printf("\nSetted has NOT GROUNDED");
		//fixtureB->GetBody()->SetLinearVelocity(b2Vec2(0,-5));
		static_cast<GameElement*>(fixtureB->GetBody()->GetUserData())->reduceGrounded();


		return;
	}
	if ( fixtureA->GetBody()->GetType() == b2_dynamicBody && ((int)fixtureB->GetUserData() == UD_TERRAIN || fixtureB->GetBody()->GetType() == b2_dynamicBody)){
		//printf("\nSetted has NOT GROUNDED");
		//fixtureA->GetBody()->SetLinearVelocity(b2Vec2(0,-5));
		static_cast<GameElement*>(fixtureA->GetBody()->GetUserData())->reduceGrounded();


		return;
	}



}


ContactListener::~ContactListener() {
}

