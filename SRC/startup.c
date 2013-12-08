//BSP support for AMF board.
//This startup.c file mainly contain two stages:
// 1, config hardware
// 2, loader user application
#include "stm32f2xx.h"

#include "config.h"
#include "system.h"
#include "comp_gpio.h"
#include "string.h"

#include "stm32f2xx_rcc.h"

#include "stm32f2xx_tim.h"

extern void SystemInit(void);
extern void usartBufferInit(void);

int cfgSysRcc()
{
    //ENable all gpio clock

    RCC->AHB1ENR |= 0xff;//refer to reference manual, RCC_AHB1ENR low 9ibts for gpio0-8
    //ENable periph clock
    //ADC clock
    RCC->APB2ENR |= (7UL <<   8);//Enable ADC1, ADC2, ADC3
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC3 , ENABLE);  
    //serial
    RCC->APB1ENR  |= (1UL << 19);
    //dma clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    //timer4
    RCC->APB1ENR |= (1UL << 2);
    //timer2
    RCC->APB1ENR |= (1UL << 0);
    //i2c2 clock
    RCC->APB1ENR |= (1UL << 22);
    //uart4 clock
    RCC->APB1ENR  |= (1UL << 19);

    //usart2 clock
    RCC->APB1ENR  |= (1UL << 17);

    //syscfg
    RCC->APB2ENR  |= (1UL << 14);
    return 0;
}


int cfgSysNvic()
{


    NVIC_InitTypeDef  NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);


    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
    NVIC_Init(&NVIC_InitStructure);			



    return 0;
}


int cfgPeripGpio()
{
    gpioCfg(gpio_a, GPIOA, 0);
    gpioCfg(gpio_b, GPIOB, 1);
    gpioCfg(gpio_c, GPIOC, 2);
    gpioCfg(gpio_d, GPIOD, 3);
    gpioCfg(gpio_e, GPIOE, 4);
    gpioCfg(gpio_f, GPIOF, 5);
    gpioCfg(gpio_g, GPIOG, 6);
    gpioCfg(gpio_h, GPIOH, 7);
   
    return 0;
}

// HOWTO:
// In order to enable a periph, we need to
// 1, enable periph(do this in config_sys_rcc); 
// 2, config pin in or out(done by config_periph_gpio);
// 3, config different IO feature, which is done by each config_periph_xxx.


/* UART config routine baudrate, date bit, stop bit, parity */
int cfgPeriphUart()
{
/* Configure UART4: 115200 baud @ 42MHz, 8 bits, 1 stop bit, no parity      */
//uart 在apb1总线上，PCLK1 = HCLK / 4 = 30M
//波特率计算方法
// baud_rate=PCLK2/(16*USARTDIV),
// PCLK在本系统中为:30M
// USARTDIV = 30M/(115200 *16)=16.27604166666667
// BRR[15:4]=16
//BRR[3:0]=16*0.276041 = 5
    UART4->BRR = (16 << 4) | 5;
    UART4->CR3 = 0x0000;
    UART4->CR2 = 0x0000;
    UART4->CR1 = 0x200C;
    UART4->CR1 |= (1 << 5);//enable rx interrupt

    return 0;
}

int cfgPeriphSpi()
{
    return 0;
}


//routine:
// 1, ENable adc clock(done by config_sys_rcc)
// 2, ENable corresponding gpio pin(done by gpio_config)
// 3, 
int cfgPeriphAd()
{
    
    return 0;
}


int cfgPeriphDMA()
{
    return 0;
}

int cfgPeriphI2c()
{


    return 0;
}



int cfgPeriphWd()//watch dog timer
{
   return 0;
}

int cfgPeriphExit()
{
return 0;
}

int cfgSysIo()
{//this might contain all useable periph in the board
    
    cfgPeriphUart();
    cfgPeriphSpi();
    cfgPeriphDMA();
    cfgPeripGpio();
    cfgPeriphWd();
    cfgPeriphExit();

    return 0;
}

int cfgSysInit()
{
    return 0;
}


void bootloader_stage1()
{
   //config_sys_init();
 
    cfgSysNvic();
    cfgSysRcc();
    cfgSysIo();

}








/*EOF*/

