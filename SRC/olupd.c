
#include <stdio.h>
#include "olupd.h"
#include "Ymodem.h"
#include "flash_if.h"

#define SYS_SRAM_END  (0x20000000 + 128 * 1024)
#define PAGE_SIZE     4096
#define PAGE_SHIFT    12

extern int Image$$RW_IRAM1$$ZI$$Limit;
unsigned int *fm_addr = NULL;
unsigned int fm_size = 0; 

unsigned int ram_size;//unused ram size

  
static int appRunInRam()
{
    //ram init
    ram_size = SYS_SRAM_END - Image$$RW_IRAM1$$ZI$$Limit;
	//jump code & execule
//	JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
//	Jump_To_Application = (pFunction) JumpAddress;
	/* Initialize user application's Stack Pointer */
//	__set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
//	Jump_To_Application();

    return 0;
}
//as a bootloader stage 2
//bootloader_stage1();
int updBootloader()
{
    
    return 0;
}


//support mode:x mode, y mode, z mode
//             file
int updFirmware()
{
#ifdef DEBUG_OLUPD
	pFunction Jump_To_Application;
    uint32_t JumpAddress;
#endif
    int timeout;
    int ret;

    ret = YmodemReceive();

    put('\n');
	if(ret != 0)
	{
	    printf("update firmware failed\r\n");
	    return -1;
	}
    if(fm_addr == NULL)
        return -1;
    FLASH_If_Init();
    FLASH_If_Erase(APPLICATION_ADDRESS);
    FLASH_If_Write(APPLICATION_ADDRESS, (unsigned int *)fm_addr, fm_size);
    //lock 
    FLASH_If_lock();
    printf("WARNNING: Amf system NEED A REBOOT\r\n");
    
#ifdef DEBUG_OLUPD
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
		   NVIC_SetVectorTable(0x8000000, 0x4000);
		   __disable_irq();
		//   NVIC_DisableIRQ(TIM2_IRQn);
		//   NVIC_DisableIRQ(SysTick_IRQn);
	//	   NVIC_DisableIRQ(UART4_IRQn);
		   //if you want to enter a 
		   Jump_To_Application();
#endif
    return 0;
}


