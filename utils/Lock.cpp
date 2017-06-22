#include "Lock.h"

Lock :: Lock ( const std::string nombre ) {

	this->nombre = nombre;
	//this->fl.l_type = F_WRLCK;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = 0;
	//this->fd = open ( this->nombre.c_str(),O_CREAT|O_RDWR,0777 );
}




Lock :: ~Lock () {
  this->fl.l_type = F_UNLCK;
  fcntl ( this->fd,F_SETLK,&(this->fl) );
	close ( this->fd );
}
