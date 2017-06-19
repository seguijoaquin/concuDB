#include "LockFile.h"

LockFile :: LockFile ( const std::string nombre ) {

	this->nombre = nombre;
	this->fl.l_type = F_WRLCK;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = 0;
	this->fd = open ( this->nombre.c_str(),O_CREAT|O_RDWR,0777 );
}

int LockFile :: tomarLock () {
	this->fl.l_type = F_WRLCK;
	return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int LockFile :: liberarLock () {
	this->fl.l_type = F_UNLCK;
	return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

ssize_t LockFile :: escribir ( const void* buffer,const ssize_t buffsize ) const {
	lseek ( this->fd,0,SEEK_END );
	return write ( this->fd,buffer,buffsize );
}

ssize_t LockFile :: escribirAlInicio ( const void* buffer,const ssize_t buffsize ) const {
	lseek ( this->fd,0,SEEK_SET );
	return write ( this->fd,buffer,buffsize );
}

int LockFile :: leerInt () {
	lseek ( this->fd,0,SEEK_SET);
	int t;
	ssize_t result = read (this->fd,&t,sizeof(int));
	if (result < 0) perror("read");
	return t;
}

LockFile :: ~LockFile () {
	close ( this->fd );
}
