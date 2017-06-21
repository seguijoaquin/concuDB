#include "Client.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


Client :: Client ( const std::string& file,const char c ) {
        this->queue = new Queue<message> ( file,c );
}

Client :: ~Client() {
        delete this->queue;
}

std::vector<message> Client :: sendRequest ( char queryType,  message newMessage ) const {
        message req;
        message res;
        memset(&req, 0, sizeof(message));
        req.mtype = REQUEST;
        req.id = getpid();
        req.queryType = queryType;
        strncpy((req.row.nombre), (newMessage.row.nombre), 62*sizeof(char));
        strncpy((req.row.direccion), (newMessage.row.direccion), 121*sizeof(char));
        strncpy((req.row.telefono), (newMessage.row.telefono), 14*sizeof(char));
        this->queue->write ( req );
        
        //read mensaje que contiene el numero de mensajes
        this->queue->read ( getpid(),&res );
		int numberOfMessages = res.numberOfMessages;
		std::vector<message> responses;
		responses.push_back(res);
		for (int i = 0 ; i < numberOfMessages ; i++ ) {
			std::cout << numberOfMessages << std::endl;
			this->queue->read ( getpid(),&res );
			responses.push_back(res);
		}
        return responses;
}

