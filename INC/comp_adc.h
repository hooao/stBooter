


#ifndef _COMP_ADC_H
#define _COMP_ADC_H


#include <stm32f2xx.h>

typedef struct voltage {
    float fpga_core_vtg[6];
    float fpga_core_cur[6];
    float cpu_core_vtg;
    float cpu_core_cur;
    float sys_12v_dc;
    float ddr3_core_vtg;
    float ddr3_core_cur;
    float sys_amf_vtg[7];

}VOLTAGE_MONITOR_t;


#define VOLTAGE_MON_AMF_2V5     0
#define VOLTAGE_MON_AMF_3V0     1
#define VOLTAGE_MON_AMF_1V4     2
#define VOLTAGE_MON_AMF_1V2     3
#define VOLTAGE_MON_AMF_1V1     4
#define VOLTAGE_MON_AMF_1V0     5
#define VOLTAGE_MON_AMF_1V8     6

#endif
/*EOF*/

