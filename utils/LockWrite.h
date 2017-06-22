#ifndef LOCK_WRITE_H_
#define LOCK_WRITE_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>

#include "Lock.h"

class LockWrite: public Lock{


public:
	LockWrite(const std::string nombre);
	~LockWrite();
	int tomarLock();
	int leerInt();
	ssize_t escribir ( const void* buffer,const ssize_t buffsize ) const;
	ssize_t escribirAlInicio(const void* buffer,const ssize_t buffsize) const;
};

#endif /* LOCK_WRITE_H_ */
