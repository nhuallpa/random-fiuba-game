
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
	, updater(&input, &output,&m,&n,&somethingToTell,&localChanges)
{
	this->loginOk = false;
	this->advance = SDL_CreateSemaphore( 1 );

	this->gameReady = false;
	this->gameOver = false;
	
}

Cliente::~Cliente(void){

}


void Cliente::run(){

	if (!this->begin()){
		Log::e("Error al iniciar el juego el cliente");
	}
	this->loop();
}

/************************ Start Network Client Side code *************************/
bool Cliente::openConnection() {
	
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
	return true;
}

bool Cliente::begin(){

	if (!this->openConnection())
	{
		return false;
	}

	this->data.cli = this;
	this->domain.setPlayerID(this->pl);
	this->updater.setPlayerId(this->pl);


	if (this->updater.doLogin())
	{
		this->loginOk = true;
	}

	if (this->isLoginOk())
	{
		updater.retrieveLevel();

		// lo voy a lanzar despues de que el server me diga que comience el juego
		//getRemoteWorld(); 

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


void Cliente::getRemoteWorld() {

	EDatagram* msg = new EDatagram();
	
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
			GameElement* elem = getElementFromPlayable(msg->playerID, msg->play[j]);
					
			this->domain.addElementToDomain(*elem);
			
			if ( msg->play[j].action == NOT_CONNECTED_RIGHT || msg->play[j].action == NOT_CONNECTED_LEFT || msg->play[j].action == NOT_CONNECTED){
				//Set user disconnected
				this->domain.addPlayer(msg->playerID,DISCONNECTED,0);
			}else
				this->domain.addPlayer(msg->playerID,CONNECTED,0);
		}
		this->domainMx.unlock();

	}
	this->gameReady = true;
	//delete msg;
}



void Cliente::loop(void){
	Log::i("============== INICIANDO CLIENTE =============");		

	bool quit = false;

	bootstrap.init();
	this->waitActivity = new WaitActivity(bootstrap.getScreen());	
	this->gameActivity = new GameActivity(bootstrap.getScreen(), &this->domain, &this->cController, this->pl, this->updater);	
	
	/*if (this->loginOk) 
	{
		this->currentActivity = this->gameActivity;
	} 
	else 
	{*/
		this->currentActivity = this->waitActivity;
	//}
	
	this->runGame();

	/** refresh the initial view*/
	this->currentActivity->render();
	informStateClient();
	FPSmanager fpsManager;
	fpsManager.rate = 30;
	SDL_initFramerate(&fpsManager);
	
	while (!this->cController.isQuit()){		
		cController.handlerEvent();
		currentActivity->update();
		currentActivity->render();
		// evaluar cambio de pantalla

		if (this->gameReady) 
		{
			this->currentActivity = this->gameActivity;
		} 
		else if (this->gameOver) 
		{
			this->currentActivity = this->waitActivity;
		}

		SDL_framerateDelay(&fpsManager);
	}
	currentActivity->stop();
	cController.destroy();
	
	this->disconnectClient();
	delete this->gameActivity;
	delete this->waitActivity;

	bootstrap.shoutDown();
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
	Sleep(45);
	Log::i("Cliente::netListener >> Disparado net listen thread");
	threadData* tData = (threadData*)data;
	Cliente* cli = tData->cli;
	char* playerId = tData->p;
	Mutex* n = &(cli)->n;
	Condition* netcond = &(cli)->somethingToUpdate;


	// Si recibo un GAME START puedo iniciar el Juego
	
	
	cli->getRemoteWorld();

	EDatagram* emsg = new EDatagram();
	bool closeListen = false;
	while(!cli->cController.isQuit() && !closeListen){
		Sleep(10);
	
		if ( !cli->input.rcvmsg(*emsg) ) {
			Log::e("\nNETLISTENER: Desconectando cliente at listening state");
			cli->srvStatus = SERVER_TIMEDOUT;
			closeListen = true;
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
	delete emsg;
	Log::i("Cliente::netListener >> Terminado net listen thread");
	return 0;
}

bool Cliente::serverAlive () {
	return this->srvStatus;
}

GameElement* Cliente::getElementFromPlayable(std::string playerID, Playable p){

	GameElement* g = new GameElement(p.wormid,"PLAYER 1",WORM,p.x,p.y,0.0,40,40,15,false);
	g->playerID = playerID;
	g->setAction( p.action );
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

void Cliente::addPlayerToView(std::string playerID, int idWorm, int x, int y)
{
	GameActivity * aGameActivity = static_cast<GameActivity *>(currentActivity);
	aGameActivity->buildNewWorms(playerID, idWorm, x, y);
	//this->domain.printDomain();
}

