#ifndef DATABASE_H_
#define DATABASE_H_

#include "../../utils/Messages.h"
#include "../../utils/LockFile.h"

class Database {
	private:
        int db;
        int index;
		
	public:
		Database ();
		~Database ();
        bool insert();
        bool findName();

};

#endif /* Database_H_ */