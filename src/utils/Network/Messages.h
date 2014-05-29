#ifndef MESSAGES_H_
#define MESSAGES_H_
#include <cstdint>


enum Messages {
	INIT=0,
	LOGIN,
	UPDATE,
	CONF,
	REJECT,
	KEEPALIVE,
	DISCONNECT,
	PLAYER_UPDATE,
	ALREADY_EXIST_USER,
	LOGIN_OK
};


#endif 
