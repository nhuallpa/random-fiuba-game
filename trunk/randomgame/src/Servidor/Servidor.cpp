#include "Servidor.h"

Servidor::Servidor()
	: input ()
	, output ()
	, cantJugadores()
	, changes ()
	, lock()
	, netlock()
	, canUpdate(lock)
	, canBroadcast(netlock)
{
}

Servidor::~Servidor(void){

}

bool Servidor::begin(void){

	// TODO @future - Initialize socket

	return true;
}

void Servidor::loop(void){
	Log::i("============== INICIANDO SERVIDOR =============");		
	// Init conns from clients
	bool quit = false;		
	while (quit == false){
		
		// TODO @future - The engine will loop separately when this runs on different sockets, not now (TP1)
		if( this->gameEngine.initWorld() ) quit = true;
	}

	//TODO @future -  CERRAR CONEXIONES DE CLIENTES 
	return void();
}

bool Servidor::run(void){
	if( this->begin() == true ){
		this->loop();
	}else{
		return false;
	}
	return true;
}

void Servidor::destroyWorld(void){
	//TODO @future -  this->gameEngine.destroyWorld();
}

GameLevel Servidor::getLevel(){

	return this->gameEngine.getLevel();
}

GameEngine Servidor::getGameEngine(){

	return this->gameEngine;
}


Servidor::Servidor(int nroPuerto, size_t cantJugadores)
	: input (nroPuerto) // En este port se recibe data del cliente
	, output (nroPuerto + 1) // Por aca realizamos updates a los clientes
	, cantJugadores(cantJugadores)
	, pList()
	, changes()
	, lock()
	, netlock()
	, canUpdate(lock)
	, canBroadcast(netlock)
{

	jugadoresConectados = 0;

	this->data.srv = this;


	//Start connection Loop, when a client connects I will trigger a new thread for him
	Thread waitConnections("Connection Handler Thread",wait4Connections,&data);

	//TODO: UpdatingThread()
	//		Dispara el thread que ante un update modifica el mundo, simula un paso
	//		y notifica a los clientes.
	Thread clientThread("Updating Thread",updating,&data);

	Thread netUpdaterThread("Updater",broadcastMessages,&data);

}

