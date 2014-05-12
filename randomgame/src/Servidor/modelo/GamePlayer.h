#ifndef __GAMEPLAYER__
#define __GAMEPLAYER__

#include "Entities\Worm.h"
#include "..\..\utils\Util.h"
#include <list>

using namespace std;

class GamePlayer{
public:
	GamePlayer(std::string playerID);
	~GamePlayer();
	static GamePlayer* NewPlayerFactory(int prefId, int amountWorms);
	void setStateConn(StateConn sc);
	void add(Worm* w);
	std::vector<Worm*> getWorms(){ return this->worms;}
	void initPlayer(int prefId, int amountWorms);
	std::string playerID;
private:
	std::vector<Worm*> worms;
	StateConn state;
};

#endif /*__GAMEPLAYER__*/
