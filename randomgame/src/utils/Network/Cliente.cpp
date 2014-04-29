#include "Cliente.h"

Cliente::Cliente()
	: input(Socket())
	, output(Socket())
	, pl()
	, localChanges()
	, networkChanges()
	, m()
	, somethingToTell(m)
{
}

Cliente::Cliente(char* ip, int port)
	: input(Socket())
	, output(Socket())
	, pl()
	, localChanges()
	, networkChanges()
	, m()
	, somethingToTell(m)

{
	//input.setKeepAlive();
	//input.setRcvTimeout(5, 0);
	//output.setKeepAlive();
	//output.setSendTimeout(5, 0);

	input.connect2(ip, port+1);
	printf("Connected to data port: %d", port);
	output.connect2(ip, port);
	printf("Connected to update port: %d", port+1);
	this->srvStatus = true;

	threadData data;
	data.cli = this;

	getRemoteWorld(); // recibo el mundo o un codigo de reject

	//Thread de escucha de mensajes en la red
	//Thread networkUpdatesThread("Net Updates",applyNetworkChanges,&data);

	//Thread de escucha de actualizaciones locales
	Thread localUpdatesThread("LocalUpdates",notifyLocalUpdates,&data);

	//Thread de keepalive (Send dummies over network)
	Thread keepaliveThread("KeepAlive",keepalive,&data);

}

Cliente::~Cliente() {


}


int Cliente::notifyLocalUpdates(void *data){

	printf("\nDisparado notify local updates thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	Condition* cond = &((Cliente*)((threadData*)data)->cli)->somethingToTell;
	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();

	while(true){
		m->lock();
		if ( cli->localChanges.empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		printf("\nGot a local change");

		msg->play.wormid = cli->localChanges.back().wormid;
		msg->play.weaponid = cli->localChanges.back().weaponid;
		msg->play.state = cli->localChanges.back().state;
		msg->play.action = cli->localChanges.back().action;
		msg->type = UPDATE;

		if ( !cli->output.sendmsg(*msg) ) {
			//Log::e("connection error");
			printf("\nClient: connection error");
			m->unlock();
			return 1;
		}

		cli->localChanges.pop_back();
		m->unlock();
	}
	return 0;
}


int Cliente::keepalive(void* data){
	printf("\nDisparado keepalive thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	Condition* cond = &((Cliente*)((threadData*)data)->cli)->somethingToTell;
	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();
	msg->type = KEEPALIVE;
	int i=0;
	while(true){
		Sleep(10);
		i++;
		//if ( !cli->output.sendmsg(*msg) ){
		//	//Server disconnected
		//	printf("Server died");

		//	break;
		//}

		if ( !cli->output.rcvmsg(*msg) ) {
			printf("\nDesconectando cliente at login");
			break;
		}
		
		//Esto es lo que se va disparar al haber una accion del lado del cliente
		if ( i == 20 ){
			m->lock();
			try{
				//printf("\nGot something from client %s at i: %d ;)",playerId,i );
				Playable p;
				p.wormid=37;
				cli->localChanges.push_back(p);
			}catch(...){
				m->unlock();
				throw std::current_exception();
			}
			m->unlock();
			cond->signal();
		}



	}

	return 0;
}

int Cliente::login(){

	Datagram msg;

	msg.type = LOGIN;
	std::strcpy((char*)&msg.playerID,this->pl.c_str()); // works?
	printf("\nplayer id: %s",msg.playerID.c_str());

	this->sendDatagram(msg);
	//Send login datagram

	return 0;
}


int Cliente::sendDatagram(Datagram msg){

	if ( !this->output.sendmsg(msg) ) {
		//Log::e("connection error");
		printf("\nClient: connection error");
		return 1;
	}
	return 0;

}



void Cliente::getRemoteWorld() {
	Messages type = LOGIN;
	std::vector<uint8_t> datos;
	std::vector<uint8_t> buffer;
	Datagram* msg = new Datagram();
	
	//Login to server
	msg->type = LOGIN;
	msg->playerID = "PLAYER1"; 
	printf("\nLogin player id: %s",msg->playerID.c_str());

	if ( !this->output.sendmsg(*msg) ) {
		//Log::e("connection error");
		printf("\nClient: connection error");
		return;
	}

	printf("\nSTART - Retrieving data from server");
	if (!this->input.rcvmsg(*msg)) {
		//Log::e("connection error");
		printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}
	printf("\nDONE - Retrieving data from server, level: %s", msg->play.level);
	//TODO SET LEVEL ON CLIENT


	if (!this->input.rcvmsg(*msg)) {
		//Log::e("connection error");
		printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}
	printf("\nDONE - Retrieving data from server, world elements: %d", msg->elements);
	int count = msg->elements;
	for ( int i=0; i < count; i++){
		if (!this->input.rcvmsg(*msg)) {
			//Log::e("connection error");
			printf("\nClient: connection error - Server disconnected/not responding");
			return;
		}
		printf("\nGetted worm id: %d",msg->play.wormid);
	}

	


}

bool Cliente::serverAlive () {
	return this->srvStatus;
}

//void Cliente::push (Playable localChange) {
//	
//}



int Cliente::sendMsg(Messages type, std::vector<uint8_t> buffer) {
	if ( !this->output.sendmsg(type, buffer) ) {
		//Log::e("connection error");
		printf("Client: connection error");
		return 1;
	}
	return 0;

}

int main(){

	Cliente myClient("localhost",10025);
	//Cliente myClient2("localhost",10026);
	while(true){
	}

	return 0;
}