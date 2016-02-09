#include "commondefines.h"
#include "message.h"
#include "ports.h"

//************************************************************

#define G_TIMER_COUNT 5
enum G_TIMER_NAMES_POSITIONS {ALL_TIMERS_INC_TIMER = 0, CHECK_MODULES_TIMER = 1};
enum G_TIMER_NAMES_VALUES {ALL_TIMERS_INC_TIMER_VALUE = 0, CHECK_MODULES_TIMER_VALUE = 100};
volatile unsigned int g_timers[G_TIMER_COUNT];
void initTimers(){
	for (char i = 0; i < G_TIMER_COUNT; i++)
		g_timers[i] = 0;
}
//***************************
void initAll(){
	initTimers();
	initPorts();
	initIRQ();
}
//***********************************************************



//***********************************************************

enum RFMRELAYFSMSTATES {START, SCAN_PORTS, SET_PORTS, CHECK_MODULES, SEND_TO_MODULES, DECODE_MESSAGE, CODE_MESSAGE};

void rfmRelayFSM(){
	static char state = START;
	
	static unsigned char message[MAX_MESSAGE_LEN];
	static unsigned char message_len = 0;
	
	switch (state) {
	
		case START:
			initAll();
			state = SCANPORTS;
			break;

		case SCAN_PORTS:
			if (!portsStateChanged()){
				state = CODE_MESSAGE;
			}
			if (g_timers[CHECK_MODULES_TIMER] >= CHECK_MODULES_TIMER_VALUE){
				state = CHECK_MODULES;
			}
			break;
			
		case CODE_MESSAGE:
			message_len = messageBuild(message, message_len, portsStateGet());
			message_len = messageCode(message, message_len);
			state = SEND_TO_MODULES;
			break;
			
		case SEND_TO_MODULES:
			rfmToWriteMode();
			rfmWrite(message, message_len);
			rfmToReadMode();
			state = SCAN_PORTS;
			break;
			
		case CHECK_MODULES:
			message_len = rfmRead(message);
			state = message_len ? DECODE_MESSAGE : SCAN_PORTS;
			g_timers[CHECK_MODULES_TIMER] = 0;
			break;
			
			case DECODE_MESSAGE:
			message_len = messageDecode(message,message_len);
			if (message_len) { // NO Errors
				state = SET_PORTS;
			}else{
				state = SCAN_PORTS;
			}
			break;
			
		case SET_PORTS:
			portsStateSet(messageParseState(message, message_len));
			state = SCAN_PORTS;
			break;
	
		default:
			// some thing incridable 
			state = SCAN_PORTS;
			break;
	
		
	}
	

	
}