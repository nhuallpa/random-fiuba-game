
#include "./Cliente.h"



Cliente::~Cliente(void){

}

bool Cliente::begin(){
	// TODO @future: Initialize sockets
	//this->connect2server(this->server);
	return true;
}



void Cliente::loop(void){
	Log::i("============== INICIANDO CLIENTE =============");		

	Uint32 start = 0;
	bool quit = false;

	bootstrap.init();

	GameViewBuilder* builder = new GameViewBuilder(&this->cController, &this->domain, &bootstrap.getScreen());
	builder->setPlayerID(this->pl);
	this->currentActivity = new GameActivity (bootstrap.getScreen(), *builder, &this->cController, this->pl);
	this->gameActivity = static_cast<GameActivity*> (currentActivity);
	
	
	/** refresh the initial view*/
	this->currentActivity->render();
	this->cController.addListener(this);


	informStateClient();
	FPSmanager fpsManager;
	fpsManager.rate = 60;
	SDL_initFramerate(&fpsManager);
	while (!this->cController.isQuit()){
		cController.handlerEvent();
		this->runGame();
		currentActivity->update();
		currentActivity->render();
		SDL_framerateDelay(&fpsManager);
	}
	cController.destroy();
	bootstrap.shoutDown();
	delete currentActivity;
	delete builder;

}

bool Cliente::run(){

	if( this->begin() == true ){
		this->loop();
	}else{
		Log::e("Error al iniciar el juego el cliente");
		return false;
	}
	return true;
}

void Cliente::destroyWorld(void){
	//TODO: Destructor
}

void Cliente::informStateClient()
{
	if (this->srvStatus == SERVER_NOT_RESPONDING)
	{
		this->currentActivity->showMessageError("El servidor no responde. Vuelva a conectarse mas tarde");
	}
	else if (this->srvStatus == SERVER_TIMEDOUT)
	{
		this->currentActivity->showMessageError("El servidor ha dejado de responder");
	}
	else if (this->srvStatus == SERVER_OK)
	{
		this->currentActivity->showMessageInfo("Se ha registrado correctamente");
	}
}


void Cliente::runGame(){
	bootstrap.getScreen().setState("Juego corriendo");
}


/************************ Start Network Client Side code *************************/
Cliente::Cliente(std::string playerID, const char* ip, int port)
	: input(Socket())
	, output(Socket())
	, pl(playerID)
	, localChanges()
	, networkChanges()
	, m()
	, n()
	, somethingToTell(m)
	, somethingToUpdate(n)
	, domain()
{
	this->loginOk = false;
	bool stat = input.connect2(ip, port+1);
	if (!stat){
		this->srvStatus = SERVER_NOT_RESPONDING;
		return;
	}

	Log::i("Connected to data port: %d", port);
	
	stat = output.connect2(ip, port);
	if (!stat){
		this->srvStatus = SERVER_NOT_RESPONDING;
		return;
	}

	//input.setRcvTimeout(15,5);
	//output.setRcvTimeout(15,5);
	//input.setSendTimeout(15,5);
	//output.setSendTimeout(15,5);

	//input.setKeepAlive();
	//output.setKeepAlive();

	Log::i("Connected to update port: %d", port+1);
	this->srvStatus = SERVER_OK;

	this->data.cli = this;
	this->domain.setPlayerID(this->pl);

	getRemoteWorld(); // recibo el mundo o un codigo de reject
	if (this->isLoginOk()){
		//Thread de escucha de mensajes en la red
		Thread networkUpdatesThread("Net Updates",applyNetworkChanges,&data);

		//Thread de keepalive (Listen for disconnect)
		Thread keepaliveThread("Listening",netListener,&data);

		//Thread de escucha de actualizaciones locales
		Thread localUpdatesThread("LocalUpdates",notifyLocalUpdates,&data);

		//Thread de simulacion de cambios locales
		//Thread clientSideThread("Emulation",clientSideEmulation,&data);
	}
	

}


