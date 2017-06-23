#include "Lock.h"

Lock :: Lock ( const std::string nombre ) {

	this->nombre = nombre;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = 0;
}




Lock :: ~Lock () {
  this->fl.l_type = F_UNLCK;
  if ( fcntl ( this->fd,F_SETLK,&(this->fl) ) == -1 ) {
	  perror("Error trying to set a lock");
  }
	close ( this->fd );
}
