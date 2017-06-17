
#ifndef CONCUDB_EVENTHANDLER_H
#define CONCUDB_EVENTHANDLER_H

class EventHandler {

public:
	virtual int handleSignal ( int signum ) = 0;
	virtual ~EventHandler () {};
};

#endif //CONCUDB_EVENTHANDLER_H
