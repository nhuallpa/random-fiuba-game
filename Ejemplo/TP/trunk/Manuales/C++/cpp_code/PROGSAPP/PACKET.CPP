void ReceivePacket (Packet *pack, Connection *c)
{
	switch (pack->Type()) {
		case controlPack:
				//...
                break;
		case dataPack:
				//...
                break;
		case diagnosticPack:
				//...
                break;
		default:
        		//...
    }
}