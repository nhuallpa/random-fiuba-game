#ifndef __GAMEPLAYER__
#define __GAMEPLAYER__

#include "Entities\Worm.h"
#include <list>

using namespace std;

enum StateConn {CONNECTED, DISCONNECTED};

class GamePlayer{
public:
	GamePlayer();
	~GamePlayer();
	static GamePlayer* NewPlayerFactory(int prefId, int amountWorms);
	void setStateConn(StateConn sc);
	void add(Worm* w);
private:
	list<Worm*> worms;
	StateConn state;
};

#endif /*__GAMEPLAYER__*/
