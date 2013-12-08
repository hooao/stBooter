

#ifndef __COMP_I2C_H
#define __COMP_I2C_H


#define INA219_POINTER_ADDR_CONFIG_REGISTER      0
#define INA219_POINTER_ADDR_SHUNT_VOLTAGE         1
#define INA219_POINTER_ADDR_BUS_VOLTAGE              2
#define INA219_POINTER_ADDR_POWER                          3
#define INA219_POINTER_ADDR_CURRENT                       4
#define INA219_POINTER_ADDR_CALIBRATION                5








unsigned short ina219ReadPower();

#endif

/*EOF*/

