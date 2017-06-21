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
	Logger::getInstance()->debug("Enviando un mensaje de nuevo registro...");
	std::vector<message> responses = client->sendRequest(FIND_NAME,newMessage);
	if ( responses.size() != 1 ) {
		// El 0 es el mensaje que dice cuantos hay que leer
		for (int i = 1; i < responses.size() ; i++ ) {
			row rowObtained = responses[i].row;
			std::stringstream ss;
			ss << "Nombre: " << rowObtained.nombre;
			ss << " Direccion: " << rowObtained.direccion;
			ss << " Telefono: " << rowObtained.telefono;
			
			Logger::getInstance()->debug("Fila obtenida:");
			Logger::getInstance()->debug(ss.str() );
		}
	} else {
		Logger::getInstance()->debug("No existen resultados para la busqueda.");
	}
	
	return responses[0];
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
	std::vector<message> responses = client->sendRequest(INSERT,newMessage);
	
	return responses[0];
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
