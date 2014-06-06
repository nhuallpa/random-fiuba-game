#include "Servidor.h"
//
//Servidor::Servidor()
//	: input ()
//	, output ()
//	, cantJugadores()
//	, changes ()
//	, lock()
//	, netlock()
//	, canUpdate(lock)
//	, canBroadcast(netlock)
//{
//}

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
	, worldlock()
	, canUpdate(lock)
	, canBroadcast(netlock)
	, canCreate(worldlock)
{

	jugadoresConectados = 0;

	//Carga el servidor con un nivel, ese nivel tiene el terreno y su fisica y los jugadores que han
	// sido registrados en el
	this->gameEngine.initWorld();


	/* Start threading stuff */

	this->data.srv = this;

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
		Sleep(30);
		m->lock();
		if ( changes->empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		printf("\nUpdating: doing stuff at server side");
		Playable p;
		p = srv->changes.back();
		printf("\nGot message from user requesting to move worm %d to %d",p.wormid,p.action);
		
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
	std::vector<Playable>* changes =  &srv->changes;
	
	Condition* cond =  &srv->canUpdate;
	Mutex* m = &srv->lock;

	Condition* netcond =  &srv->canBroadcast;
	Mutex* n =  &srv->netlock;

	Condition* worldcond =  &srv->canCreate;
	Mutex* w =  &srv->worldlock;

	EDatagram* datagram = new EDatagram();

	int i=0;

	while(true){
		Sleep(30);
		//One step into the world
		w->lock();
		srv->getGameEngine().step();
		w->unlock();
		n->lock();
		
		//si algo cambio actualizo a los clientes
		if ( i>=3 ){
			
			i=0;
			srv->somethingChange();

			//chequeo si hay clientes
			if ( srv->pList.size() ){
				
				std::map<std::string, std::pair<Socket,Socket>> copy = srv->pList;
				std::map<std::string, std::pair<Socket,Socket>>::iterator it = copy.begin();

				//Por cada cliente le envio los cambios
				srv->worldQ.type = UPDATE;
				for ( ; it != copy.end() ; ++it){
					it->second.second.sendmsg(srv->worldQ);
					//printf("\nSended to the client, wormid %d, x: %f, y: %f",srv->worldQ.play[0].wormid,srv->worldQ.play[0].x, srv->worldQ.play[0].y);
				}
			}
		}
		n->unlock();
		i++;
	}
	return 0;
}

bool Servidor::somethingChange(){

	std::map<int,GameElement*> copy = this->gameEngine.getLevel()->getEntities();
	std::map<int,GameElement*>::iterator it = copy.begin();

	bool flag = false;
	int i=0;

	for ( ; it != copy.end() ; ++it){
		if( it->second->changed ){
			this->worldQ.play[i].wormid = it->second->getId();
			this->worldQ.play[i].x = it->second->getPosition().first;
			this->worldQ.play[i].y = it->second->getPosition().second;
			flag = true;
			i++;
		}
		if ( !static_cast<Worm*>(it->second)->isAlive() ){

			//Envio data de que esta muerto (x=-1,y=-1) y lo elimino del mundo
			this->gameEngine.getLevel()->removeEntity(it->second->getId());
		}

	}

	this->worldQ.elements = i+1; 
	printf("\nUpdated %d elements at this step",i);
	////TODO: Remover
	//for ( ; i != 15; i++)
	//	this->worldQ.play[i].wormid = 0;

	return flag;
}


bool Servidor::updateModel(Playable p){

	//Apply playable to the world, locate wormid and apply the action
	this->gameEngine.applyAction2Element(p.wormid,p.action);

	//Make a step into the world
	//this->gameEngine.step();

	//Look for changes in the world, if something change 
	//somethingChange()

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

	Condition* worldcond =  &srv->canCreate;
	Mutex* w =  &srv->worldlock;

	std::vector<uint8_t> datos(10);
	std::vector<uint8_t> keepaliveData(10);
	Messages keepaliveMsg = KEEPALIVE;
	EDatagram* datagram = new EDatagram();


	// Receive LOGIN info
	if (! ((threadData*)data)->clientO.rcvmsg(*datagram)) {
		printf("\nDesconectando cliente at login");
		srv->disconnect(playerId);
		return 1;
	}


	srv->pList.insert(	std::make_pair<std::string,std::pair<Socket,Socket>>(datagram->playerID,
						std::make_pair(aThreadData->clientO,
						aThreadData->clientI)
						)
					);


	w->lock();
	//Valido si puede estar en el nivel antes de avanzar
	if ( !srv->getGameEngine().registerPlayer(datagram->playerID) ){
		printf("\Cliente no permitido en el server");
		srv->disconnect(playerId);
		return 1;
	}
	w->unlock();
	printf("\nCliente registrado satisfactoriamente en el servidor");
	
	std::strcpy((char*)playerId,datagram->playerID.c_str() );

	//Envio el nivel YAML al cliente
	ParserYaml* aParser = ParserYaml::getInstance();
	aThreadData->clientI.sendFile(aParser->getLevelFilePath());


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
		printf("\nSending %d elements at init",el);
		aThreadData->clientI.sendmsg(*datagram);
	}
	
	//Tell everybody that a new player has arrived!
	srv->notifyUsersAboutPlayer(playerId);

	int activeClient=1;
		try {
		while (activeClient) {
			Sleep(30);
			if (! aThreadData->clientO.rcvmsg(*datagram)) {
				printf("\nDesconectando cliente: %s",playerId );
				srv->notifyUsersAboutPlayer(playerId);
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
				printf("\nGot update");
				srv->changes.push_back(datagram->play[0]);

				m->unlock();
				cond->signal();


				break;

			case LOGIN:
				
				m->unlock();
				cond->signal();
				break;
			}
		}
	} catch (...) {
		//srv->desconectar(playerId);
		throw std::current_exception();
	}
	printf("\nAbandonando cliente: %s\n",playerId);
	srv->notifyUsersAboutPlayer(playerId);




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
	this->gameEngine.getLevel()->disconnectPlayer(playerId);
	closesocket(this->pList[playerId].first.getFD());
	closesocket(this->pList[playerId].second.getFD());
	this->pList.erase(playerId);
	this->jugadoresConectados--;
	this->notifyUsersAboutPlayer(playerId);

}

void Servidor::notifyUsersAboutPlayer(std::string playerId){

	//send message to all the users telling abut the news of the player
	
	EDatagram* datagram = new EDatagram();

	datagram->type = PLAYER_UPDATE;
	datagram->playerID = playerId;
	datagram->playerState = this->gameEngine.getLevel()->getPlayerStatus(playerId);

	int el = this->gameEngine.getLevel()->getWormsFromPlayer(playerId,datagram->play);
	printf("\nSending %d elements",el);
	datagram->elements = el;

	std::map<std::string, std::pair<Socket,Socket>> copy = this->pList;
	std::map<std::string, std::pair<Socket,Socket>>::iterator it = copy.begin();

	for ( ; it != copy.end() ; ++it){
		//send over the network
		if ( it->first.compare(playerId) )
			it->second.second.sendmsg(*datagram);

	}

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