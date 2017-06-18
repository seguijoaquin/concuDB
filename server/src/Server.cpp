#include "Server.h"
#include "../../utils/Logger.h"
#include "../../utils/Constants.h"


Server :: Server (const std::string& file, const char c ) {
	this->queue = new Queue<message> (file,c);
        this->serverpid = getpid();
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
                        this->endCommunication();
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
        this->queue->read ( REQUEST, &(newRequest) );
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
        textoRta << "[Recibido: " << requestReceived->id << "] = " << requestReceived->text;
        Logger::getInstance()->debug(textoRta.str().c_str());
        //mtype of the response is the id of the process who made the petition to the server
        message response;
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

int Server :: endCommunication () {
        //this->queue->destroy();
        //delete (this->queue);
        return 0;
}
/*
message Server :: getRequestReceived () const {
        return this->requestReceived;
}

message Server :: getResponse () const {
        return this->response;
}
*/
__pid_t Server :: getServerPid () const {
        return this->serverpid;
}

