#include "Database.h"



using namespace std;

Database :: Database () {
    this->db.open("database.db", std::fstream::in | std::fstream::out | std::ios_base::app);
    
}

Database :: ~Database () {
    this->db.close();
}

int Database :: insert (row newRow) {
      LockWrite lock("index.db");
        int newIndex = lock.leerInt() + 1;
        lock.escribirAlInicio(&newIndex,sizeof(newIndex));
        if (this->db.is_open()) {
            this->db << "(" << newIndex << ";" << newRow.nombre << ";" << newRow.direccion << ";" << newRow.telefono << ")" << std::endl;
            this->db.flush();
            if ( db.fail() ) {
				perror("Insert failed");
				return ERROR;
			}
        }
    return SUCCESS;
}

struct row getFields(std::string fileLine) {

	std::istringstream iss(fileLine);
	std::string id;
    std::getline(iss,id,';');
    std::string nombre;
    std::getline(iss,nombre,';');
    std::string direccion;
    std::getline(iss,direccion,';');
    std::string telefono;
    std::getline(iss,telefono,';');

    struct row result;
    result.id = atoi(id.c_str());
    strcpy(result.nombre, nombre.c_str());
    strcpy(result.direccion, direccion.c_str());
    strcpy(result.telefono, telefono.c_str());

    return result;
}

std::vector<struct row> Database :: findName (std::string name) {
   LockRead lock("index.db");
		std::vector<struct row> result;
		std::string line;
		this->db.clear();
		this->db.seekg(0,ios::beg);
		while (std::getline(this->db,line)) {
			if ( db.fail() ) {
				perror("findName Failed");
				throw errno;
			}
			struct row fields = getFields(line);
			if ( name.compare( fields.nombre ) == 0 ){
				result.push_back(fields);
			}
		}
    return result;
}
