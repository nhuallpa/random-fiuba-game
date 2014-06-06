#include "Updater.h"


Updater::Updater(Socket* input, Socket* output,	Mutex* m, Mutex* n,	Condition* somethingToTell,	std::vector<Playable>* localChanges)
				: input(input)
				, output(output)
				, m(m)
				, n(n)
				, somethingToTell(somethingToTell)
				, localChanges(localChanges)

{
}


Updater::~Updater(void)
{
}


bool Updater::doLogin()
{
	Messages type = LOGIN;
	std::vector<uint8_t> datos;
	std::vector<uint8_t> buffer;
	EDatagram* msg = new EDatagram();
	
	//Login to server
	msg->type = LOGIN;
	msg->playerID = this->pl; 

	Log::t("Sending login info ");
	if ( !this->output->sendmsg(*msg) ) {
		Log::e("Client: Login request connection error");
		//this->srvStatus = SERVER_NOT_RESPONDING;
		return false;
	}
	// recibo confirmacion de login
	EDatagram* datagram = new EDatagram();
	if ( !this->input->rcvmsg(*datagram) ) {
		Log::e("Client: Login response connection error");
		return false;
	}
	// proceso resultado
	if (datagram->type == ALREADY_EXIST_USER) {
		Log::i("Client: El usuario ya esta registrado y jugando en el servidor");
		return false;
	} else if (datagram->type == LOGIN_OK) {
		Log::i("Client: Login con exito");
		return true;
	} else {
		Log::i("Client: Login ERROR - rta %d" ,datagram->type);
		return false;
	}
	delete datagram;

}

void Updater::retrieveLevel()
{
	EDatagram* msg = new EDatagram();
	// Get YAML
	this->input->receiveFile("res/levels/clienteyaml.yaml");

	// se comenta hace porque pincha
	//delete msg;
}

void Updater::doLogout()
{
	//Logout to server
	EDatagram* msg = new EDatagram();

	msg->type = LOGOUT;
	msg->playerID = this->pl; 

	Log::t("Sending login info ");
	if ( !this->output->sendmsg(*msg) ) {
		Log::e("Updater::doLogout >> I coudn't send logout msg");
	} else {
		Log::i("Updater::doLogout >> Logout done!");
	}
}

void Updater::doStopWorm(int idWorm)
{
	Playable p;
	p.action = MOVE_STOP;
	p.wormid = idWorm;
	this->addLocalMovementFromView(p);
}

void Updater::doSelectWapon(int wormId, int idWeapon)
{
	Playable p;
	p.action = WITH_WEAPON;
	p.wormid = wormId;
	p.weaponid = idWeapon;
	this->addLocalMovementFromView(p);
}

void Updater::doShoot(int wormId, int idWeapon, int x_aim, int y_aim)
{
	Playable p;
	p.action = DO_SHOOT;
	p.wormid = wormId;
	p.weaponid = idWeapon;
	p.x = x_aim;
	p.y = y_aim;
	this->addLocalMovementFromView(p);
}

void Updater::addLocalMovementFromView(Playable p){

	this->m->lock();
	try{
		this->localChanges->push_back(p);
	}catch(...){
		this->m->unlock();
		throw std::current_exception();
	}
	this->m->unlock();
	this->somethingToTell->signal();

}
