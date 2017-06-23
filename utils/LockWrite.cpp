#include "LockWrite.h"

LockWrite :: LockWrite ( const std::string nombre ):Lock(nombre){
  if ( tomarLock() == -1 ) { 
	 perror("Error: Tomar lock");
  }
}


int LockWrite::tomarLock(){
  this->fd = open (this->nombre.c_str(),O_CREAT|O_RDWR,0777);
  this->fl.l_type = F_WRLCK;
	return fcntl (this->fd,F_SETLKW,&(this->fl));
}



ssize_t LockWrite :: escribir ( const void* buffer,const ssize_t buffsize ) const {
	lseek ( this->fd,0,SEEK_END );
	return write ( this->fd,buffer,buffsize );
}


ssize_t LockWrite :: escribirAlInicio ( const void* buffer,const ssize_t buffsize ) const {
	lseek ( this->fd,0,SEEK_SET );
	return write ( this->fd,buffer,buffsize );
}


int LockWrite :: leerInt () {
	lseek ( this->fd,0,SEEK_SET);
	int t;
	ssize_t result = read (this->fd,&t,sizeof(int));
	if (result < 0) perror("read");
	return t;
}

LockWrite :: ~LockWrite () {}
