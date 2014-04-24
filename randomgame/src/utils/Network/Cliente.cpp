#include "Cliente.h"

Cliente::Cliente()
	: input(Socket())
	, output(Socket())
	, pl()
	, localChanges()
	, networkChanges()
{
}

Cliente::Cliente(char* ip, int port)
	: input(Socket())
	, output(Socket())
	, pl()
	, localChanges()
	, networkChanges()
{
	input.setKeepAlive();
	input.setRcvTimeout(5, 0);
	output.setKeepAlive();
	output.setSendTimeout(5, 0);

	input.connect2(ip, port+1);
	printf("Connected to data port: %d", port);
	output.connect2(ip, port);
	printf("Connected to update port: %d", port+1);
	this->srvStatus = true;

	threadData data;
	data.cli = this;

	getRemoteWorld(); // recibo el mundo o un codigo de reject

	//Thread de escucha de mensajes en la red
	//Thread 

	//Thread de escucha de actualizaciones locales
	//Thread

	//Thread de keepalive (Send dummies over network)
	Thread keepaliveThread("KeepAlive",keepalive,&data);

}

Cliente::~Cliente() {
}

int Cliente::keepalive(void* data){
	printf("Disparado cliente");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	std::string* playerId = &((threadData*)data)->p;

	std::vector<uint8_t> keepaliveData(10);
	Messages keepaliveMsg = KEEPALIVE;

	while(true){
		cli->sendMsg(keepaliveMsg,keepaliveData);

	}

	return 0;
}

void Cliente::getRemoteWorld() {
	Messages type;
	std::vector<uint8_t> datos;
	
	if (!this->input.rcvmsg(type, datos)) {
		//Log::e("connection error");
		printf("\nClient: connection error - Server disconnected/not responding");
	}
	printf("\nRetrieving data from server");

	switch (type) {
	case Messages::PLAYER:
		
		break;

	case UPDATE:
		
		break;

	case REJECT:

		break;

	case KEEPALIVE:

		break;
	}
}

bool Cliente::serverAlive () {
	return this->srvStatus;
}

//void Cliente::push (Playable localChange) {
//	
//}



void Cliente::sendMsg(Messages type, std::vector<uint8_t> buffer) {
	if ( !this->output.sendmsg(type, buffer) ) {
		//Log::e("connection error");
		printf("Client: connection error");
	}

}

int main(){

	Cliente myClient("localhost",10025);
	//Cliente myClient2("localhost",10026);
	while(true){
	}

	return 0;
}