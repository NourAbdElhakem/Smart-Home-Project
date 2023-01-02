




#ifndef UART_H_
#define UART_H_

#include "MEMMAP.h"
#include "STDTYPS.h"
#include "UTILS.h"





u8 UART_Recievestring_checksum(u8*str);
void UART_sendstring_checksum(u8*str);

u32 UART_recieveNumber(void);

void UART_sendnumbers(u8 num);

void UART_Recieve_string(u8*str);

void UART_Send_string(u8*str);

u8 UART_periodicReceive(u8*pdata);

u8 UART_Receive(void);

void UART_Send(u8 data);


void UART_init(void);


void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));

void UART_SendNoBlock(u8 data);
u8 UART_ReceiveNoBlock(void);
void UART_sendAsynchronous_string(u8*str);

void UART_RecieveAsynchronous_string(u8*str);

#endif /* UART_H_ */