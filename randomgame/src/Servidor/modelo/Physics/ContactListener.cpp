#include "ContactListener.h"
#include "Body.h"

ContactListener::ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

	if (!contact->IsTouching()) {
		return;
	}

	void* data1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* data2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (!data1 || !data2) {
		return;
	}

	auto ca = static_cast<Body*>(data1);
	auto cb = static_cast<Body*>(data2);
	//auto entidad1 = ca->;
	//auto entidad2 = cb->entidad;
	//if (!entidad1.valido() || !entidad2.valido()) {
	//	return;
	//}


}

ContactListener::~ContactListener() {
}

