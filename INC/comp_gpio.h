//name: gpio_config_table
//mainly used for each gpio pin definition.

#ifndef GPIO_CONFIG__H
#define GPIO_CONFIG__H
#include <stm32f2xx.h>


#define gpio_pin_0  0
#define gpio_pin_1  1
#define gpio_pin_2  2
#define gpio_pin_3  3
#define gpio_pin_4  4
#define gpio_pin_5  5
#define gpio_pin_6  6
#define gpio_pin_7  7
#define gpio_pin_8  8
#define gpio_pin_9  9
#define gpio_pin_10  10
#define gpio_pin_11  11
#define gpio_pin_12  12
#define gpio_pin_13  13
#define gpio_pin_14  14
#define gpio_pin_15  15

//Marco for GPIO moder register
#define gpio_mode_IN 0
#define gpio_mode_OP 1
#define gpio_mode_AF 2
#define gpio_mode_AN 3
//Marco for OTYPER mode register
#define gpio_otyper_push_pull 0
#define gpio_otyper_open_drain 1
//Marco for GPIO OSPEEDR register
#define gpio_ospeedr_2M  0
#define gpio_ospeedr_25M  1
#define gpio_ospeedr_50M  2
#define gpio_ospeedr_100M 3
//Marco for GPIO PUPDR
#define gpio_pupdr_none 0    //no pull-up, pull-down
#define gpio_pupdr_pull_up 1
#define gpio_pupdr_pull_down 2
#define gpio_pupdr_reserved   3
//Marco for GPIO AF
#define gpio_af0_system          0
#define gpio_af1_tim1_tim2     1
#define gpio_af2_tim3_tim5     2
#define gpio_af3_tim8_tim11   3
#define gpio_af4_i2c1_i2c3      4
#define gpio_af5_spi1_spi2      5
#define gpio_af6_spi3               6
#define gpio_af7_usart1_usart3                   7
#define gpio_af8_usart4_usart6                   8
#define gpio_af9_can1_can2_tim12_tim14  9
#define gpio_af10_otg_fs_otg_hs               10
#define gpio_af11_eth                                 11
#define gpio_af12_fsmc_sdio_otg_hs         12
#define gpio_af13_dcmi                               13
#define gpio_af14                                         14
#define gpio_af15_eventout                         15


struct gpio_attribute {
    unsigned char setbit; /*determine whether this pin should be set or not */
    unsigned char mode;  /*gpio pin mode:0,in; 1,out;2,af; 3,an*/
    unsigned char otyper;/*out put type*/
    unsigned char ospeedr;/*pin speed*/
    unsigned char pupdr;/*pull up, pull down*/
    unsigned char    af;
};




extern const struct gpio_attribute gpio_a[16];
extern const struct gpio_attribute gpio_b[16];
extern const struct gpio_attribute gpio_c[16];
extern const struct gpio_attribute gpio_d[16];
extern const struct gpio_attribute gpio_e[16];
extern const struct gpio_attribute gpio_f[16];
extern const struct gpio_attribute gpio_g[16];
extern const struct gpio_attribute gpio_h[];


int gpioCfg(const struct gpio_attribute *gpio_grp, GPIO_TypeDef *GPIOx, unsigned char group_num);
#endif
/*EOF*/

