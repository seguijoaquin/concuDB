#ifndef MESSAGES_H_
#define MESSAGES_H_

#define REQUEST        1
#define RESPONSE       2
#define TEXT_SIZE      255


typedef struct message {
        long mtype;
        int id;
        char queryType;
        char text;
} message;

#endif /* MESSAGES_H_ */

