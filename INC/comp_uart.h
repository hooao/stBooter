
#ifndef __COMP_UART_H__
#define __COMP_UART_H__

#include <stm32f2xx.h>

#define USART_MSG_LEN_MAX 64
#define USART_BODY_LEN_MAX	(USART_MSG_LEN_MAX-16)
#define USART_HARD_LEN		5
#define USART_VERIFY_LEN	2
#define USART_RX_BUFFR_CNT 1

typedef struct{
	unsigned char *pBufPut;
	unsigned char *pBufGet;
	unsigned char *pBufBegin;
	unsigned char *pBufEnd;
	unsigned char usartBuf[USART_MSG_LEN_MAX*USART_RX_BUFFR_CNT];
}USART_RX_BUFFER_RING;

typedef struct SERIAL_HEAD_CTX
{
	unsigned char magic1;  /* 0xaa */
	unsigned char magic2;  /* 0x55 */
	unsigned char srcSlot;  
	unsigned char dstSlot;  
	unsigned char bodyLen; /* body len :not include crc checkout 2bytes*/
//	unsigned char body[0];
}SERIAL_HEAD;


char send_byte(USART_TypeDef * UARTx, unsigned char ch);
char get_byte(USART_TypeDef * UARTx, unsigned char *ch);
char put(unsigned char ch);


//valiable used by fis
extern __IO char uart_cache[32];
extern __IO char uart_buffer[16];
extern char *p_uart_produce;
extern char *p_uart_custom;
extern  unsigned char cmd_counter;


#endif
/*EOF*/
