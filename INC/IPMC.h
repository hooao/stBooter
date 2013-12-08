


#ifndef __IPMC_H__
#define __IPMC_H__

#include"comp_adc.h"


//
typedef struct IPMC_sensor_status_t{

	signed char temp[8];       /*  status area: indicate status value  */
	VOLTAGE_MONITOR_t vtg;     /*   indicate voltage or current value */
	unsigned char power;      /**/
	char hotSwap; 
	char cpuHealth;
	char fruSta;
}IPMC_SENSOR_STA;

typedef struct IPMC_sensor_alarm_t{
	char temp;  /* bit 7-0: each bit indicate one temp alarm status: bit7 temp[7], bit6 temp[6] …
	                      0 no alarm 1- alarm */
	char other;          /*bit 7-3 reserved  bit 2   hotSwap;bit 1   cpuHealth;bit 0   fruSta;    */
	int  vtg;  /* bit 32-0: each bit indicate one voltage or current alarm status: 
	                        bit23 power[23], bit22 power[22] …bit0 power[0],other: reserve
	                        0 no alarm 1- alarm   */

}IPMC_SENSOR_ALARM;

typedef struct IPMC_sensor_limit_t{
	signed char temp[8];      
	VOLTAGE_MONITOR_t vtg;        //limit值为真实值 x 100
}IPMC_SENSOR_LMT;

typedef struct FRU_addr_t{
	    char shelfAddr;      /* system shelf address */
	    char caseAddr;      /* system case address */
	    char phySlotId;      /* physical slot ID in system */
		char logicSlotId;     /* logic slot ID in system*/
		char hardAddr;       /* hard address in system*/
	    char i2cAddr;       /* I2C address */
	    char caseType; 
} FRU_ADDR_AREA;

typedef struct IPMC_data_t{
	IPMC_SENSOR_STA sensorStaTab;     /* sensor status table */
	IPMC_SENSOR_ALARM sensorAlarmTab;   /* sensor alarm table */
	IPMC_SENSOR_LMT sensorLimitTab;   /* sensor limit table */
	FRU_ADDR_AREA fruAddr;           /* FRU address */
	char fruActEn;                       /* ShMC send CMD of active or inavtive of FRU*/
	char alarmFlag;       /* indicate weather exist alarm in seneor alarm table
	                              as long as any of member of sensorAlarmTab exist one '1', alaramFlag=1;
	                                all of member of sensorAlarmTab are '0', alarmFlag=0*/
	unsigned char fruMSRShMCIdentify;          /*
	                                           1,master ShMC;0 IPMC
	                                           */
	char gx36HeartBeat;
} IPMC_DATA_AREA;





extern IPMC_DATA_AREA local_data_pool;

#endif
/*EOF*/

