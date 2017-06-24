#ifndef LOCK_H_
#define LOCK_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>
#include "./Constants.h"

class Lock{

protected:
	struct flock fl;
	int fd;
	std::string nombre;

public:
	Lock( const std::string nombre );
	virtual ~Lock();
	virtual int tomarLock() = 0;
};

#endif /* LOCK_H_ */
