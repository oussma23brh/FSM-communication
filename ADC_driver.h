/* 
 * File:   ADC_driver.h
 * Author: oussama
 *
 * Created on 20 April 2023, 12:39
 */

#ifndef ADC_DRIVER_H
#define	ADC_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ADC_DRIVER_H */

/*included files*/
#include "i2c_driver.h"


/*defines*/
#define ADC_I2C_ADDRESS 0x40
#define REF_REGISTER 0x66
#define GEN_STATUS 0x10
#define GEN_CONTROL 0x14
#define ADC_CH_EN_1 0x19
#define CONV_TRIG 0x1C
#define ADC_RESULT_CH_1 0x20
#define ADC_RESULT_CH_2 0x21
#define ADC_RESULT_CH_3 0x22
#define ADC_RESULT_CH_4 0x23

/*prototypes*/
void ADC_reset(void);
void ADC_init(void);
void ADC_read(void);


/*global variables*/
uint16_t ADC_result0 = 0x0FFF;
uint16_t ADC_result[4]; //array to hold ADC conversion results
double SC_voltage = 0;       //voltage at output of signal conditioning circuit
double voltage = 0;       //Analog value
char ResultBuffer[15];      //buffer to hold characters to be displayed on terminal
char DigitalBuffer[20];
char SCBuffer[20];


