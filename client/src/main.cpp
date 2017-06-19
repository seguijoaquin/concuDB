#include <iostream>
#include "../../utils/Logger.h"
#include "Client.h"
#include "../../utils/Constants.h"
#include <strings.h>
#include <string>


void printMenu () {
	std::cout << std::endl;
	std::cout << "Qué desea hacer?" << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "1) Ingresar nuevo registro" << std::endl;
	std::cout << "2) Consultar por nombre" << std::endl;
	std::cout << "3) Salir" << std::endl;
};

message buildNameSearch(Client* client) {
	Logger::getInstance()->debug("Enviando un mensaje de busqueda...");
	message newMessage;
	memset (&newMessage,0,sizeof(message));
	std::cout << "Ingrese nombre a buscar (sin espacios, arreglar bug): ";
	std::cin >> newMessage.row.nombre;
	return client->sendRequest(FIND_NAME,newMessage);
};

message buildNewRegister(Client* client) {
	message newMessage;
	memset (&newMessage,0,sizeof(message));
	std::cout << "Ingrese nombre (sin espacios, arreglar bug): ";
	std::cin >> newMessage.row.nombre;
	std::cout << "Ingrese direccion (sin espacios, arreglar bug): ";
	std::cin >> newMessage.row.direccion;
	std::cout << "Ingrese telefono: ";
	std::cin >> newMessage.row.telefono;

	Logger::getInstance()->debug("Enviando un mensaje de nuevo registro...");
	return client->sendRequest(INSERT,newMessage);
};

bool generateRequest(message* request, Client* client) {
	printMenu();
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
		if (newMessage.success != SUCCESS) {
			Logger::getInstance()->error("El servidor ha devuelto un mensaje de error");
		} else {
    		Logger::getInstance()->debug("El servidor dice que la consulta fue procesada con exito!");
		}
	}

	Logger::getInstance()->debug("Finalizando Cliente");
	
	return 0;

}
