#include "Servidor.h"


Servidor::~Servidor(void){

}

bool Servidor::begin(void){

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

GameLevel* Servidor::getLevel(){

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
	, playerslock()
	, worldlock()
	, canUpdate(lock)
	, canBroadcast(netlock)
	, canCreate(worldlock)
	, canAddNews(playerslock)
{

	//input.setRcvTimeout(15,5);
	//output.setRcvTimeout(15,5);
	//input.setSendTimeout(15,5);
	//output.setSendTimeout(15,5);
	//input.setKeepAlive();
	//output.setKeepAlive();

	this->advance = SDL_CreateSemaphore( 1 );

	jugadoresConectados = 0;

	//Carga el servidor con un nivel, ese nivel tiene el terreno y su fisica y los jugadores que han
	// sido registrados en el
	this->gameEngine.initWorld();


	/* Start threading stuff */

	this->data.srv = this;

	this->worldQ.type = UPDATE;

	//Start connection Loop, when a client connects I will trigger a new thread for him
	Thread waitConnections("Connection Handler Thread",wait4Connections,&data);

	//TODO: UpdatingThread()
	//		Dispara el thread que ante un update modifica el mundo, simula un paso
	//		y notifica a los clientes.
	Thread clientThread("Updating Thread",updating,&data);

	//Thread netUpdaterThread("Updater",broadcastMessages,&data);

	//TODO Refactor para que corra en el hilo principal 
	Thread stepOverThread("step",stepOver,&data);

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
		Sleep(10);
		m->lock();
		if ( changes->empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		//printf("\nUpdating: doing stuff at server side");
		Playable p;
		p = srv->changes.back();
		//printf("\nGot message from user requesting to move worm %d to %d",p.wormid,p.action);
		
		srv->updateModel(p); 
		
		srv->changes.pop_back();
		m->unlock();
	}
	return 0;
}



int Servidor::stepOver(void* data){
	printf("\n\n\StepOver Thread running\n");

	threadData* aThreadData = (threadData*)data;
	Servidor* srv = aThreadData->srv;
	
	Condition* netcond =  &srv->canBroadcast;
	Mutex* n =  &srv->netlock;

	Condition* worldcond =  &srv->canCreate;
	Mutex* w =  &srv->worldlock;

	int i=0;
	while(true){
		Sleep(20);

		w->lock();
		srv->getGameEngine().step();
		w->unlock();

		//si algo cambio actualizo a los clientes
		if ( i>=1 ){
			i=0;
	
			//chequeo si hay clientes
			if ( srv->pList.size()  ){
				SDL_SemWait(srv->advance);
				int res = srv->somethingChange();
				if ( res ){
					srv->worldQ.type = UPDATE;
					//Agrego a la cola y notifico clientes
					srv->notifyAll();
				}
				SDL_SemPost(srv->advance);
			} 
		}
		i++;
	}

	return 0;
}

int Servidor::somethingChange(){

	std::map<int,GameElement*> copy = this->gameEngine.getLevel()->getEntities();
	std::map<int,GameElement*>::iterator it = copy.begin();

	bool flag = false;
	int i=0;

	for ( ; it != copy.end() ; ++it){
		if( it->second->changed ){
			this->worldQ.play[i].wormid = it->second->getId();
			this->worldQ.play[i].x = it->second->getPosition().first;
			this->worldQ.play[i].y = it->second->getPosition().second;
			this->worldQ.play[i].action = it->second->getAction();
			flag = true;
			i++;
		}
		if ( !static_cast<Worm*>(it->second)->isAlive() ){

			//Envio data de que esta muerto (x=-1,y=-1) y lo elimino del mundo
			this->gameEngine.getLevel()->removeEntity(it->second->getId());
		}

	}

	this->worldQ.elements = i; 

	return i;
}


bool Servidor::updateModel(Playable p){
	//Apply playable to the world, locate wormid and apply the action
	this->gameEngine.applyAction2Element(p.wormid,p.action);

	return true;
}







int Servidor::wait4Connections(void* data){
	//this is where client connects. srv will hang in this mode until client conn
	printf("Listening");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;

	std::vector<Playable>* changes = &srv->changes;

	Condition* cond = &srv->canUpdate;
	Mutex* m = &srv->lock;

	Condition* canStart =  &srv->canAddNews;
	Mutex* allIn =  &srv->playerslock;

	int players = 0;
	while (true){
		Sleep(10);
		while(srv->cantJugadores > srv->jugadoresConectados){
			
			Socket sClientO = srv->input.aceptar();
			Socket sClientI = srv->output.aceptar();

			threadData* dataCliente = new threadData();
			dataCliente->srv = srv;
			dataCliente->clientI = sClientI;
			dataCliente->clientO = sClientO;
			srv->jugadoresConectados++;
			Thread clientThread("Client Thread",initClient,dataCliente);
		}

		// Avisa si todos estan conectados
		if ( srv->jugadoresConectados == srv->cantJugadores){
			srv->notifyAll();

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

	Condition* worldcond =  &srv->canCreate;
	Mutex* w =  &srv->worldlock;

	Condition* canStart =  &srv->canAddNews;
	Mutex* allIn =  &srv->playerslock;


	std::vector<uint8_t> datos(10);
	std::vector<uint8_t> keepaliveData(10);
	Messages keepaliveMsg = KEEPALIVE;
	EDatagram* datagram = new EDatagram();


	// Receive LOGIN info
	if (! ((threadData*)data)->clientO.rcvmsg(*datagram)) {
		
		printf("\nDesconectando cliente at login");
		closesocket(aThreadData->clientO.getFD());
		closesocket(aThreadData->clientI.getFD());
		srv->jugadoresConectados--;
		return 1;
	}

	w->lock();
	//Valido si puede estar en el nivel antes de avanzar
	Log::i("Valido nuevo cliente en el server - %d", datagram->playerID.c_str());
	if ( !srv->getGameEngine().registerPlayer(datagram->playerID) ){
		w->unlock();
		printf("\nCliente no permitido en el server");
		
		// envio Rechazo
		Sleep(1);
		EDatagram* msg = new EDatagram();
		msg->type = ALREADY_EXIST_USER;
		aThreadData->clientI.sendmsg(*msg);
		
		// Cierro socket abiertos del cliente
		closesocket(aThreadData->clientO.getFD());
		closesocket(aThreadData->clientI.getFD());
		srv->jugadoresConectados--;

		delete msg;
		return 1;
	} else {
		// envio LOGIN_OK
		w->unlock();
		EDatagram* msg = new EDatagram();
		msg->type = LOGIN_OK;
		((threadData*)data)->clientI.sendmsg(*msg);
	}
	


	
	
	srv->pList.insert(	std::make_pair<std::string,std::pair<Socket,Socket>>(datagram->playerID,
					std::make_pair(aThreadData->clientO,
					aThreadData->clientI)
					)
				);


	srv->inserPlayerIntotWorld(datagram->playerID);


	printf("\nCliente registrado satisfactoriamente en el servidor");
	std::strcpy((char*)playerId,datagram->playerID.c_str() );

	//Envio el nivel YAML al cliente
	ParserYaml* aParser = ParserYaml::getInstance();
	aThreadData->clientI.sendFile(aParser->getLevelFilePath());

	//En este punto el cliente se registro OK, chequeo si estan todos los players, si no espero.

	srv->playerMutexes[playerId].first->lock();
	
	while ( srv->pList.size() != srv->cantJugadores ){
		srv->playerMutexes[playerId].second->wait();
	}
	srv->playerMutexes[playerId].first->unlock();


	printf("\nElements at model: %d, sending to the client", srv->getGameEngine().getLevel()->getEntities().size() );
	int i = 0;
	std::string pl;
		
	//Notifico de todos los players que tengo en el mundo
	datagram->elements = srv->gameEngine.getLevel()->getAmountOfUsers();
	aThreadData->clientI.sendmsg(*datagram);
	printf("\nAmount of user into the level: %d",datagram->elements);

	std::map<std::string, GamePlayer*> gpcopy = srv->gameEngine.getLevel()->getPlayers();
	std::map<std::string, GamePlayer*>::iterator itGP = gpcopy.begin(); 
	
	//Por cada player envio sus elementos
	for ( ; itGP != gpcopy.end(); ++itGP ){
		datagram->playerID = itGP->second->playerID;
		datagram->playerState = srv->gameEngine.getLevel()->getPlayerStatus(itGP->second->playerID);
		int el = srv->gameEngine.getLevel()->getWormsFromPlayer(itGP->second->playerID,datagram->play);
		datagram->elements = el;
		printf("\nSending %d elements about player: %s at init",el,itGP->second->playerID.c_str());
		aThreadData->clientI.sendmsg(*datagram);
	}
	

	threadData* dataCliente = new threadData();
	dataCliente->srv = srv;
	dataCliente->clientI = aThreadData->clientI;
	dataCliente->clientO = aThreadData->clientO;
	std::strcpy(dataCliente->p,playerId);
	Thread clientThread("Update Client Thread",updateClient,dataCliente);

	//Sleep(10);

	//Tell everybody that a new player has arrived!
	srv->notifyUsersAboutPlayer(playerId);


	int activeClient=1;
		try {
		while (activeClient &&  srv->gameEngine.getLevel()->getPlayerStatus(playerId) != DISCONNECTED ) {
			Sleep(10);
			if (! aThreadData->clientO.rcvmsg(*datagram)) {
				printf("\nDesconectando cliente: %s",playerId );
				//srv->notifyUsersAboutPlayer(playerId);
				srv->disconnect(playerId);
				activeClient=0;
				break;
			}
			
			// Got something ;)
			/*m->lock();*/
			//try{
			//	printf("\nGot something from client %s ;)",playerId );
			//}catch(...){
			//	m->unlock();
			//	throw std::current_exception();
			//}

			switch (datagram->type) {
			case UPDATE:
				m->lock();
				Log::t("Got update, action %s to worm: %d",Util::actionString(datagram->play[0].action).c_str(), datagram->play[0].wormid);
				srv->changes.push_back(datagram->play[0]);


				cond->signal();
				m->unlock();

				break;

			case LOGIN:
				
				m->unlock();
				cond->signal();
				break;
			}
		}
	} catch (...) {
		srv->disconnect(playerId);
		throw std::current_exception();
	}
	printf("\nSali intacto");
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
	
	//No desconecto dos veces
	if ( this->gameEngine.getLevel()->getPlayerStatus(playerId) != DISCONNECTED ){
		Log::i("Releasing player: %s",playerId.c_str());
		printf("\nReleasing player: %s\n",playerId.c_str());
		this->gameEngine.getLevel()->disconnectPlayer(playerId);
		this->gameEngine.getLevel()->disconnectWormsFromPlayer(playerId);
		closesocket(this->pList[playerId].first.getFD());
		closesocket(this->pList[playerId].second.getFD());
		this->pList.erase(playerId);
		this->jugadoresConectados--;
		this->notifyUsersAboutPlayer(playerId);
		this->playerQueueStat.erase(playerId);

	}

}

void Servidor::notifyUsersAboutPlayer(std::string playerId){

	SDL_SemWait(this->advance);
	this->worldQ.type = PLAYER_UPDATE;
	this->worldQ.playerID = playerId;
	this->worldQ.playerState = this->gameEngine.getLevel()->getPlayerStatus(playerId);
	int el = this->gameEngine.getLevel()->getWormsFromPlayer(playerId,this->worldQ.play);
	this->worldQ.elements = el;
				
	printf("\nNOTIFYING NEWS: Sending type: %d (player_update), about: %s, elements: %d",this->worldQ.type, this->worldQ.playerID.c_str(), this->worldQ.elements);

	
	this->notifyAll();
	SDL_SemPost(this->advance);



}


int Servidor::updateClient(void* data){

	printf("\n\nUpdate Client Thread running for player: %s\n",static_cast<threadData*>(data)->p);

    threadData* aThreadData = (threadData*)data;

    Servidor* srv = aThreadData->srv;
    std::vector<Playable>* changes =  &srv->changes;

    Condition* netcond =  &srv->canBroadcast;
    Mutex* n =  &srv->netlock;

    char* playerId = aThreadData->p;

    EDatagram datagram;

    while(true){           
		//Sleep(25);
		srv->playerMutexes[playerId].first->lock();
		if ( srv->playerQueues[playerId]->empty() ){
			srv->playerMutexes[playerId].second->wait();
		}
		//printf("Messages at queue: %d", srv->playerQueues[playerId]->size() );
		//memcpy(datagram, &srv->playerQueues[playerId]->front() ,sizeof(EDatagram));
		datagram = srv->playerQueues[playerId]->front() ;
		srv->playerQueues[playerId]->pop();
		srv->playerMutexes[playerId].first->unlock();
		if ( datagram.type == PLAYER_UPDATE && !datagram.playerID.compare(playerId) )
			continue;
		//Log::i("Sending type: %d to %s",datagram.type,playerId);
		if ( !aThreadData->clientI.sendmsg(datagram) ){
			printf("Desconectando cliente: %s desde Update Thread",playerId);
			srv->disconnect(playerId);
			return 0;
		}
    }
    return 0;
}

void Servidor::resetWorldQ(){

	std::map<std::string,TransmitStatus> copy = this->playerQueueStat;
	std::map<std::string,TransmitStatus>::iterator it=copy.begin();

	for( ; it!=copy.end(); ++it)
		it->second = TX_WAIT;

}

void Servidor::setWorldQ(){

	std::map<std::string,TransmitStatus> copy = this->playerQueueStat;
	std::map<std::string,TransmitStatus>::iterator it=copy.begin();

	for( ; it!=copy.end(); ++it)
		it->second = TX_READY;

}

bool Servidor::allInWaitingStatus(){

	//bool flag = true;
	std::map<std::string,TransmitStatus> copy = this->playerQueueStat;
	std::map<std::string,TransmitStatus>::iterator it=copy.begin();

	for( ; it!=copy.end(); ++it){
		if ( it->second == TX_READY ){
			return false;
		}
	}

	return true;
}

void Servidor::inserPlayerIntotWorld(std::string pl){

	this->playerQueueStat[pl] = TX_WAIT;
	Mutex* m = new Mutex();
	Condition* c = new Condition(*m);
	this->playerMutexes[pl] = std::make_pair(m,c);
	this->playerQueues[pl] = new queue<EDatagram>;


}


void Servidor::notifyAll(){

	std::map<std::string,std::pair<Mutex*,Condition*>> mutexes = this->playerMutexes;
	std::map<std::string,std::pair<Mutex*,Condition*>>::iterator itm=mutexes.begin();

	for( ; itm!=mutexes.end(); ++itm){
		itm->second.first->lock();
		this->playerQueues[itm->first]->push( this->worldQ );
		itm->second.second->signal();
		itm->second.first->unlock();
	}


}