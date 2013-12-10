

#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include "config.h"
#include "stm32f2xx.h"
#include "comp_fish.h"





#define IPMC_MONITOR_UART_TIMEOUT     60//time out 60s


#define AMF_SYS_LED_OOS_ON     do{GPIOG->BSRRL = 1UL <<  7 ;}while(0)//PG7
#define AMF_SYS_LED_SHMC_ON    do{GPIOE->BSRRL = 1UL <<  0 ;}while(0)//PE0
#define AMF_SYS_LED_IS_ON      do{GPIOD->BSRRL = 1UL <<  7 ;}while(0)
#define AMF_SYS_LED_DEBUG_ON   do{GPIOG->BSRRL = 1UL <<  10;}while(0)
#define AMF_SYS_LED_HS_ON      do{GPIOE->BSRRL = 1UL <<  1 ;}while(0)

#define AMF_SYS_LED_OOS_OFF    do{GPIOG->BSRRH = 1UL <<  7 ;}while(0)
#define AMF_SYS_LED_SHMC_OFF   do{GPIOE->BSRRH = 1UL <<  0 ;}while(0)
#define AMF_SYS_LED_IS_OFF     do{GPIOD->BSRRH = 1UL <<  7 ;}while(0)
#define AMF_SYS_LED_DEBUG_OFF  do{GPIOG->BSRRH = 1UL <<  10;}while(0)
#define AMF_SYS_LED_HS_OFF     do{GPIOE->BSRRH = 1UL <<  1 ;}while(0)

#define AMF_SYS_POWEROK        (GPIOG->IDR & (0x40))
#define AMF_SYS_48V_ALARM   (GPIOE->IDR & (0x40))





//function
void srvAmfDisplay(void);
void srvAmfLedsCheck(void);
void srvAmfDC12vOn(void);
void srvAmfDC12vOff(void);
void serv_amf_payload_on(void);
void srvAmfPayloadOff(void);
void srvAmfWaitBit(void);

int ipmcSetupSlot();
void vDebugLedTask(void * pvParameters);
void vSensorScanTask(void * pvParameters);
void vAlarmTableScan(void * pvParameters);
void vPowerManageTask(void * pvParameters);


#endif
/*EOF*/

