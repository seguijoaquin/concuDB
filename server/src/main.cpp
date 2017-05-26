#include <iostream>
#include "../../utils/Logger.h"
#include "Server.h"



int main() {
	
	Logger::getInstance()->debug("Iniciando Servidor");
	
	Server server ("../ftok",'a');
	server.start();

	Logger::getInstance()->debug("Finalizando Servidor");
	
	return 0;

}
