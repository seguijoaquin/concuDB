#include "Server.h"
#include "../../utils/Logger.h"
#include "../../utils/Constants.h"


Server :: Server (const std::string& file, const char c ) {
	this->queue = new Queue<message> (file,c);
}

Server :: ~Server () {
	delete this->queue;
}

void Server :: registerExitSignal () {
        SignalHandler::getInstance()->registrarHandler(SENAL_SALIDA,&this->senal_salida_handler);
}

void Server :: destroyExitSignal () {
        SignalHandler::destruir();
}

void Server :: start () {
        this->registerExitSignal();
        while (this->senal_salida_handler.getGracefulQuit() == 0) {
                this->getRequest();
                sleep(2);
                this->processRequest();
                sleep(2);
                this->answerRequest();
                sleep(2);
        } 
        Logger::getInstance()->debug("Saliendo...");
        this->destroyExitSignal();
}

bool Server :: getRequest () {
        Logger::getInstance()->debug("Esperando request...");
        //this->queue->read ( REQUEST,&(this->requestReceived) );
        sleep(2);
        Logger::getInstance()->debug("Request recibido!");
        return true;
        //return (this->requestReceived.text != SALIDA);
}

int Server :: processRequest () {
        Logger::getInstance()->debug("Procesando Request...");

        //std::stringstream textoRta;
        //textoRta << "[Recibido: " << this->requestReceived.id << "] = " << this->requestReceived.text;
        //Logger::getInstance()->debug(textoRta.str().c_str());

        //mtype of the response is the id of the process who made the petition to the server
        //this->response.mtype = this->requestReceived.id;
        //this->response.id = RESPONSE;
        //this->response.text = 'S';
        //std::stringstream res;
        //res << "OK";
        //strcpy ( this->response.text,res.str().c_str() );

        return 0;
}

int Server :: answerRequest () const {
        Logger::getInstance()->debug("Respondiendo...");
        //this->queue->write ( this->response );
        //returns the id of the process who's picking up the server message
        //return this->response.id;
        return 0;
}

message Server :: getRequestReceived () {
        return this->requestReceived;
}

message Server :: getResponse () {
        return this->response;
}

