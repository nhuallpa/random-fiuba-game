
#include "Servidor.h"
#include <string>

Servidor::Servidor()
	: input ()
	, output ()
	, cantJugadores()
	, changes ()
	, lock()
	, canUpdate(lock)
{
}




Servidor::Servidor(int nroPuerto, size_t cantJugadores)
	: input (nroPuerto + 1)
	, output (nroPuerto)
	, cantJugadores(cantJugadores)
	, pList()
	, changes()
	, lock()
	, canUpdate(lock)
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
	threadData data;
	data.srv = this;
	printf("Data inicial: %p, server: %p",data,data.srv);



	//Start connection Loop, when a client connects I will trigger a new thread for him
	//TODO: Dispararlo en un thread

	Thread waitConnections("Connection Handler Thread",wait4Connections,&data);
	//this->waitConnections();

	//TODO: Loop reading changed elements, if I had one I will send it to the client
	//IDEA: Usar SDL_Cond para avisar que hay un elemento :)


	//TODO: UpdatingThread()
	//		Dispara el thread que ante un update modifica el mundo, simula un paso
	//		y notifica a los clientes.

	Thread clientThread("Updating Thread",updating,&data);
	Sleep(100000);
	this->canUpdate.signal();
}

int Servidor::updating(void* data){
	printf("Updating...");
	Servidor* srv = ((threadData*)data)->srv;
	Queue<Playable>* changes = &((Servidor*)((threadData*)data)->srv)->changes;
	Condition* cond = &((Servidor*)((threadData*)data)->srv)->canUpdate;
	Mutex* m = &((Servidor*)((threadData*)data)->srv)->lock;

	while(true){
		m->lock();
		if ( changes->empty() ){
			printf("waiting.. is empty :(");
			cond->wait();
		}
		printf("doing stuff");
		//TODO: Do stuff

		m->unlock();
	}
	return 0;
}

int Servidor::wait4Connections(void* data){
	//this is where client connects. srv will hang in this mode until client conn
	printf("Listening");
	Servidor* srv = (Servidor*)((threadData*)data)->srv;
	printf("Data Wait 4 conn: %p, server: %p",data,srv);
	Queue<Playable>* changes = (Queue<Playable>*)&((Servidor*)((threadData*)data)->srv)->changes;
	Condition* cond = (Condition*)&((Servidor*)((threadData*)data)->srv)->canUpdate;
	Mutex* m = (Mutex*)&((Servidor*)((threadData*)data)->srv)->lock;

	int players = 0;
	while (srv->cantJugadores > players){
		Socket sClientO = srv->input.aceptar();
		sClientO.setRcvTimeout(5, 0);
		Socket sClientI = srv->output.aceptar();

		threadData* dataCliente = new threadData();
		dataCliente->srv = srv;
		dataCliente->clientI = sClientI;
		dataCliente->clientO = sClientO;
		
		//ToDo: ocupar el map/list de clientes conectados

		Thread clientThread("Client Thread",initClient,dataCliente);

		players++;
	}

	return 0;

}


void Servidor::waitConnections(){
	//this is where client connects. srv will hang in this mode until client conn
	printf("Listening");
	
	int players = 0;
	while (this->cantJugadores > players){
		
		Socket sClientO = this->input.aceptar();
		sClientO.setRcvTimeout(5, 0);
		
		Socket sClientI = this->output.aceptar();
		
		threadData* dataCliente = new threadData();

		dataCliente->srv = this;
		dataCliente->clientI = sClientI;
		dataCliente->clientO = sClientO;
		//ToDo: ocupar el map/list de clientes conectados

		Thread clientThread("Client Thread",initClient,dataCliente);
		players++;
	}
}


Servidor::~Servidor() {
	//TODO: Close every socket pair
	// for (auto& par : clientes.get()) {
		// close(par.second.input);
		// close(par.second.output);
	// }
}


int Servidor::initClient(void* data){
	printf("Disparado cliente");
	Servidor* srv = ((threadData*)data)->srv;
	Queue<Playable>* changes = &((Servidor*)((threadData*)data)->srv)->changes;
	Condition* cond = &((Servidor*)((threadData*)data)->srv)->canUpdate;
	Mutex* m = &((Servidor*)((threadData*)data)->srv)->lock;

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
				printf("nada");
				//srv->desconectar(playerId);
				break;
			}
			printf("algo");
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

	Servidor mySrv(10025,1);
	while(true){

	}
	return 0;


}