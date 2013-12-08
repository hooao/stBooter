
/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_it.h"
#include "config.h"
#include "system.h"
#include "ipmc.h"
#include "shmc.h"
unsigned long long pb_cycle_start, pb_cycle_end;
extern IPMC_DATA_AREA local_data_pool;
extern void srvAmfDC12vOff(void);
/** @addtogroup Template_Project
  * @{
  */



/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}



/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

//pow_pb_l
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line5) == SET)
    {
        if((GPIOE->IDR | 0xFFDF) == 0xFFDF)
        {
        /* Clear the EXTI line 5 pending bit */
            pb_cycle_start = sys_data.clock_cycle;
            EXTI_ClearITPendingBit(EXTI_Line5);
        }
        else
        {
            pb_cycle_end = sys_data.clock_cycle;
            if((pb_cycle_end - pb_cycle_start) >= 300)
            {
                if(local_data_pool.sensorStaTab.fruSta != FRU_STATE_S1)//s2,s3,s4,s5
                { 
                    local_data_pool.fruActEn = 0;
            	    local_data_pool.sensorStaTab.fruSta = FRU_STATE_S1;
            	}
            	else
            	{
            	    local_data_pool.fruActEn = 1;//pow 键按下立即请求激活
            	    local_data_pool.sensorStaTab.fruSta = FRU_STATE_S2;
            	}
        	}
            else if((pb_cycle_end - pb_cycle_start) >= 6)
            {
                 //local_data_pool.fruActEn = 0;
            }
        	else
                ;
            pb_cycle_end = pb_cycle_start = 0;
            EXTI_ClearITPendingBit(EXTI_Line5);
        }
    }

}


//every 10ms occur a interrupt
void TIM2_IRQHandler(void)        //rIPMC sensor scan task
{	
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    sys_data.clock_cycle ++;
	
    if(AMF_SYS_400MS == 0)
    {
        //AMF_IPMC_OOSLED_REVERSE;
        sys_data.task_timer_flg |= AMF_SYS_TIMER_FLG_400MS;
        //IWDG_ReloadCounter();
    }
    if(AMF_SYS_500MS == 0)
    {
        sys_data.task_timer_flg |= AMF_SYS_TIMER_FLG_500MS;
       // AMF_IPMC_DEBUGLED_REVERSE;
    }
    if(AMF_SYS_1S == 0)
    {
         sys_data.task_timer_flg |= AMF_SYS_TIMER_FLG_1S;
    }
    if(AMF_SYS_2S == 0)
    {
         sys_data.task_timer_flg |= AMF_SYS_TIMER_FLG_2S;
    }
    if(AMF_SYS_5S == 0)
    {
         sys_data.task_timer_flg |= AMF_SYS_TIMER_FLG_5S;
    }

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
