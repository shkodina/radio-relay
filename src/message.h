#ifndef MY_MESSAGE_H
#define MY_MESSAGE_H

#include "commondefines.h"

#define MAX_MESSAGE_LEN 128;


char 			messageBuild		(unsigned char * message, unsigned char message_len, unsigned int ports_state);
unsigned int 	messageParseState	(unsigned char * message, unsigned char message_len)
char 			messageCode			(unsigned char * message, unsigned char message_len);
char 			messageDecode		(unsigned char * message, unsigned char message_len);

#endif