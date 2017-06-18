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

message Client :: sendRequest ( char queryType,  /*const std::string&*/ char text ) const {
        message req;
        message res;
        memset(&req, 0, sizeof(message));

        req.mtype = REQUEST;
        req.id = getpid();
        req.queryType = queryType;
        req.text = text;
        this->queue->write ( req );
        this->queue->read ( getpid(),&res );

        return res;
}
