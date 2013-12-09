
#include "config.h"
#include "system.h"
#include "version.h"


unsigned long long bootTick = 0;

void srvAmfEarlyInit()
{
    usartBufferInit();

}


void srvAmfDC12vIpmcUpCtrOn(void)
{
    int i;
    //GPIOG->BSRRH = 1UL <<  11;//12v DC
    GPIOE->ODR |= 1UL <<  3;
    i=0xffffff;
    while(--i);
        ;
}

void srvAmfPayloadOn(void)
{
    //GPIOB->BSRRH = 1UL <<  13;//payload
    GPIOB->BSRRL |= 1UL <<  13;

}

void srvAmfPayloadOff(void)
{
    GPIOB->BSRRH |= 1UL <<  13;//payload
}


void srvAmfDC12vOn(void)
{
    int i;
    //GPIOG->BSRRH = 1UL <<  11;//12v DC
    GPIOG->ODR |= 1UL <<  11;
    //delay a little bit
    i=1000;
    while(i--)
        ;

}

int srvBoardInit()
{
    srvAmfEarlyInit();
    bootloader_stage1();
    fish_init();
    
#ifndef BARE_ENVIRONMENT
    srvAmfPayloadOff();
    while(!AMF_SYS_48V_ALARM)
    {
    //调用48v模块的i2c接口，将错误信息记录到sys_data结构体中
    // sys_data.pim48vdc_alarm = module_48vdc_alarm();
    }
    
    srvAmfDC12vIpmcUpCtrOn();
    srvAmfDC12vOn();
	
   	while(!AMF_SYS_POWEROK)
        ;
#endif
}

int srvSleep(unsigned int sec)
{
    unsigned long long curTick;
    curTick = bootTick;
    while((bootTick - curTick) < (10 * sec))
    ;
    return 0;
}


////////////////system tick handler////////////
void SysTick_Handler(void)
{
    bootTick ++;
}

