
#include "./Cliente.h"


Cliente::Cliente(std::string playerID, std::string ip, int port)
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
	, domainMx()
	, updateDomain(domainMx)
	, serverPort(port)
	, serverIp(ip)
{
	this->loginOk = false;
	this->advance = SDL_CreateSemaphore( 1 );
	
}

Cliente::~Cliente(void){

}


bool Cliente::run(){

	if( this->begin()){
		this->loop();
	}else{
		Log::e("Error al iniciar el juego el cliente");
		return false;
	}
	return true;
}

/************************ Start Network Client Side code *************************/
bool Cliente::begin(){

	bool stat = input.connect2(serverIp.c_str(), serverPort+1);
	if (!stat){
		this->srvStatus = SERVER_NOT_RESPONDING;
		return false;
	}

	Log::i("Connected to data port: %d", serverPort);
	
	stat = output.connect2(serverIp.c_str(), serverPort);
	if (!stat){
		this->srvStatus = SERVER_NOT_RESPONDING;
		return false;
	}

	Log::i("Connected to update port: %d", serverPort+1);
	this->srvStatus = SERVER_OK;

	this->data.cli = this;
	this->domain.setPlayerID(this->pl);

	getRemoteWorld(); // recibo el mundo o un codigo de reject
	if (this->isLoginOk())
	{
		//Thread de escucha de mensajes en la red
		Thread networkUpdatesThread("Net Updates",applyNetworkChanges,&data);

		//Thread de keepalive (Listen for disconnect)
		Thread keepaliveThread("Listening",netListener,&data);

		//Thread de escucha de actualizaciones locales
		Thread localUpdatesThread("LocalUpdates",notifyLocalUpdates,&data);
		return true;
	}
	else
	{
		return false;
	}
}

void Cliente::loop(void){
	Log::i("============== INICIANDO CLIENTE =============");		


	Uint32 start = 0;
	bool quit = false;

	bootstrap.init();

	GameViewBuilder* builder = new GameViewBuilder(&this->domain, &bootstrap.getScreen());
	builder->setPlayerID(this->pl);
	this->currentActivity = new GameActivity (bootstrap.getScreen(), *builder, &this->cController, this->pl);
	
	this->gameActivity = static_cast<GameActivity*> (currentActivity);
	this->gameActivity->wormIdDesSelected = -1;
	
	
	/** refresh the initial view*/
	this->currentActivity->render();
	this->cController.addListener(this);


	informStateClient();
	FPSmanager fpsManager;
	fpsManager.rate = 30;
	SDL_initFramerate(&fpsManager);
	while (!this->cController.isQuit()){
		
		if (this->gameActivity->wormIdDesSelected > 0) {
			Playable p;
			p.action = MOVE_STOP;
			p.wormid = this->gameActivity->wormIdDesSelected;
			this->addLocalMovementFromView(p);
			this->gameActivity->wormIdDesSelected = -1;
		}

		cController.handlerEvent();
		this->runGame();
		//SDL_SemWait(this->advance);
		currentActivity->update();
		currentActivity->render();
		//SDL_SemPost(this->advance);
		SDL_framerateDelay(&fpsManager);
	}

	if (this->gameActivity->wormIdSelected > 0) 
	{
		Playable p;
			p.action = MOVE_STOP;
			p.wormid = this->gameActivity->wormIdSelected;
			this->addLocalMovementFromView(p);
			this->gameActivity->wormIdSelected = -1;
	}
	cController.destroy();
	bootstrap.shoutDown();
	this->disconnectClient();
	delete currentActivity;
	delete builder;

}


void Cliente::disconnectClient(){

	//closesocket(this->input.getFD());
	//closesocket(this->output.getFD());

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
	bootstrap.getScreen().setState("Jugando como " + this->pl);
}




int Cliente::applyNetworkChanges(void *data){
	Log::i("Cliente::applyNetworkChanges >> Disparado apply Network Changes thread");
	Cliente* cli = ((threadData*)data)->cli;
	
	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;
	
	char* playerId = ((threadData*)data)->p;
	EDatagram* msg = new EDatagram();
	msg->type = KEEPALIVE;

	while(true && !cli->cController.isQuit() ){

		Sleep(1); 

		// Wait for network updates from server
		n->lock(); //Nestor: cambio de lugar porque me parece que el netListener se bloquearia en un caso
				   //Ariel: No, si esta vacia espera (eso lo desbloquea), si no esta vacia ya tiene el lock	
				   // y opera tranquilo
		while ( cli->clientQueue.empty() ){
			netcond->wait();
		}
		EDatagram temp = cli->clientQueue.front();
		cli->clientQueue.pop();
		n->unlock();

		Playable p;

		//SDL_SemWait(cli->advance);
		
		for ( int i=0; i < temp.elements; i++){
			p.wormid = temp.play[i].wormid;
			//p.weaponid = emsg->play[i].weaponid;
			p.x = temp.play[i].x;
			p.y = temp.play[i].y;
			p.action = temp.play[i].action;
			cli->updateModel(p);
			//Log::i("\nProcessing wid: %d, x: %f, y: %f", p.wormid,p.x,p.y);
		}
		//SDL_SemPost(cli->advance);
	}

	Log::i("Cliente::applyNetworkChanges >> Terminado apply Network Changes thread");
	return 0;

}


