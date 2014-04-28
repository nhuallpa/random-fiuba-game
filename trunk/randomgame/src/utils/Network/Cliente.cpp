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
	printf("Disparado keepalive thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	std::string* playerId = &((threadData*)data)->p;

	std::vector<uint8_t> keepaliveData(10);
	Messages keepaliveMsg = KEEPALIVE;

	while(true){
		if ( cli->sendMsg(keepaliveMsg,keepaliveData) ){
			//Server disconnected
			printf("Server died");

			break;
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

	
	printf("\nClient: Getting world");

	//Login to server
	/*buffer.push_back(uint8_t(pl));*/

	Datagram msg;

	msg.type = LOGIN;
	msg.playerID = "PL1"; // works?
	printf("\nLogin player id: %s",msg.playerID.c_str());

	if ( !this->output.sendmsg(msg) ) {
		//Log::e("connection error");
		printf("\nClient: connection error");
		return;
	}

		printf("\nSTART - Retrieving data from server");
	if (!this->input.rcvmsg(type, datos)) {
		//Log::e("connection error");
		printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}
		printf("\nDONE - Retrieving data from server");




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