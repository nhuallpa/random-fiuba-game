
#include "Servidor.h"
#include <string>

Servidor::Servidor()
	: input ()
	, output ()
	, cantJugadores()
	, deltas ()
{
}




Servidor::Servidor(int nroPuerto, size_t cantJugadores)
	: input (nroPuerto + 1)
	, output (nroPuerto)
	, cantJugadores(cantJugadores)
	, playerList()
	, deltas ()
{
	output.setKeepAlive();
	output.setListen(4);
	input.setKeepAlive();
	input.setListen(4);

/* Eventos que puede recibir el modelo

- Seleccion de worm
- Movimiento de worm

Estructura del mensaje:

PLAYABLE
Worm ID, Worm position: X,Y
Worm action: STEP RIGHT, STEP LEFT, JUMP, INITIAL PLACEMENT
Weapon: ?
Target:

- Conexion de jugador   ------> Va en mensajes INIT
- Desconexion de jugador -----> Va en mensajes INIT


*/

	// Inicio el thread para recibir clientes nuevos
	printf("Por crear thread");

	//Start connection Loop, when a client connects I will trigger a new thread for him
	this->wait4Connections();

	//TODO: Loop reading changed elements, if I had one I will send it to the client
	//IDEA: Usar SDL_Cond para avisar que hay un elemento :)



}

void Servidor::wait4Connections(){
	//this is where client connects. svr will hang in this mode until client conn
	printf("Listening");
	int players = 0;
	while (this->cantJugadores > players){
		Socket sClientO = this->input.aceptar();
		sClientO.setRcvTimeout(5, 0);

		Socket sClientI = this->output.aceptar();
		threadData data;
		data.srv = this;
		data.clientI = sClientI;
		data.clientO = sClientO;

		//ToDo: ocupar el map/list de clientes conectados

		Thread clientThread("Client Thread",initClient,&data);

		players++;
	}
        

}



Servidor::~Servidor() {
	//TODO
	// for (auto& par : clientes.get()) {
		// close(par.second.input);
		// close(par.second.output);
	// }
}


int Servidor::initClient(void* data){
	
	Servidor* srv = (Servidor*)((threadData*)data)->srv;

	//TODO: Enviar data del mundo necesaria para el cliente - vector de Playable con action INITIAL_PLACEMENT
	//Playable* playableWorld = srv->getPlayable();

	//TODO: Esperar mensajes del cliente, al recibir, bloquear elementsChanged 
	//		y agregarlo a la cola. Luego (en otro loop) mirar los cambios y 
	//		propagarlos

	std::vector<uint8_t> datos;
	Messages type = KEEPALIVE;
		try {
		while (true) {
			if (! ((threadData*)data)->clientO.rcvmsg(type, datos)) {
				
				//srv->desconectar(playerId);
				break;
			}
			switch (type) {
			case UPDATE:
				

				
				break;


			case KEEPALIVE:
				// Al pasar un tiempo, el cliente manda un paquete para mantener vivo el socket
				// El servidor responde un vivo para mantener abierto el otro socket
				//this->sendHeartBeat(playerId, Red::TipoMensaje::Vivo);
				break;
			}
		}
	} catch (...) {
		//srv->desconectar(playerId);
	}





	return 0;
}

bool Servidor::allConnected() const {
	//return !( playerList.get().size() < cantJugadores);
	return false;
}

void Servidor::notifyReject(Socket& client) {
	std::vector<uint8_t> buffer;
	buffer.push_back(uint8_t(Messages::REJECT));
	client.sendmsg(Messages::REJECT, buffer);
}



//void Servidor::broadcastMsg(Playable change) {
//
//		//ToDo: Recorro lista de clientes y envio las actualizaciones
//
//		// try {
//			// enviarMensaje(par.first, delta.aRed());
//		// } catch (...) {
//			// desconectar(par.first);
//		// }
//
//}
//

//
//void Servidor::wait4Updates(Player playerId) {
//	Messages type;
//	std::vector<uint8_t> datos;
//
//	try {
//		while (true) {
//			if (!recibir(playerId.output, type, datos)) {
//				desconectar(playerId);
//				break;
//			}
//			switch (type) {
//			case Red::TipoMensaje::Objeto:
//				//Aplico al modelo
//				//this->processCommand();
//				//Doy un paso en el mundo
//				
//				//Obtengo la lista de elementos modificados y la envio
//				deltas.push(Serializacion::Objeto::deRed(datos));
//				
//				break;
//
//			// Estos casos no se dan ya que los unicos msjs que puede recibir el servidor es de Objeto o Vivo
//			case Red::TipoMensaje::Jugador:
//			case Red::TipoMensaje::Rechazo:
//			case Red::TipoMensaje::Vivo:
//				// Al pasar un tiempo, el cliente manda un paquete para mantener vivo el socket
//				// El servidor responde un vivo para mantener abierto el otro socket
//				this->sendHeartBeat(playerId, Red::TipoMensaje::Vivo);
//				break;
//			}
//		}
//	} catch (...) {
//		desconectar(playerId);
//	}
//}
//
//
//
//void Servidor::enviarMensaje(Player playerId, std::vector<uint8_t> buffer) {
//	if (!enviar(playerId.input, Red::TipoMensaje::Objeto, buffer)) {
//		desconectar(idCli);
//	}
//}
//

//
//void Servidor::sendHeartBeat(Player playerId, Message::KEEPALIVE keepalive) {
//	std::vector<uint8_t> buffer;
//	buffer.push_back(uint8_t(playerId));
//	if (!enviar(playerId.input, keepalive, buffer)) {
//		desconectar(playerId);
//	}
//}
//
//void Servidor::desconectar(Player playerId) {
//	std::pair<int,int> deleted;
//
//	playerList.transform([&] (Players val) -> Players {
//		if (val.count(playerId) != 0) {
//			deleted = val[playerId.name];
//			val.erase(idCli);
//		}
//		return val;
//	});
//
//	close(deleted.first);
//	close(deleted.second);
//
//}


int main (){

	Servidor mySrv(10025,4);
	while(true){

	}
	return 0;


}