#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <string.h>
#include <sstream>

#include "../../utils/Messages.h"
#include "../../utils/Queue.h"
#include "../../utils/signals/SENAL_SALIDA_Handler.h"
#include "../../utils/signals/SignalHandler.h"

class Server {
	private:
		Queue<message>* queue;
		message requestReceived;
		message response;
		SENAL_SALIDA_Handler senal_salida_handler;

	public:
		Server ( const std::string& file, const char c );
		~Server ();

		void start();
		bool getRequest ();
		int processRequest ();
		int answerRequest () const;
		void registerExitSignal ();
		void destroyExitSignal ();

		message getRequestReceived ();
		message getResponse ();
};

#endif /* Server_H_ */
