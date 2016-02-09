#include "ports.h"
#include "commonmakros.h"

volatile unsigned int g_ports_state = 0;

inline unsigned int getPorts(){
	return 0;
}

inline void setPorts(unsigned int ports_state){
	
}

//*********************************************************

char portsStateChanged(){
	unsigned int cur_state = getPorts();
	if (cur_state != g_ports_state){
		g_ports_state = cur_state;
		return TRUE;
	}
	return FALSE;
}

unsigned int portsStateGet(){
	return g_ports_state;
}

void portsStateSet(unsigned int ports_state){
	setPorts(ports_state);
}