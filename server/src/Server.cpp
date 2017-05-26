#include "Server.h"
#include "../../utils/Logger.h"

Server :: Server (const std::string& file, const char c ) {
	this->queue = new Queue<message> (file,c);
}

Server :: ~Server () {
	delete this->queue;
}

void Server :: start () {
        while (this->getRequest()) {
                sleep(5);
                this->processRequest();
                sleep(5);
                this->answerRequest();
                sleep(5);
        }        
}

bool Server :: getRequest () {
        Logger::getInstance()->debug("Esperando request...");
        this->queue->read ( REQUEST,&(this->requestReceived) );
        Logger::getInstance()->debug("Request recibido!");
        if (this->requestReceived.id > 0) {
                return true;
        }
        return false;
}

int Server :: processRequest () {
        Logger::getInstance()->debug("Procesando Request...");

        std::stringstream textoRta;
        textoRta << "[Recibido: " << this->requestReceived.id << "] = " << this->requestReceived.text;
        Logger::getInstance()->debug(textoRta.str().c_str());

        //mtype of the response is the id of the process who made the petition to the server
        this->response.mtype = this->requestReceived.id;
        this->response.id = RESPONSE;
        std::stringstream res;
        res << "OK";
        strcpy ( this->response.text,res.str().c_str() );

        return 0;
}

int Server :: answerRequest () const {
        Logger::getInstance()->debug("Respondiendo...");
        this->queue->write ( this->response );
        //returns the id of the process who's picking up the server message
        return this->response.id;
}

message Server :: getRequestReceived () {
        return this->requestReceived;
}

message Server :: getResponse () {
        return this->response;
}

