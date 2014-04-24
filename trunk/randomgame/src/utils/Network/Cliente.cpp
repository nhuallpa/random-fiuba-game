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

	input.connect2(ip, port);
	printf("first connected");
	output.connect2(ip, port + 1);
	printf("second connected");

	//esperarMensaje(); // recibo el mundo o un codigo de reject

	//Thread de escucha de mensajes en la red


	//Thread de escucha de actualizaciones locales


	//Thread de keepalive (Send dummies over network)

}

Cliente::~Cliente() {
}

void Cliente::esperarMensaje() {
	Messages type;
	std::vector<uint8_t> datos;
	
	if (!this->input.rcvmsg(type, datos)) {
		//Log::e("connection error");
		printf("Client: connection error");
	}

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

bool Cliente::alive () {
	return true;
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