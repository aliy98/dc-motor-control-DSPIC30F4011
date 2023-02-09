#ifndef UART_H
#define	UART_H

#define MSG_SIZE 25

void init_uart();
int send_msg_to_UART(char* msg);
  
#endif	/* UART_H */
