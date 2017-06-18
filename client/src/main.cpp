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
	message res = client.sendRequest(INSERT,'A');
    Logger::getInstance()->debug("Enviado: A");
	std::stringstream textoRta;
    textoRta << "Respuesta: " << res.text << std::endl;
    Logger::getInstance()->debug(textoRta.str().c_str()); 
/*	
	sleep(3);
	Logger::getInstance()->debug("Enviando mensaje al servidor..."); sleep(1);
	message res2 = client.sendRequest(FIND_NAME,'B');
	Logger::getInstance()->debug("Enviado: B");
	std::stringstream textoRta2;
    textoRta2 << "[Respuesta: " << res2.text << std::endl;
    Logger::getInstance()->debug(textoRta2.str().c_str()); 
	
	sleep(1);
*/
	Logger::getInstance()->debug("Finalizando Cliente");
	
	return 0;

}
