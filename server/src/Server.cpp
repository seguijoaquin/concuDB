#include "Server.h"
#include "../../utils/Logger.h"
#include "../../utils/Constants.h"


Server :: Server (const std::string& file, const char c ) {
	this->queue = new Queue<message> (file,c);
        this->db = new Database ();
}

Server :: ~Server () {
	this->queue->destroy();
	delete (this->queue);
	delete (this->db);
}

void Server :: registerExitSignal () {
        SignalHandler::getInstance()->registrarHandler(SENAL_SALIDA,&this->senal_salida_handler);
}

void Server :: destroyExitSignal () {
        SignalHandler::destruir();
}

void Server :: start () {
        this->registerExitSignal();
        while ( this->senal_salida_handler.getGracefulQuit() == 0 ) {
                message requestReceived;
                if ( this->getRequest(&requestReceived) ) {
                        std::vector<message> responses = this->processRequest(&requestReceived);
                        this->answerRequest(responses);
                        exit(EXIT_SUCCESS);
                }
        }
        Logger::getInstance()->debug("Saliendo...");
        this->destroyExitSignal();
}

int addNumberOfMessagesResponse(std::vector<message>* responses, message req, int numberOfMessages) {
	message numOfMsgRes;
	memset(&numOfMsgRes, 0, sizeof(message));
	numOfMsgRes.mtype = req.id;
	numOfMsgRes.id = RESPONSE;
	numOfMsgRes.success = SUCCESS;
	numOfMsgRes.numberOfMessages = numberOfMessages;
	responses->push_back(numOfMsgRes);
}

void logMessage(message msg) {
	std::stringstream ss;
	ss << "mtype: " << msg.mtype
		<< " success: " << msg.success
		<< " row: Nombre: " << msg.row.nombre
		<< " Direccion: " << msg.row.direccion 
		<< " Telefono: " << msg.row.telefono;
		
	Logger::getInstance()->debug(ss.str());
}


bool Server :: getRequest (message* requestReceived) const {
        Logger::getInstance()->debug("Esperando request...");
        message newRequest;
        int result = this->queue->read ( REQUEST, &(newRequest) );
        if ( result == -1 ) return false;
        if ( fork() == 0 ) {
                (*requestReceived) = newRequest;
                Logger::getInstance()->debug("Por procesar el siguiente request");
				logMessage(newRequest);
                return true;
        } else {
                Logger::getInstance()->debug("Request recibido!");
                return false;
        }
}



std::vector<message> Server :: processRequest (message* requestReceived) const {
        Logger::getInstance()->debug("Procesando Request en nuevo proceso...");
		std::vector<message> responses;
        if (requestReceived->queryType == INSERT) {
                Logger::getInstance()->debug("Insertando fila");
                addNumberOfMessagesResponse(&responses,*requestReceived,1);
				
                row newRow;
                memset(&newRow,0,sizeof(row));
                strncpy((newRow.nombre), (requestReceived->row.nombre), 62*sizeof(char));
                strncpy((newRow.direccion), (requestReceived->row.direccion), 121*sizeof(char));
                strncpy((newRow.telefono), (requestReceived->row.telefono), 14*sizeof(char));

                //mtype of the response is the id of the process who made the petition to the server
                message response;
                memset(&response, 0, sizeof(message));
                response.mtype = requestReceived->id;
                response.id = RESPONSE;
                response.success = this->db->insert(newRow);
			
				responses.push_back(response);
        }
        if (requestReceived->queryType == FIND_NAME) {
                Logger::getInstance()->debug("Buscando nombre");
                //	At first the server will send a message containing 
                //	the number of rows that it will be sending
				std::vector<struct row> rows = this->db->findName(requestReceived->row.nombre);
				addNumberOfMessagesResponse(&responses,*requestReceived,rows.size());
				
				for (int i=0 ; i<rows.size() ; i++) {
					message response;
					memset(&response, 0, sizeof(message));
					response.mtype = requestReceived->id;
					response.id = RESPONSE;
					response.success = SUCCESS;
					response.row = rows[i];
					
					responses.push_back(response);
				}
        }
		return responses;
}


int Server :: answerRequest (std::vector<message> responses) const {
        Logger::getInstance()->debug("Respondiendo...");
		for (int i = 0 ; i < responses.size() ; i++) {
			Logger::getInstance()->debug("Enviando: ");
			logMessage(responses[i]);
			this->queue->write ( responses[i] );
		}
        //returns the id of the process who's picking up the server message
        return responses[0].id;
}
