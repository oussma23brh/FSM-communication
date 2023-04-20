#include <xc.h>
#include <stdint.h>
#include "ADC_driver.h"


/*Initialize the LMP92001 ADC & configure the 4 channels*/
void ADC_init(void){
    i2c_driver_write_byte(ADC_I2C_ADDRESS, ADC_CH_EN_1, 0x0F);      //configure ADC channels
    i2c_driver_write_byte(ADC_I2C_ADDRESS, GEN_CONTROL, 0x02);       //lock the internal registers
}

/*Reset the LMP92001 module*/
void ADC_reset(void){
    //send_string("Start of reset \n");
    i2c_driver_write_byte(ADC_I2C_ADDRESS,GEN_CONTROL,0x80);  //send reset command words
    //I2C1_Write1ByteRegister(ADC_I2C_ADDRESS, GEN_CONTROL, 0x80);        //send reset command words
    //send_string("End of reset \n");
}

/*Trigger conversion and read result*/
void ADC_read(void){
    i2c_driver_write_byte(ADC_I2C_ADDRESS, GEN_CONTROL, 0x02);       //lock the internal registers
    i2c_driver_write_byte(ADC_I2C_ADDRESS,CONV_TRIG, 0x00);        //trigger conversion
    uint8_t ADC_data[2];        //buffer to temporarily hold conversion results
    uint8_t busy_status;
    do{
        i2c_driver_read_byte(ADC_I2C_ADDRESS,GEN_STATUS,&busy_status);
    }while(busy_status & (1<<7) !=0);
    i2c_driver_write_byte(ADC_I2C_ADDRESS, GEN_CONTROL, 0x00);       //unlock the internal registers
    //reading the conversion result of ch1
    i2c_driver_read_twobytes(ADC_I2C_ADDRESS, ADC_RESULT_CH_1, &ADC_result0);
    //ADC_result[0] = i2c_driver_read_twobytes(ADC_I2C_ADDRESS, ADC_RESULT_CH_1, uint16_t * data);       //  
    
    /*
    //reading the conversion result of ch2
    I2C1_WriteNBytes(ADC_I2C_ADDRESS,ADC_RESULT_CH_2,1);      //prepare to read conversion results of ch2
    I2C1_ReadNBytes(ADC_I2C_ADDRESS,ADC_data,2);       //read 2 bytes (ch 2) store them in ADC_data
    ADC_result[1] = (ADC_data[0] << 8) | ADC_data[1];
    
    //reading the conversion result of ch3
    I2C1_WriteNBytes(ADC_I2C_ADDRESS,ADC_RESULT_CH_3,1);      //prepare to read conversion results of ch3
    I2C1_ReadNBytes(ADC_I2C_ADDRESS,ADC_data,2);       //read 2 bytes (ch 3) store them in ADC_data
    ADC_result[2] = (ADC_data[0] << 8) | ADC_data[1];
    
    //reading the conversion result of ch4
    I2C1_WriteNBytes(ADC_I2C_ADDRESS,ADC_RESULT_CH_4,1);      //prepare to read conversion results of ch4
    I2C1_ReadNBytes(ADC_I2C_ADDRESS,ADC_data,2);       //read 2 bytes (ch 4) store them in ADC_data
    ADC_result[3] = (ADC_data[0] << 8) | ADC_data[1];
    */
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //untested alternative
    /*
    uint8_t channel = 0;
    uint8_t ch_address = ADC_RESULT_CH_1;       //address of channel to read from
    for(channel = 0; channel < 4; channel++){
        I2C2_WriteNBytes(ADC_I2C_ADDRESS,ch_address,1);      //prepare to read conversion results of chx
        I2C2_ReadNBytes(ADC_I2C_ADDRESS,ADC_data,2);       //read 2 bytes (chx) store them in ADC_data
        ADC_result[channel] = (ADC_data[0] << 8) | ADC_data[1];
        ch_address++;
    }
    */
}
