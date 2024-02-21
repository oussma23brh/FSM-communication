#include <xc.h>
#include <stdint.h>
#include "ADC_driver.h"
#include "mcc_generated_files/eusart1.h"



/*Initialize the LMP92001 ADC & configure the 4 channels*/
void ADC_init(void){
    i2c_driver_write_byte(ADC_I2C_ADDRESS, ADC_CH_EN_1, 0x0F);       //configure ADC channels
    i2c_driver_write_byte(ADC_I2C_ADDRESS, GEN_CONTROL, 0x02);       //lock the internal registers
    i2c_driver_write_byte(ADC_I2C_ADDRESS, REF_REGISTER, 0x02);      //enable external ADC reference
}

/*Reset the LMP92001 module*/
void ADC_reset(void){
    i2c_driver_write_byte(ADC_I2C_ADDRESS,GEN_CONTROL,0x80);  //send reset command words
}

/*Trigger conversion and read result*/
void ADC_read(void){
    //send_string("Inside read func of ADC \n");
    i2c_driver_write_byte(ADC_I2C_ADDRESS, GEN_CONTROL, 0x02);       //lock the internal registers
    i2c_driver_write_byte(ADC_I2C_ADDRESS,CONV_TRIG, 0x01);        //trigger conversion
    uint8_t ADC_data[2];        //buffer to temporarily hold conversion results
    
    uint8_t busy_status;
    //send_string("just before reading loop \n");
    do{
        //send_string("at the start of the loop \n");
        i2c_driver_read_byte(ADC_I2C_ADDRESS,GEN_STATUS,&busy_status);
        //send_string("at the end of the loop \n");
    }while(busy_status & (1<<7) !=0);
    //send_string("after loop \n");
    
    i2c_driver_write_byte(ADC_I2C_ADDRESS, GEN_CONTROL, 0x00);       //unlock the internal registers
    
    
    //reading the conversion result of ch1
    i2c_driver_read_twobytes(ADC_I2C_ADDRESS, ADC_RESULT_CH_1, &ADC_result[0]);
    //reading the conversion result of ch2
    i2c_driver_read_twobytes(ADC_I2C_ADDRESS, ADC_RESULT_CH_2, &ADC_result[1]);
    //reading the conversion result of ch3
    i2c_driver_read_twobytes(ADC_I2C_ADDRESS, ADC_RESULT_CH_3, &ADC_result[2]);
    //reading the conversion result of ch4
    i2c_driver_read_twobytes(ADC_I2C_ADDRESS, ADC_RESULT_CH_4, &ADC_result[3]);
    //send_string("after reading all data \n");
    
    
}