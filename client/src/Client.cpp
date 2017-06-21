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

message Client :: sendRequest ( char queryType,  message newMessage ) const {
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
        
        if ( queryType == FIND_NAME ) {
			this->queue->read ( getpid(),&res );
			int numberOfMessages = res.numberOfMessages;
			std::cout << "Numero a leer: "<< res.numberOfMessages << std::endl;
			for (int i=0 ; i < numberOfMessages ; i++ ) {
				this->queue->read ( getpid(),&res );
				std::cout << "Nombre: " << res.row.nombre << " Telefono: " <<res.row.telefono 
							<< " Direccion: " << res.row.direccion << std::endl;
							
			}
		} else {
			this->queue->read ( getpid(),&res );
		}
        

        return res;
}

