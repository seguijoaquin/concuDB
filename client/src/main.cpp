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


//En el flujo del programa del programa, cuando se llama por primera vez siempre
//hay un \n, para eso uso ignore, pero cuando se llama reiterada veces, no hay
//salto de linea. con value, digo cuando ignorar o no el salto de linea.
void getParameter(char* parameter_insert,bool value){
	std::string answer;
	if (value) std::cin.ignore();
	std::getline(std::cin,answer);
	strncpy(parameter_insert,answer.c_str(),answer.length());
	//TODO borrar este linea cuando ya se haga la entrega
	printf("El parametro ingresado es:%s \n",parameter_insert);
}

message buildNameSearch(Client* client){
	Logger::getInstance()->debug("Enviando un mensaje de busqueda...");
	message newMessage;
	memset (&newMessage,0,sizeof(message));
	std::cout << "Ingrese nombre a buscar: ";
	getParameter(newMessage.row.nombre,true);
	return client->sendRequest(FIND_NAME,newMessage);
};

message buildNewRegister(Client* client) {
	message newMessage;
	memset (&newMessage,0,sizeof(message));
	std::cout << "Ingrese nombre (sin espacios, arreglar bug): ";
	getParameter(newMessage.row.nombre,true);
	std::cout << "Ingrese direccion (sin espacios, arreglar bug): ";
	getParameter(newMessage.row.direccion,false);
	std::cout << "Ingrese telefono: ";
	getParameter(newMessage.row.telefono,false);
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
