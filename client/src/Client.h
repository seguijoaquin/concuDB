#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#include "../../utils/Messages.h"
#include "../../utils/Queue.h"
#include "../../utils/Constants.h"

class Client {

        private:
                Queue<message>* queue;

        public:
                Client ( const std::string& file,const char c );
                ~Client();
                std::vector<message> sendRequest ( char queryType, message newMessage ) const;
};

#endif /* CLIENT_H_ */
