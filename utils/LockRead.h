#ifndef LOCK_READ_H_
#define LOCK_READ_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>

#include "Lock.h"

class LockRead: public Lock{


public:
	LockRead( const std::string nombre );
	int tomarLock();
	~LockRead();
};

#endif /* LOCK_H_ */
