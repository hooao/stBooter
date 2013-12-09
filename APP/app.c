#include <config.h>
#include "system.h"
#include "version.h"
#include "Ymodem.h"
#include "flash_if.h"


int main()
{			 
		pFunction Jump_To_Application;
    uint32_t JumpAddress;

    srvBoardInit();
    printf("stBooter Loader\r\n");
    printf("Version :%s\r\n", VERSTR);
    printf("Press Enter to active console\r\n");
#if 0
	//jump to new application
	//application running
		   JumpAddress = *(__IO uint32_t *)(APPLICATION_ADDRESS + 4);
		   Jump_To_Application = (pFunction) JumpAddress;
		   __set_MSP(*(uint32_t *)APPLICATION_ADDRESS);
		   //before entering a new application, you should disable all NVIC
		   
		   NVIC->ICER[0] = 0xffffffff;
		   NVIC->ICER[1] = 0xffffffff;
		   NVIC->ICER[2] = 0xffffffff;
		   NVIC->ICER[3] = 0xffffffff;
		   NVIC->ICER[4] = 0xffffffff;
		   NVIC->ICER[5] = 0xffffffff;
		   NVIC->ICER[6] = 0xffffffff;
		   NVIC->ICER[7] = 0xffffffff;
		   
		//   NVIC_DisableIRQ(TIM2_IRQn);
		//   NVIC_DisableIRQ(SysTick_IRQn);
	//	   NVIC_DisableIRQ(UART4_IRQn);
		   //if you want to enter a 
		   Jump_To_Application();
			 #endif
    while(1)
    {
        fish_echo();
    }
    return 0;
}

/*EOF*/