bool Cliente::updateModel(Playable p){

	this->domainMx.lock();
	this->domain.updateElement(p.wormid, p.x, p.y, p.action );
	this->domainMx.unlock();
	return true;
}


int Cliente::notifyLocalUpdates(void *data){
	Log::i("Cliente::notifyLocalUpdates >> Disparado notify local updates thread");
	threadData* aThreadData = (threadData*)data;
	Cliente* cli = aThreadData->cli;
	Mutex* m = &cli->m;
	Condition* cond = &(cli->somethingToTell);
	char* playerId = aThreadData->p;
	EDatagram* msg = new EDatagram();

	while(true && !cli->cController.isQuit()){
		m->lock();
		if ( cli->localChanges.empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		Log::t("\nGot a local change");

		msg->play[0].wormid = cli->localChanges.back().wormid;
		//msg->play[0].weaponid = cli->localChanges.back().weaponid;
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

	Log::i("Cliente::notifyLocalUpdates >> Terminado notify local updates thread");
	return 0;
}


int Cliente::netListener(void* data){

	Log::i("Cliente::netListener >> Disparado net listen thread");
	Cliente* cli = ((threadData*)data)->cli;

	char* playerId = ((threadData*)data)->p;
	EDatagram* emsg = new EDatagram();

	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;

	while(true && !cli->cController.isQuit() ){
		Sleep(10);
	
		if ( !cli->input.rcvmsg(*emsg) ) {
			Log::e("\nNETLISTENER: Desconectando cliente at listening state");
			cli->srvStatus = SERVER_TIMEDOUT;
			return 1;
		}
		//printf("\nGot network change");
		switch(emsg->type){
		case UPDATE:
			//Log::t("Got UPDATE message from server");
			
			try{
				//Log::i("\nGot something from client %s worm: %d posY: %f",emsg->playerID.c_str(),emsg->play[0].wormid,emsg->play[0].y);
				n->lock();
				cli->clientQueue.push(*emsg);
				
				netcond->signal();
				n->unlock();

			}catch(...){
				
				throw std::current_exception();
				break;
			}
			
			
			break;
		case PLAYER_UPDATE:
			//Add the user to the players that are playing list
			Log::i("Updated player: %s state to %d",emsg->playerID.c_str(), emsg->playerState);
			cli->domain.addPlayer(emsg->playerID,emsg->playerState,0);
			/*n->lock();*/
			if (emsg->playerState == CONNECTED)
			{
				Log::d("El usuario %s se ha CONECTADO ", emsg->playerID.c_str());
				int i=0;
				//SDL_SemWait(cli->advance);
				cli->domainMx.lock();
				for (i=0; i< emsg->elements; i++) 
				{
					
					cli->addPlayerToView(emsg->playerID, emsg->play[i].wormid, emsg->play[i].x, emsg->play[i].y );
					
					Log::i("Adding to View Player %s, wormid: %d, X: %f, Y: %f",emsg->playerID.c_str(), emsg->play[i].wormid, emsg->play[i].x, emsg->play[i].y);
				}
				//SDL_SemPost(cli->advance);
				cli->domainMx.unlock();
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
			/*n->unlock();*/
			break;
		}
	
	}

	Log::i("Cliente::netListener >> Terminado net listen thread");
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
		this->domainMx.lock();
		for ( int j=0; j < els; j++){

			Log::i("Got worm id: %d at pos: %f, %f, action: %s",msg->play[j].wormid, msg->play[j].x, msg->play[j].y, Util::actionString(msg->play[j].action).c_str());

			//Trigger changes into game elements of the client
			GameElement* elem = getElementFromPlayable(msg->play[j]);
			elem->playerID = msg->playerID;
			elem->setAction( msg->play[j].action );
			
			this->domain.addElementToDomain(*elem);
			
			if ( msg->play[j].action == NOT_CONNECTED_RIGHT || msg->play[j].action == NOT_CONNECTED_LEFT || msg->play[j].action == NOT_CONNECTED){
				//Set user disconnected
				this->domain.addPlayer(msg->playerID,DISCONNECTED,0);
			}else
				this->domain.addPlayer(msg->playerID,CONNECTED,0);
		}
		this->domainMx.unlock();

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
			//if (e.x == 1) //Salta derecha
			//{
			//	p.action = 	JUMP_RIGHT;
			//	Log::t("CLIENTE: Saltar derecha");
			//}
			//else if (e.x == -1) // Saltar izquierda
			//{
			//	p.action = 	JUMP_LEFT;
			//	Log::t("CLIENTE: Saltar izquierda");
			//} 
			//else 
			//{
				p.action = 	JUMP;
				Log::t("CLIENTE: Saltar");
			//}
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
	this->domain.printDomain();
}

