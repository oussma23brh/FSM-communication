/* 
 * File:   AD5593R.h
 * Author: oussama
 *
 * Created on 07 January 2024, 14:03
 */

#ifndef AD5593R_H
#define	AD5593R_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* AD5593R_H */



/*included files*/
#include "i2c_driver.h"
#include <stdbool.h>


#define AD5593_I2C_ADDRESS       0x20

/* POINTER BYTE CONSTANTS */
/* Mode bits */
#define AD5593_CONFIG_MODE   0b0000 << 4
#define AD5593_DAC_WRITE     0b0001 << 4
#define AD5593_ADC_READBACK  0b0100 << 4
#define AD5593_DAC_READBACK  0b0101 << 4
#define AD5593_GPIO_READBACK 0b0110 << 4
#define AD5593_REG_READBACK  0b0111 << 4


/*CONFIG_MODE BYTES*/
#define CONFIG_ADC_SEQUENCE      0b0010 // ADC sequence register - Selects ADCs for conversion
#define CONFIG_GP_CONTROL        0b0011 // General-purpose control register - DAC and ADC control register
#define CONFIG_ADC_CONFIG        0b0100 // ADC pin configuration - Selects which pins are ADC inputs
#define CONFIG_PD_REF_CTRL       0b1011 // Power-down/reference control - Enables/disables the reference and powers down the DACs 
#define CONFIG_SOFT_RESET        0b1111 // Resets the AD5593R


/*constants*/
const int _VREF = 0;
const int _2xVREF = 1;


/*prototypes*/
void AD5593_reset(void);
void set_VREF(bool activate);
void set_ADC_BUFF(bool activate);
void set_ADC_range(int range);
void ADC_ch_config(void);
void lock_config_reg(bool lock);
void AD5593_ADC_convert(int channel);
void AD5593_get_conv_result(int channel);
void AD5593_init_VREF(void);
void AD5593_init_w_EVREF(void);
void AD5593_ADC_read(void);


/*global variables*/
uint16_t reg;
uint8_t data[2];
uint16_t ADC_result[4]; //array to hold ADC conversion results
