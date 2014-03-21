#pragma once

#include "./Servidor/Servidor.h"
#include "./Cliente/Cliente.h"


class Administrador{

	private:
		bool isServer;
		Servidor* aServer;
		Cliente* aClient;

		void parseCommands(void);

	public:
		Administrador(void);
		~Administrador(void);
		void run();

};
