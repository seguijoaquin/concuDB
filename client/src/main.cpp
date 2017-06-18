#include <iostream>
#include "../../utils/Logger.h"
#include "Client.h"
#include "../../utils/Constants.h"
#include <strings.h>
#include <string>


message buildNameSearch(Client* client) {
	Logger::getInstance()->debug("Enviando un mensaje de busqueda...");
	return client->sendRequest(FIND_NAME,'B');
};

message buildNewRegister(Client* client) {
	//TODO: Armar message a enviar con los datos del nuevo registro
	Logger::getInstance()->debug("Enviando un mensaje de nuevo registro...");
	return client->sendRequest(INSERT,'A');
};

bool generateRequest(message* request, Client* client) {
	std::cout << std::endl;
	std::cout << "Qué desea hacer?" << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "1) Ingresar nuevo registro" << std::endl;
	std::cout << "2) Consultar por nombre" << std::endl;
	std::cout << "3) Salir" << std::endl;
	char input;
	std::cin >> input;
	std::cout << "Eligió la opción: " << input << std::endl;
	if (input == '3') return false;
	if (input == '2') (*request) = buildNameSearch(client);
	if (input == '1') (*request) = buildNewRegister(client);
	return true;
}

int main() {
	
	Logger::getInstance()->debug("Iniciando Cliente");

	Client client ("../ftok",'a');
	message newMessage;
	memset (&newMessage,0,sizeof(newMessage));

	while ( generateRequest(&newMessage,&client) ) {
		std::stringstream textoRta;
    	textoRta << "Respuesta: " << newMessage.text;
    	Logger::getInstance()->debug(textoRta.str().c_str());
		sleep(1);
	}

	Logger::getInstance()->debug("Finalizando Cliente");
	
	return 0;

}
