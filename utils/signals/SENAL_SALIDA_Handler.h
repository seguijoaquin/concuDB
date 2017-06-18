
#ifndef CONCUDB_SENAL_SALIDA_HANDLER_H
#define CONCUDB_SENAL_SALIDA_HANDLER_H


#include <signal.h>
#include <assert.h>

#include "EventHandler.h"
#include "../Constants.h"
#include "../Logger.h"
#include "../Queue.h"

class SENAL_SALIDA_Handler : public EventHandler {

private:
    sig_atomic_t gracefulQuit;

public:

    SENAL_SALIDA_Handler () : gracefulQuit(0) {
    }

    ~SENAL_SALIDA_Handler () {
    }

    virtual int handleSignal ( int signum ) {
        assert ( signum == SENAL_SALIDA );
        Logger::getInstance()->debug("Recibo señal de salida");
        this->gracefulQuit = 1;
        return 0;
    }

    sig_atomic_t getGracefulQuit () const {
        return this->gracefulQuit;
    }

};


#endif //CONCUDB_SENAL_SALIDA_HANDLER_H
