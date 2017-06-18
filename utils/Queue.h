#ifndef QUEUE_H_
#define QUEUE_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>

template <class T> class Queue {
	private:
		key_t	key;
		int		id;

	public:
		Queue ( const std::string& file,const char c );
		~Queue();
		int write ( const T& data ) const;
		int read ( const int type,T* buffer ) const;
		int destroy () const;
};

template <class T> Queue<T> :: Queue ( const std::string& file,const char c ) {
	this->key = ftok ( file.c_str(),c );
	if ( this->key == -1 )
		perror ( "ftok" );

	this->id = msgget ( this->key,0777|IPC_CREAT );
	if ( this->id == -1 )
		perror ( "msgget" );
}

template <class T> Queue<T> :: ~Queue () {
}

template <class T> int Queue<T> :: destroy () const {
	int result = msgctl ( this->id,IPC_RMID,NULL );
	if (result == -1) {
		perror("msgctl");
		exit(EXIT_FAILURE);
	}
	return result;
}

template <class T> int Queue<T> :: write ( const T& data ) const {
	int result = msgsnd ( this->id,static_cast<const void*>(&data),sizeof(T)-sizeof(long),0 );
	if (result == -1) {
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}
	return result;
}

template <class T> int Queue<T> :: read ( const int type,T* buffer ) const {
	int result = msgrcv ( this->id,static_cast<void *>(buffer),sizeof(T)-sizeof(long),type,0 );
	if (result == -1) {
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	return result;
}

#endif /* QUEUE_H_ */
