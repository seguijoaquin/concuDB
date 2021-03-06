#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <string.h>
#include <sstream>
#include <unistd.h>

#include "../../utils/Messages.h"
#include "../../utils/Queue.h"
#include "../../utils/signals/SENAL_SALIDA_Handler.h"
#include "../../utils/signals/SignalHandler.h"
#include "../../utils/LockFile.h"
#include "Database.h"

class Server {
	private:
		Queue<message>* queue;
		SENAL_SALIDA_Handler senal_salida_handler;
		Database* db;
		
	public:
		Server ( const std::string& file, const char c );
		~Server ();

		void start();
		bool getRequest ( message* receivedRequest ) const;
		std::vector<message> processRequest ( message* receivedRequest ) const;
		int answerRequest ( std::vector<message> responses ) const;
		void registerExitSignal ();
		void destroyExitSignal ();

};

#endif /* Server_H_ */
