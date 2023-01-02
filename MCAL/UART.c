
#include "UART.h"

static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;


 u8 str1[20];
static volatile u8*TX_str[20];
static volatile u8 j=0;

volatile u8 uart_flag=0;

u8 num_aft_str;

static u8*RX_str;

void UART_init(void)
{
	
	//setting the baud rate 9600
	
	UBRRL=51;
	
	//clear bit to mode normal speed
	
	CLEAR_BIT(UCSRA,U2X);
	
	
	//enabling the Transmitter or the Receive
	
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	
	
}


void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA, UDRE));
	UDR=data;
}




u8 UART_Receive(void)
{
	
	while(!READ_BIT(UCSRA,RXC));
	
	return UDR ;
}
	
	
	
	
u8 UART_periodicReceive(u8*pdata)
{	if(READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
	
		return 1 ;
	}
	
	return 0;
	
}



void UART_Send_string(u8*str)
{
	u8 i ;
	
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]);
		
	}

	
}


// recieve string with num 
void UART_Recieve_string(u8*str)
{
	 u8 i=0;
	
		str[i]=UART_Receive();
		
	for(;str[i]!='#';)
	{
		++i;
		str[i]=UART_Receive();
		
	}
	
	str[i]=0;
	++i;
	str[i]=UART_Receive();

	num_aft_str=str[i];
	
}

void UART_sendnumbers(u8 num)
{
	
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
	
	
	
}




u32 UART_recieveNumber(void)
{
	
	u32 num;
	
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	
	num=((u32)b0)|((u32)(b1<<8))|((u32)(b2<<16))|((u32)(b3<<24));
	
	return num ;
}

void UART_sendstring_checksum(u8*str)
{
	u8 i ,len=0;
	u16 sum=0;
	
	for(len=0;str[len];len++);
	
	UART_Send(len);

	for(i=0;i<len;++i)
	{
		UART_Send(str[i]);
		
		sum=sum+str[i];
		
	}
	
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
	
	
}


u8 UART_Recievestring_checksum(u8*str)
{
	u8 len ,i,sum_calc=0;
	u16 sum_rec=0;
	u8 b0 , b1 ;
	
	len=UART_Receive();
	for(i=0;i<len;++i)
	{
		str[i]=UART_Receive();
		sum_calc+=str[i];

	}
	
	b0=UART_Receive();
	b1=UART_Receive();
	
	sum_rec=(u16)(b0)|(u16)(b1<<8);
	
	if(sum_rec==sum_calc)
	{
		return 1 ;
		
	}
	else
	{
		return 0 ;
		
	}
	
	
}


void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}


void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

/*
ISR(UART_RX_vect)
{
	
	static u8 i=0;
	RX_str[i]=UART_ReceiveNoBlock();
	++i;
}
*/

ISR(UART_TX_vect)
{
	 static u8 i=1, k=0;
	if(TX_str[k][i]!=0)
	{
		UART_SendNoBlock(TX_str[k][i]);
		i++;
		
	}
	else
	{
		i=1;
		++k;
		
	}
	
	
}

void UART_sendAsynchronous_string(u8*str)
{

	UART_SendNoBlock(str[0]);
	TX_str[j]=str;
	UART_TX_InterruptEnable();
	++j;
	
}

void UART_RecieveAsynchronous_string(u8*str)
{
	RX_str=str;
	UART_RX_InterruptEnable();
	
}


ISR(UART_RX_vect)
{
	
	uart_flag=1;
	UART_Recieve_string(str1);
	
}