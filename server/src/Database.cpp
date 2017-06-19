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

int Database :: findName () {
    return SUCCESS;
}