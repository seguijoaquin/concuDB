#include "LockRead.h"

LockRead :: LockRead ( const std::string nombre ):Lock(nombre){
  tomarLock();
}


int LockRead::tomarLock(){
  this->fd = open (this->nombre.c_str(),O_CREAT|O_RDONLY,0777);
  this->fl.l_type = F_RDLCK;
	return fcntl (this->fd,F_SETLKW,&(this->fl));
}



LockRead :: ~LockRead () {}
