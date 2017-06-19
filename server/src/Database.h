#ifndef DATABASE_H_
#define DATABASE_H_

#include "../../utils/Messages.h"
#include "../../utils/LockFile.h"
#include "../../utils/Constants.h"

#include <stdio.h>
#include <iostream>
#include <fstream>

class Database {
	private:
        LockFile* indexFile;
	std::fstream db;
		
	public:
		Database ();
		~Database ();
        int insert(row newRow);
        int findName();

};

#endif /* Database_H_ */