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

class Server {
	private:
		Queue<message>* queue;
		//message requestReceived;
		//message response;
		SENAL_SALIDA_Handler senal_salida_handler;
		__pid_t serverpid;

	public:
		Server ( const std::string& file, const char c );
		~Server ();

		void start();
		bool getRequest ( message* receivedRequest ) const;
		message processRequest ( message* receivedRequest ) const;
		int answerRequest ( message response ) const;
		void registerExitSignal ();
		void destroyExitSignal ();

		//message getRequestReceived () const;
		//message getResponse () const;

		__pid_t getServerPid() const;
		int endCommunication ();
};

#endif /* Server_H_ */
