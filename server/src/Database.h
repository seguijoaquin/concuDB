#ifndef DATABASE_H_
#define DATABASE_H_

#include "../../utils/Messages.h"
#include "../../utils/LockFile.h"
#include "../../utils/Constants.h"


#include "../../utils/LockRead.h"
#include "../../utils/LockWrite.h"


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <ctype.h>

class Database {
	private:
				std::fstream db;

	public:
		Database ();
		~Database ();
        int insert(row newRow);
        std::vector<struct row> findName(std::string name);

};

#endif /* Database_H_ */
