#include "LockRead.h"

LockRead :: LockRead ( const std::string nombre ):Lock(nombre){
  if ( tomarLock() == -1 ) { 
	 perror("Error: Tomar lock");
	 throw errno;
  }
}


int LockRead::tomarLock(){
  this->fd = open (this->nombre.c_str(),O_RDONLY,0777);
  this->fl.l_type = F_RDLCK;
	return fcntl (this->fd,F_SETLKW,&(this->fl));
}



LockRead :: ~LockRead () {}
