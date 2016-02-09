#include "message.h"

volatile static unsigned char message[MAX_MESSAGE_LEN];
volatile static unsigned char message_len = 0;

//****************************************************************************

char 			messageBuild		(unsigned char * message, unsigned char message_len, unsigned int ports_state){
	message[PACKET_TYPE_POSITION] = PACKET_TYPE;
	message[MODULE_ID_POSITION] = MODULE_ID;
	char data_len = 2; // sizeof(ports_state);
	message[DATA_LEN_POSITION] = data_len; 

	char * int_p = &ports_state;
	for (char i = 0; i < data_len; i++){
		message[DATA_START_POSITION + i] =  *(int_p + i);
	}	
}

//****************************************************************************

unsigned int 	messageParseState	(unsigned char * message, unsigned char message_len){
	unsigned int port_state = 0;
	char * int_p = &ports_state;
	char data_len = 2; // sizeof(ports_state);
	for (char i = 0; i < data_len; i++){
		*(int_p + i) = message[DATA_START_POSITION + i];
	}	
	return port_state;
}

//***************************************************************************
//***** there is no coding algorithms for at now
//***************************************************************************

char 			messageCode			(unsigned char * message, unsigned char message_len){
	// send it back in source raw view
	return message_len;
}

//***************************************************************************

char 			messageDecode		(unsigned char * message, unsigned char message_len){
	// send it back in source raw view
	return message_len;
}

//***************************************************************************