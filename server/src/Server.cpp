#include "Server.h"
#include "../../utils/Logger.h"
#include "../../utils/Constants.h"


Server :: Server (const std::string& file, const char c ) {
	this->queue = new Queue<message> (file,c);
}

Server :: ~Server () {
        this->queue->destroy();
	delete (this->queue);
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
                        message response = this->processRequest(&requestReceived);
                        this->answerRequest(response);
                        exit(EXIT_SUCCESS);
                }
                sleep(1);
        } 
        Logger::getInstance()->debug("Saliendo...");
        this->destroyExitSignal();
}

bool Server :: getRequest (message* requestReceived) const {
        Logger::getInstance()->debug("Esperando request...");
        message newRequest;
        int result = this->queue->read ( REQUEST, &(newRequest) );
        if ( result == -1 ) return false;
        if ( fork() == 0 ) {
                (*requestReceived) = newRequest;
                return true;
        } else {
                Logger::getInstance()->debug("Request recibido!");
                return false;
        }
}

message Server :: processRequest (message* requestReceived) const {
        Logger::getInstance()->debug("Procesando Request en nuevo proceso...");

        if (requestReceived->queryType == INSERT) {
                Logger::getInstance()->debug("Insertando fila");
        }

        if (requestReceived->queryType == FIND_NAME) {
                Logger::getInstance()->debug("Buscando nombre");
        }
        std::stringstream textoRta;
        textoRta << "[Recibido de : " << requestReceived->id << "] = " << requestReceived->text;
        Logger::getInstance()->debug(textoRta.str().c_str());
        //mtype of the response is the id of the process who made the petition to the server
        message response;
        memset(&response, 0, sizeof(message));
        response.mtype = requestReceived->id;
        response.id = RESPONSE;
        response.queryType = 'a';
        response.text = 'S';
        return response;
}

int Server :: answerRequest (message response) const {
        Logger::getInstance()->debug("Respondiendo...");
        this->queue->write ( response );
        //returns the id of the process who's picking up the server message
        return response.id;
}
