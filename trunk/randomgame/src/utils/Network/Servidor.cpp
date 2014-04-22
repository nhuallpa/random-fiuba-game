
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
	
	
	// Updating thread -- clients and model (first)
	//Thread("Envio de mensajes de update", [&] () {
	//	while (true) {
	//		//PlayableObject playable = deltas.pop();
	//		//Si Hubo una actualizacion --> actualizo el modelo
	//		//this->processCommands() //Updates modified data
	//		//step() in the world
	//		//Brodcastea delta a los clientes
	//		//broadcastMsg(this->change);
	//		//condicion.signal();
	//	}
	//	return 0;
	//});

	// Inicio el thread para recibir clientes nuevos
	printf("Por crear thread");

	//Start connection Loop, when a client connects I will trigger a new thread for him
	this->wait4Connections();


	//Thread arrivalHandler("Arrival Handler", messageManager, this);
	//arrivalHandler.wait();
}

void Servidor::wait4Connections(){
	//this is where client connects. svr will hang in this mode until client conn
	printf("Listening");
	int players = 0;
	while (this->cantJugadores > players){
		Socket sClientO = this->input.aceptar();
		sClientO.setRcvTimeout(5, 0);

		Socket sClientI = this->output.aceptar();
       
		//pthread_create(&threadA[noThread], NULL, task1, NULL);
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
//
//void Servidor::push (PlayableObject changes) {
//	deltas.push(changes);
//}

int Servidor::messageManager(void* data){

	Servidor* srv = (Servidor*)data; 
	while (true) {
		printf("Thread loopeando");
		Socket sClientO = srv->input.aceptar();
		sClientO.setRcvTimeout(5, 0);

		Socket sClientI = srv->output.aceptar();

		if (srv->allConnected()) {
			// Ya estan todos los jugadores conectados, rechazo el que recien se conecto
			notifyReject(sClientI);
			//Log::e(SERVER,"Couldn't connect, all seats taken try again later");
			return 0;
		}

		Player gamer;
	
		//Get a position on the players list
		 //playerList.transform([&] (Players val) -> Players {
			 //idCli = getSiguienteJugador(val);
			//val[gamer.name] = std::make_pair<int,int>(sClientI,sClientO);
		//	return val;
		//});

		//TODO: Enviar data del mundo necesaria para el cliente - vector de Playable con action INITIAL_PLACEMENT
	
		// std::vector<uint8_t> vec = getCanonico().aRed();
		// enviarMensaje(idCli, vec);
		// this->sendWorld(id,data); //SendWorld() hace un getWorld2Playable() y deja en un playable vector el mundo

		//TODO: Esperar mensajes del cliente
		//Thread("Wait messages from client", [&] () {
		//	wait4Updates(idCli);
		//	return 0;
		//});

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


//void Servidor::esperarLlamadas() {

//	Socket sClientO = input.aceptar();
//	sClientO.setRcvTimeout(5, 0);
//
//	Socket sClientI = output.aceptar();
//
//	if (allConnected()) {
//		// Ya estan todos los jugadores conectados, rechazo el que recien se conecto
//		this->notifyReject(sClientI);
//		//Log::e(SERVER,"Couldn't connect, all seats taken try again later");
//		return;
//	}
//
//	Player gamer;
//	
//	//Get a position on the players list
//	 playerList.transform([&] (Players val) -> Players {
//		 //idCli = getSiguienteJugador(val);
//		//val[gamer.name] = std::make_pair<int,int>(sClientI,sClientO);
//		return val;
//	});
//
//	//TODO: Enviar data del mundo necesaria para el cliente - vector de Playable con action INITIAL_PLACEMENT
//	// Envio el Objeto actual al cliente
//	// std::vector<uint8_t> vec = getCanonico().aRed();
//	// enviarMensaje(idCli, vec);
//	// this->sendWorld(id,data); //SendWorld() hace un getWorld2Playable() y deja en un playable vector el mundo
//
//	Thread("Wait messages from client", [&] () {
//		wait4Updates(idCli);
//		return 0;
//	});
//}
//
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