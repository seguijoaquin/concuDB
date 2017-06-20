#include "Database.h"

using namespace std;

Database :: Database () {
    this->indexFile = new LockFile ("index.db");
    this->db.open("database.db", std::fstream::in | std::fstream::out | std::ios_base::app);
    //Inicio index.db con un 0
    //int x;
    //x = 0;
    //this->indexFile->escribirAlInicio(&x,sizeof(x));
    //if (this->db->leerInt() == 125) std::cout << "EXITO!!!" << std::endl;
}

Database :: ~Database () {
    this->db.close();
    delete (this->indexFile);
}

int Database :: insert (row newRow) {
    this->indexFile->tomarLock();
        int newIndex = this->indexFile->leerInt() + 1;
        this->indexFile->escribirAlInicio(&newIndex,sizeof(newIndex));
        if (this->db.is_open()) {
            this->db << "(" << newIndex << ";" << newRow.nombre << ";" << newRow.direccion << ";" << newRow.telefono << ")" << std::endl;
            this->db.flush();
        }
    this->indexFile->liberarLock();

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
	this->indexFile->tomarLock();
		std::vector<struct row> result;
		std::string line;
		this->db.clear();
		this->db.seekg(0,ios::beg);
		while (std::getline(this->db,line)) {
			struct row fields = getFields(line);
			std::cout << "fields nomre:" <<fields.nombre << " parametro: " << name<< std::endl;
			if ( name.compare( fields.nombre ) == 0 ){
				result.push_back(fields);
			}
		}
	this->indexFile->liberarLock();
    return result;
}
