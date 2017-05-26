#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <string.h>
#include <sstream>

#include "../../utils/Messages.h"
#include "../../utils/Queue.h"

class Server {
	private:
		Queue<message>* queue;
		message requestReceived;
		message response;

	public:
		Server ( const std::string& file, const char c );
		~Server ();

		void start();
		bool getRequest ();
		int processRequest ();
		int answerRequest () const;

		message getRequestReceived ();
		message getResponse ();
};

#endif /* Server_H_ */
