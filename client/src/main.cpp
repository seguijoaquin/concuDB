#include <iostream>
#include "../../utils/Logger.h"
#include "Client.h"



int main() {
	
	Logger::getInstance()->debug("Iniciando Cliente");

	Client client ("../ftok",'a');

	std::stringstream request;
	request << "HOLA";
	message res = client.sendRequest(getpid(),request.str());
    Logger::getInstance()->debug(res.text);

	
	message res2 = client.sendRequest(0,request.str());
    Logger::getInstance()->debug(res2.text);
	
	Logger::getInstance()->debug("Finalizando Cliente");
	
	return 0;

}
