#include <iostream.h>

enum PType	{controlPack, dataPack, diagnosePack};
enum Bool	{false, true};

class Packet {
public:
	//...
    PType	Type	(void)	{return dataPack;}
	Bool	Valid	(void)	{return true;}
};

class Connection {
public:
	//...
	Bool	Active	(void)	{return true;}
};

class InactiveConn	{};
class InvalidPack	{};
class UnknownPack	{};

void ReceivePacket (Packet *pack, Connection *c)
	throw(InactiveConn, InvalidPack, UnknownPack)
{
	if (!c->Active())
    	throw InactiveConn();
    if (!pack->Valid())
    	throw InvalidPack();

	switch (pack->Type()) {
		case controlPack:	//...
                				break;
		case dataPack:		//...
                				break;
		case diagnosePack:	//...
                				break;
		default:			//...
        	throw UnknownPack();
    }
}

int main (void)
{
	Packet *p = new Packet;
    Connection *c = new Connection;

    try {
    	ReceivePacket(p, c);
        //...
    }
    catch (InactiveConn) {cout << "inactive connection\n";}
    catch (InvalidPack) {cout << "inactive connection\n";}
    catch (UnknownPack) {cout << "inactive connection\n";}

	return 0;
}