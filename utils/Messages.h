#ifndef MESSAGES_H_
#define MESSAGES_H_

#define REQUEST        1
#define RESPONSE       2
#define TEXT_SIZE      255

typedef struct row {
        int id;
        char nombre[61];
        char direccion[120];
        char telefono[13];
} row;


typedef struct message {
        long mtype;
        int id;
		int numberOfMessages;
        char queryType;
        int success;
        struct row row;
} message;

#endif /* MESSAGES_H_ */

