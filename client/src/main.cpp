#include <iostream>
#include "../../utils/Logger.h"
#include "Client.h"
#include "../../utils/Constants.h"
#include <strings.h>
#include <string>



int main() {
	
	Logger::getInstance()->debug("Iniciando Cliente");

	Client client ("../ftok",'a');

	Logger::getInstance()->debug("Enviando un mensaje al servidor..."); sleep(1);
	message res = client.sendRequest('A');
    Logger::getInstance()->debug("Enviado: A");
	std::cout << "Respuesta: " << res.text << std::endl;
	
	sleep(3);
	Logger::getInstance()->debug("Enviando mensaje de salida al servidor..."); sleep(1);
	message res2 = client.sendRequest(SALIDA);
	std::cout << "Respuesta: " << res.text << std::endl;
	
	sleep(1);

	Logger::getInstance()->debug("Finalizando Cliente");
	
	return 0;

}