int Cliente::clientSideEmulation(void *data){

	printf("\nDisparado apply Network Changes thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	Condition* cond = &((Cliente*)((threadData*)data)->cli)->somethingToTell;
	
	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;
	
	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();
	msg->type = KEEPALIVE;
	size_t i = 0;

	while(true){
		//copy and (un)comment this to mock local changes
		Sleep(10);
		i++;

		//Esto es lo que se va disparar al haber una accion del lado del cliente
		if ( i == 500 || i == 2000 ){
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


int Cliente::applyNetworkChanges(void *data){
	Sleep(10);
	Log::i("Cliente::applyNetworkChanges >> Disparado apply Network Changes thread");
	Cliente* cli = ((threadData*)data)->cli;
	
	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;
	
	char* playerId = ((threadData*)data)->p;
	EDatagram* msg = new EDatagram();
	msg->type = KEEPALIVE;

	while(true){

		Sleep(1); // Nestor: lo paso a uno para que se actualizan rapdido los cambios

		// Wait for network updates from server
		n->lock(); //Nestor: cambio de lugar porque me parece que el netListener se bloquearia en un caso
				   //Ariel: No, si esta vacia espera (eso lo desbloquea), si no esta vacia ya tiene el lock	
				   // y opera tranquilo
		if ( cli->networkChanges.empty() ){
			netcond->wait();
		}
		if (cli->networkChanges.size() > 1) {
			Log::t("Cliente::applyNetworkChanges >> Mas de un cambio para actualizar");
		}
		//n->lock();
		while (!cli->networkChanges.empty())
		{	
			Playable p;
			p = cli->networkChanges.front();

			cli->updateModel(p);

			cli->networkChanges.pop();
		}
		n->unlock();
	}

	return 0;

}


bool Cliente::updateModel(Playable p){

	this->domain.updateElement(p.wormid, p.x, p.y, p.action );
	return true;
}

//
int Cliente::notifyLocalUpdates(void *data){
	Log::i("Cliente::notifyLocalUpdates >> Disparado notify local updates thread");
	threadData* aThreadData = (threadData*)data;
	Cliente* cli = aThreadData->cli;
	Mutex* m = &cli->m;
	Condition* cond = &(cli->somethingToTell);
	char* playerId = aThreadData->p;
	EDatagram* msg = new EDatagram();

	while(true){
		m->lock();
		if ( cli->localChanges.empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		Log::t("\nGot a local change");

		msg->play[0].wormid = cli->localChanges.back().wormid;
		msg->play[0].weaponid = cli->localChanges.back().weaponid;
		msg->play[0].state = cli->localChanges.back().state;
		msg->play[0].action = cli->localChanges.back().action;
		msg->playerID = cli->pl.c_str();

		msg->type = UPDATE;

		if ( !cli->output.sendmsg(*msg) ) {
			Log::t("Local Update - Client connection with server error");
			cli->srvStatus = SERVER_TIMEDOUT;
			cli->informStateClient();
			m->unlock();
			return 1;
		}

		cli->localChanges.pop_back();
		m->unlock();
	}
	return 0;
}


int Cliente::netListener(void* data){
	Sleep(10);
	Log::i("Cliente::netListener >> Disparado net listen thread");
	Cliente* cli = ((threadData*)data)->cli;

	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();
	EDatagram* emsg = new EDatagram();

	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;

	while(true){
		Sleep(10);
	
		if ( !cli->input.rcvmsg(*emsg) ) {
			Log::e("\nNETLISTENER: Desconectando cliente at listening state");
			cli->srvStatus = SERVER_TIMEDOUT;
//			cli->informStateClient();
			//TODO: metodo de desconexion del server, mensaje y grisar pantalla o retry

			return 1;
		}
		//printf("\nGot network change");
		switch(emsg->type){
		case UPDATE:
			Log::t("Got UPDATE message from server");
			n->lock();
			try{
				//printf("\nGot something from client %s at i: %d ;)",playerId,i );
				Playable p;

				// Esto deberia ser mas rapido, quizas lo meta en un vector de edatagrams
				// que se van a ir vaciando del lado del cliente
				for ( int i=0; i < emsg->elements; i++){
					p.wormid = emsg->play[i].wormid;
					//p.weaponid = emsg->play[i].weaponid;
					p.x = emsg->play[i].x;
					p.y = emsg->play[i].y;
					p.action = emsg->play[i].action;
					Log::d("Recibo accion %s para worm %d", Util::actionString(p.action).c_str(), p.wormid);
					cli->networkChanges.push(p);
					Log::d("Getted wormid: %d at pos x: %f, y: %f",p.wormid,p.x, p.y);
				}

			}catch(...){
				n->unlock();
				throw std::current_exception();
				break;
			}
			
			n->unlock();
			if ( emsg->elements ){
				netcond->signal();
			}

			break;
		case PLAYER_UPDATE:
			//Add the user to the players that are playing list
			Log::i("Updated player: %s state to %d",emsg->playerID.c_str(), emsg->playerState);
			cli->domain.addPlayer(emsg->playerID,emsg->playerState,0);
			
			if (emsg->playerState == CONNECTED)
			{
				Log::d("El usuario %s se ha CONECTADO ", emsg->playerID.c_str());
				int i=0;
				for (i=0; i< emsg->elements; i++) 
				{
					cli->addPlayerToView(emsg->playerID, emsg->play[i].wormid, emsg->play[i].x, emsg->play[i].y );
					Log::d("Adding to View Player %s, wormid: %d, X: %f, Y: %f",emsg->playerID.c_str(), emsg->play[i].wormid, emsg->play[i].x, emsg->play[i].y);
				}
				cli->getCurrentActivity()->showMessageInfo("El usuario " + emsg->playerID + " ha ingresado");	
			}
			else if (emsg->playerState == DISCONNECTED)
			{
				Log::d("El usuario %s se ha DESCONECTADO ", emsg->playerID.c_str());
				cli->getCurrentActivity()->showMessageInfo("El usuario " + emsg->playerID + " se ha desconectado");	
			}
			else if (emsg->playerState == RECONNECTED)
			{
				Log::d("El usuario %s se ha RECONECTADO ", emsg->playerID.c_str());
				cli->getCurrentActivity()->showMessageInfo("El usuario " + emsg->playerID + " se ha reconectado");	
			}
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

	//Nestor: Evaluar si fue aceptado

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

bool Cliente::doLogin()
{
		Messages type = LOGIN;
	std::vector<uint8_t> datos;
	std::vector<uint8_t> buffer;
	EDatagram* msg = new EDatagram();
	
	//Login to server
	msg->type = LOGIN;
	msg->playerID = this->pl; 

	Log::t("Sending login info ");
	if ( !this->output.sendmsg(*msg) ) {
		Log::e("Client: Login request connection error");
		this->srvStatus = SERVER_NOT_RESPONDING;
		return false;
	}
	// recibo confirmacion de login
	EDatagram* datagram = new EDatagram();
	if ( !this->input.rcvmsg(*datagram) ) {
		Log::e("Client: Login response connection error");
	}
	if (datagram->type == ALREADY_EXIST_USER) {
		Log::i("Client: El usuario ya esta registrado y jugando en el servidor");
		return false;
	} else if (datagram->type == LOGIN_OK) {
		Log::i("Client: Login con exito");
		this->loginOk = true;
		return true;
	} else {
		Log::i("Client: Login ERROR - rta %d" ,datagram->type);
		return false;
	}
	delete datagram;

}

void Cliente::getRemoteWorld() {

	EDatagram* msg = new EDatagram();
	if (!this->doLogin()){
		Log::t("Failed login, exiting");
		return;
	}
	// Get YAML
	this->input.receiveFile("res/levels/clienteyaml.yaml");

	//Get amount of users from the server
	Log::t("Getting amount of users from server ");
	if (!this->input.rcvmsg(*msg)) {
		Log::e("Client: connection error - Server disconnected/not responding while retrieving amount of users");
		this->srvStatus = SERVER_NOT_RESPONDING;
		return;
	}

	int count = msg->elements;
	Log::i("Going to load %d players",count);

	for ( int i=0 ; i < count ; i++ ){
		Log::t("Loading player: %d ",i);
		if (!this->input.rcvmsg(*msg)) {
			Log::e("Client: connection error - Server disconnected/not responding while retrieving their worms");
			this->srvStatus = SERVER_NOT_RESPONDING;
			return;
		}
		int els = msg->elements;

		for ( int j=0; j < els; j++){

			Log::i("Got worm id: %d at pos: %f, %f, action: %d",msg->play[j].wormid, msg->play[j].x, msg->play[j].y, msg->play[j].action);

			//Trigger changes into game elements of the client
			GameElement* elem = getElementFromPlayable(msg->play[j]);
			elem->playerID = msg->playerID;
			elem->setAction( msg->play[j].action );
			this->domain.addElementToDomain(*elem);

			if ( msg->play[j].action == NOT_CONNECTED ){
				//Set user disconnected
				this->domain.addPlayer(msg->playerID,DISCONNECTED,0);
			}else
				this->domain.addPlayer(msg->playerID,CONNECTED,0);
		}
	}
	delete msg;
}



bool Cliente::serverAlive () {
	return this->srvStatus;
}


GameElement* Cliente::getElementFromPlayable(Playable p){

	GameElement* g = new GameElement(p.wormid,"PLAYER 1",WORM,p.x,p.y,0.0,40,40,15,false);

	return g;

}






void Cliente::lockLocalMutex(){
	this->m.lock();
}

void Cliente::unlockLocalMutex(){
	this->m.unlock();
}

void Cliente::lockNetworkMutex(){
	this->n.lock();
}

void Cliente::unlockNetworkMutex(){
	this->n.unlock();
}

void Cliente::addLocalChange(Playable p){
	this->localChanges.push_back(p);
}

void Cliente::signalLocalChange(){
	this->somethingToTell.signal();
}

void Cliente::signalNetworkChange(){
	this->somethingToUpdate.signal();
}

int Cliente::sendMsg(Messages type, std::vector<uint8_t> buffer) {
	if ( !this->output.sendmsg(type, buffer) ) {
		Log::e("connection error");
		//printf("Client: connection error");
		return 1;
	}
	return 0;

}

void Cliente::addLocalMovementFromView(Playable p){

	this->m.lock();
	try{
		this->localChanges.push_back(p);
	}catch(...){
		this->m.unlock();
		throw std::current_exception();
	}
	this->m.unlock();
	this->somethingToTell.signal();

}

//TODO: pasar a gameActivity
void Cliente::OnMovement(MovementEvent e){

	Playable p;
	int wormIdSelected = this->gameActivity->getWormIdSelected();

	if (wormIdSelected > 0 && 
		this->gameActivity->isThisClientOwner(wormIdSelected) && 
		this->gameActivity->isAlive(wormIdSelected))
	{
		p.wormid = wormIdSelected;
		if (e.y == -1)  // Solo saltar
		{
			if (e.x == 1) //Salta derecha
			{
				p.action = 	JUMP_RIGHT;
				Log::t("CLIENTE: Saltar derecha");
			}
			else if (e.x == -1) // Saltar izquierda
			{
				p.action = 	JUMP_LEFT;
				Log::t("CLIENTE: Saltar izquierda");
			} 
			else 
			{
				p.action = 	JUMP;
				Log::t("CLIENTE: Saltar");
			}
		}
		else if (e.x == 1) // derecha
		{
			p.action = 	MOVE_RIGHT;
		}
		else if (e.x == -1) // izquierda
		{
			p.action = 	MOVE_LEFT;
		} 
		else if (e.x == 0) // quieto
		{
			p.action = 	MOVE_STOP;
		}
		this->addLocalMovementFromView(p);
	}

	
}

void Cliente::addPlayerToView(std::string playerID, int idWorm, int x, int y)
{
	GameActivity * aGameActivity = static_cast<GameActivity *>(currentActivity);
	aGameActivity->buildNewWorms(playerID, idWorm, x, y);
}

