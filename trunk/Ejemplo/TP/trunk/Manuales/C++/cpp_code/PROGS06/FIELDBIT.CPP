typedef unsigned int Bit;

enum PacketType {dataPack, controlPack, supervisoryPack};
enum Bool		{false, true};

class Packet {
public:
		Packet	(void);

private:
	Bit	type		: 2;
	Bit acknowledge	: 1;
	Bit channel		: 4;
	Bit	sequenceNo	: 4;
	Bit	moreData	: 1;
	//...
};

Packet::Packet (void)
{
	type = controlPack;
    acknowledge = true;
}