int Servidor::updating(void* data){
	printf("\n\n\nUpdating Thread running\n");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;
	std::vector<Playable>* changes =  &srv->changes;
	
	Condition* cond =  &srv->canUpdate;
	Mutex* m = &srv->lock;

	Condition* netcond =  &srv->canBroadcast;
	Mutex* n =  &srv->netlock;

	while(true){
		m->lock();
		if ( changes->empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		printf("\nUpdating: doing stuff at server side");
		Playable p;
		p = srv->changes.back();
		//srv->updateModel(p);
		//if necessary signal condition to start broadcasting, if not wait
		n->lock();
		srv->worldChanges.push_back(p);
		n->unlock();
		netcond->signal();
		
		


		srv->changes.pop_back();
		m->unlock();
	}
	return 0;
}


int Servidor::broadcastMessages(void* data){
	printf("\n\n\Broadcast Thread running\n");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;

	std::vector<Playable>* worldChanges = &srv->worldChanges;
	
	Condition* netcond = &srv->canBroadcast;
	Mutex* n = &srv->netlock;

	while(true){
		n->lock();
		if ( worldChanges->empty() ){
			//printf("\nwaiting.. is empty :(");
			netcond->wait();
		}
		printf("\nUpdating all the clients");

		Playable p = worldChanges->back();

		for ( int i = 0 ; i < srv->jugadoresConectados ; i++){
			printf("Sending data to client: %d",i);
		}


		worldChanges->pop_back();
		n->unlock();

	}

	
	return 0;	
}



int Servidor::wait4Connections(void* data){
	//this is where client connects. srv will hang in this mode until client conn
	printf("Listening");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;

	std::vector<Playable>* changes = &srv->changes;

	Condition* cond = &srv->canUpdate;
	Mutex* m = &srv->lock;

	int players = 0;
	while (true){
		
		while(srv->cantJugadores > srv->jugadoresConectados){
			Socket sClientO = srv->input.aceptar();
			Socket sClientI = srv->output.aceptar();

			threadData* dataCliente = new threadData();
			dataCliente->srv = srv;
			dataCliente->clientI = sClientI;
			dataCliente->clientO = sClientO;

			Thread clientThread("Client Thread",initClient,dataCliente);

			srv->jugadoresConectados++;
		}
	}

	return 0;

}


void Servidor::waitConnections(){

}


int Servidor::initClient(void* data){
	printf("Disparado cliente");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;

	std::vector<Playable>* changes = &srv->changes;
	Condition* cond = &srv->canUpdate;
	Mutex* m = &srv->lock;
	char* playerId = aThreadData->p;

	//TODO: Enviar data del mundo necesaria para el cliente - vector de Playable con action INITIAL_PLACEMENT
	//Playable* playableWorld = srv->getPlayable();

	//TODO: Esperar mensajes del cliente, al recibir, bloquear elementsChanged 
	//		y agregarlo a la cola. Luego (en otro loop) mirar los cambios y 
	//		propagarlos

	std::vector<uint8_t> datos(10);
	std::vector<uint8_t> keepaliveData(10);
	Messages keepaliveMsg = KEEPALIVE;
	Datagram* datagram = new Datagram();


	// Receive LOGIN info
	if (! ((threadData*)data)->clientO.rcvmsg(*datagram)) {
		printf("\nDesconectando cliente at login");
		srv->disconnect(playerId);
		return 1;
	}


	srv->pList.insert(	std::make_pair<std::string,std::pair<int,int>>(datagram->playerID,
						std::make_pair(((threadData*)data)->clientO.getFD(),
						((threadData*)data)->clientI.getFD())
						)
					);

	std::strcpy((char*)playerId,datagram->playerID.c_str() );

	datagram->type = CONF;
	std::strcpy(datagram->play.level,"level.yaml");

	//Send World info to client (LEVEL)
	((threadData*)data)->clientI.sendmsg(*datagram);
	printf("\nEnviando data (level) al cliente");

	//Send World info to client (entire world)
	//TODO: Elements
	datagram->type = INIT;
	datagram->elements = 2;
	((threadData*)data)->clientI.sendmsg(*datagram);
	printf("\nEnviando data (elements) al cliente");

	//Start sending elements
	//TODO for loop

	//GameElement aWorm(1,"PLAYER 1",WORM,30,50,0,45,45,15,false);
	//GameElement aWorm1(2,"PLAYER 1",WORM,70,80,0,45,45,15,false);
	//GameElement aWorm2(3,"PLAYER 1",WORM,150,95,0,45,45,15,false);

	datagram->type = INIT;
	datagram->play.wormid = 21;
	datagram->play.x = 30;
	datagram->play.y = 51;


	aThreadData->clientI.sendmsg(*datagram);
	printf("\nEnviando data (worm 21) al cliente");

	datagram->play.wormid = 45;
	datagram->play.x = 70;
	datagram->play.y = 80;
	aThreadData->clientI.sendmsg(*datagram);
	printf("\nEnviando data (worm 45) al cliente");


	int activeClient=1;
		try {
		while (activeClient) {
			//Sleep(1);
			if (! aThreadData->clientO.rcvmsg(*datagram)) {
				printf("\nDesconectando cliente: %s",playerId );
				srv->disconnect(playerId);
				activeClient=0;
				break;
			}
			
			// Got something ;)
			m->lock();
			try{
				printf("\nGot something from client %s ;)",playerId );
			}catch(...){
				m->unlock();
				throw std::current_exception();
			}


			switch (datagram->type) {
			case UPDATE:
				printf("\nGot update");
				srv->changes.push_back(datagram->play);

				m->unlock();
				cond->signal();


				break;


			case KEEPALIVE:
				// Al pasar un tiempo, el cliente manda un paquete para mantener vivo el socket
				// El servidor responde un vivo para mantener abierto el otro socket
				//this->sendHeartBeat(playerId, Red::TipoMensaje::Vivo);
				//printf("\nGot keepalive");
				// DEPRECATED - Handling connections in other way now
				printf("\nGot keepalive");
				//((threadData*)data)->clientI.sendmsg(keepaliveMsg,keepaliveData);
				
				m->unlock();
				cond->signal();
				break;
			case LOGIN:
				//((threadData*)data)->clientI.sendmsg(type,datos);
				printf("\nEnviando data al cliente - switch");
				
				m->unlock();
				cond->signal();
				break;
			}
		}
	} catch (...) {
		//srv->desconectar(playerId);
		throw std::current_exception();
	}
	printf("\nAbandonando cliente\n");





	return 0;
}

bool Servidor::allConnected() const {
	return !( this->pList.size() < cantJugadores);
	//return false;
}

void Servidor::notifyReject(Socket& client) {
	std::vector<uint8_t> buffer;
	buffer.push_back(uint8_t(Messages::REJECT));
	client.sendmsg(Messages::REJECT, buffer);
}




void Servidor::disconnect(Player playerId) {
	
	printf("\nReleasing player: %s\n",playerId.c_str());
	closesocket(this->pList[playerId].first);
	closesocket(this->pList[playerId].second);
	this->pList.erase(playerId);
	this->jugadoresConectados--;

}

//Main mock
//int main (){
//
//	Servidor mySrv(10025,1);
//	while(true){
//
//	}
//	return 0;
//
//
//}