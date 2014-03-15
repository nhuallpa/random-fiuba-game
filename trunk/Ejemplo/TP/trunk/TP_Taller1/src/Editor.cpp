#include "Main/mainJuego.h"

#include "Log/Logger.h"
#include "Log/Suceso.h"
#include "Sonido/Sonido.h"

using namespace std;

int main (int argc, char *argv[])
{
	//Creo los logger
	Log::Logger cout_logger(Log::FATAL | Log::ERROR | Log::DEBUG);
	Log::Logger file_logger("Log.txt", Log::ALL);

	if (argc != 2) {
		Log::Suceso(Log::FATAL, "Cantidad de argumentos invalido. \n Ingreso correcto: TP_Taller1 <path de archivo YAML>");
		return -1;
	}

	Sonido::Instancia()->setSalida(Salida::local);
	return mainJuego(nullptr, argv[1]);
}
