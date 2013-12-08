

#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include "config.h"
#include "stm32f2xx.h"
#include "comp_adc.h"
#include "comp_fish.h"

#define AMF_SYS_10MS     (sys_data.clock_cycle % 1)
#define AMF_SYS_100MS     (sys_data.clock_cycle % 10)
#define AMF_SYS_300MS     (sys_data.clock_cycle % 30)
#define AMF_SYS_400MS     (sys_data.clock_cycle % 40)
#define AMF_SYS_500MS     (sys_data.clock_cycle % 50)
#define AMF_SYS_1S           (sys_data.clock_cycle % 100)
#define AMF_SYS_2S           (sys_data.clock_cycle % 200)
#define AMF_SYS_5S           (sys_data.clock_cycle % 500)


#define AMF_SYS_TIMER_FLG_10MS     0x1
#define AMF_SYS_TIMER_FLG_100MS    0x2
#define AMF_SYS_TIMER_FLG_300MS    0x4
#define AMF_SYS_TIMER_FLG_400MS    0x8
#define AMF_SYS_TIMER_FLG_500MS    0x10
#define AMF_SYS_TIMER_FLG_1S      0x20
#define AMF_SYS_TIMER_FLG_2S      0x40
#define AMF_SYS_TIMER_FLG_5S      0x80


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
struct system_data {

    //gpio_configration
    unsigned int gpio_mode[MAX_PIN_GROUP];
    unsigned int gpio_otyper[MAX_PIN_GROUP];
    unsigned int gpio_ospeedr[MAX_PIN_GROUP];
    unsigned int gpio_pupdr[MAX_PIN_GROUP];
    unsigned int gpio_af[2][MAX_PIN_GROUP];



    //ATCA related
    //for IPMC 
    __IO uint16_t aADCTripleConvertedValue[24];/* voltage in digital format */
    VOLTAGE_MONITOR_t *sys_vtg_cur;
    unsigned char     *sys_temp;
    float             power;

    //for ShMC 
    //unsigned char pim48vdc_alarm;                 //48V电源模块错误信息
    //for shelf
    unsigned char board_state;/* bit[7:4] board power state; bit[3:0] IPMC state */


    //operation system related
    //for RTOS
    __IO unsigned long clock_cycle;

    //for FiSH (faster Interface SHELL)
    HUIF_FISH_t fish;
    unsigned char display_all_flg;

    //for task running 
    unsigned char task_timer_flg;/* bit0:10ms bit1:100ms bit2:300ms bit3:400ms bit4:500MS bit5:1S bit6:2S bit7:5S */
};


extern struct system_data sys_data;



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

