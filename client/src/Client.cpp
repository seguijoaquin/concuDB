#include "Client.h"
#include <sys/types.h>
#include <unistd.h>

Client :: Client ( const std::string& file,const char c ) {
        this->queue = new Queue<message> ( file,c );
}

Client :: ~Client() {
        //this->queue->destroy ();
        delete this->queue;
}

message Client :: sendRequest ( char queryType,  /*const std::string&*/ char text ) const {
        message req;
        message res;

        req.mtype = REQUEST;
        req.id = getpid();
        req.queryType = queryType;
        //strcpy ( req.text,text.c_str() );
        req.text = text;

        this->queue->write ( req );
        this->queue->read ( getpid(),&res );

        return res;
}
