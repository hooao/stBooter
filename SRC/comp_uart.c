
//This is comp_uart.c
//This file mainly offer component of the uart.


#include <stdio.h>
#include "stm32f2xx.h"
#include "system.h"
#include "comp_fish.h"
#include "comp_uart.h"

#include "errcode.h"







unsigned char pendsv_flag;
USART_RX_BUFFER_RING RxBufRing;
__IO char uart_cache[32];//存放uart收到的数据
__IO char uart_buffer[16];//在命令解析的过程中，存放一个命令
unsigned char cmd_counter = 0;//uart_buffer中存放命令的字符数
char *p_uart_produce = NULL;
char *p_uart_custom = NULL;
static unsigned long uart_recv_cycle_last = 0;
FISH_CMD_t fish_command_list[FISH_MAX_CMD_SUPPORT];

unsigned char SizeOfRxBody = 0;		   
unsigned char  TxCounter=0;					  //发送计数器
unsigned char  RxCounter=0; 				  //接收计数器
unsigned char  UsartRxFullFlag = 0;

char send_byte(USART_TypeDef * UARTx, unsigned char ch)
{
    while (!(UARTx->SR & 0x0080))
        ;
    UARTx->DR = (ch & 0xFF);
    return 0;
}

char send_buf(USART_TypeDef * UARTx, unsigned char *buf, int len)
{
	    int i = 0;
	    if(len <=0 )
			return -1;
	    for(i = 0; i < len; i++)
    	    send_byte(UARTx,*(buf+i));
			return i;
}
char recv_buf(USART_TypeDef * UARTx, unsigned char *buf, int len)
{
	    int i = 0;
	    if(len <=0 )
			return -1;
	    for(i = 0; i < len; )
        {
            if(get_byte(UARTx,(buf+i)) != -1)
            i++;
        }
		return i;
}

char put(unsigned char ch)
{
    send_byte(UART4, ch);
    return 0;
}
char get_byte(USART_TypeDef * UARTx, unsigned char *ch)
{
    //if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	int try = 0xfffff;
    while((USART_GetITStatus(UART4, USART_IT_RXNE) == RESET) && (try--))
			;
		if(try > 0)
		{
        *ch = UARTx->DR;
        return 0;
		}
    else
    return (-1);
}


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
  return (send_byte(UART4,c));
}

char putstr(char *str)
{  
    int i;
    for(i = 0; i < strlen(str); i++)
    send_byte(UART4, *(str+i) );
    return 0;
}


void usartBufferInit(void)
{
	RxBufRing.pBufBegin = &(RxBufRing.usartBuf[0]);
	RxBufRing.pBufEnd = &(RxBufRing.usartBuf[USART_RX_BUFFR_CNT*USART_MSG_LEN_MAX-1]);
	RxBufRing.pBufPut =  &(RxBufRing.usartBuf[0]);
	RxBufRing.pBufGet = &(RxBufRing.usartBuf[0]);
	memset(&(RxBufRing.usartBuf[0]), 0, USART_RX_BUFFR_CNT*USART_MSG_LEN_MAX);
}



//echo

//uart4 handler
//the handler, receive date from "terminal" only.
void UART4_IRQHandler()
{
  static int counter;
	counter = 0;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)	
    {
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
        *p_uart_produce = USART_ReceiveData(UART4);
        if(p_uart_produce == &uart_cache[31])
            p_uart_produce = uart_cache;
        else
            p_uart_produce ++;
    }
}




int uartCmdAnalize()
{
 
	return OK;
}

void USART2_IRQHandler()
{
    unsigned char *pRxBufHead = RxBufRing.pBufPut ;
    
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)				//检测是否是接收中断
    {	
    	     USART_ClearITPendingBit(USART2, USART_IT_RXNE);       //清除中断标志    
    	     pRxBufHead[RxCounter++]= USART_ReceiveData(USART2);

            if(pRxBufHead[0]!=0xaa)
	      {
		      RxCounter = 0;
		      return;
        }	  
	      if(RxCounter == sizeof(SERIAL_HEAD))
	      {
					if(pRxBufHead[1]!=0x55)
					{
						RxCounter = 0;
						return;
					}
					SizeOfRxBody=pRxBufHead[4];
	      }
	      if(SizeOfRxBody>USART_BODY_LEN_MAX)
	      {
					RxCounter = 0;
					return;
	      }
	      if(RxCounter == SizeOfRxBody+USART_HARD_LEN)								//如果接收数据量等于接收数据长度+6字节头+2字节checksum
	      {	
                USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
				uartCmdAnalize();
                USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	            RxBufRing.pBufGet = RxBufRing.pBufPut;
	      		RxBufRing.pBufPut += RxCounter;
	      		if(RxBufRing.pBufPut > RxBufRing.pBufEnd)
	      		    RxBufRing.pBufPut = RxBufRing.pBufBegin;
	      		RxCounter=0;      
	      }
       }
}
