#include <xc.h>
#include <stdint.h>
 #include "AD5593R.h"
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/device_config.h"



/*Reset the AD5593R module*/
void AD5593_reset(void){
    i2c_driver_write_twobytes_noack(AD5593_I2C_ADDRESS, AD5593_CONFIG_MODE | CONFIG_SOFT_RESET, 0x0DAC);
}

/*Enable or Disable internal VREF*/
void set_VREF(bool activate){
    i2c_driver_read_twobytes(AD5593_I2C_ADDRESS, AD5593_REG_READBACK | CONFIG_PD_REF_CTRL , reg);
    data[0] = (uint8_t)(reg >> 8);
    data[1] = (uint8_t)reg;
    if(activate){
        data[0] |= (1 << 1);    //set the internal ref bit
    }
    else{
        data[0] &= ~(1 << 1);    //reset the internal ref bit
    }
    reg = (data[0] << 8) | data[1];
    i2c_driver_write_twobytes(AD5593_I2C_ADDRESS, AD5593_CONFIG_MODE | CONFIG_PD_REF_CTRL, reg);
}

/*Disable the internal buffer of the ADC*/
void set_ADC_BUFF(bool activate){
    i2c_driver_read_twobytes(AD5593_I2C_ADDRESS, AD5593_REG_READBACK | CONFIG_GP_CONTROL, reg);
    data[0] = (uint8_t)(reg >> 8);
    data[1] = (uint8_t)reg;
    if(activate){
        data[0] |= 0x01;   //set the internal buffer bit
    }
    else{
        data[0] &= ~(0x01);   //set the internal buffer bit
    }
    reg = (data[0] << 8) | data[1];
    i2c_driver_write_twobytes(AD5593_I2C_ADDRESS, AD5593_CONFIG_MODE | CONFIG_GP_CONTROL, reg);
}

/*Set the ADC range:: */
void set_ADC_range(int range){
    i2c_driver_read_twobytes(AD5593_I2C_ADDRESS, AD5593_REG_READBACK | CONFIG_GP_CONTROL, reg);
    data[0] = (uint8_t)(reg >> 8);
    data[1] = (uint8_t)reg;
    if(range == _VREF){
        data[1] &= ~(1 << 5);
    }
    else if(range == _2xVREF){
        data[1] |= (1 << 5);
    }
    reg = (data[0] << 8) | data[1];
    i2c_driver_write_twobytes(AD5593_I2C_ADDRESS, AD5593_CONFIG_MODE | CONFIG_GP_CONTROL, reg);
}

/*Configure the ADC channels (0->3)*/
void ADC_ch_config(void){
    i2c_driver_read_twobytes(AD5593_I2C_ADDRESS, AD5593_REG_READBACK | CONFIG_ADC_CONFIG, reg);
    data[0] = (uint8_t)(reg >> 8);
    data[1] = (uint8_t)reg;
    data[1] |= 0x0F;
    reg = (data[0] << 8) | data[1];
    i2c_driver_write_twobytes(AD5593_I2C_ADDRESS, AD5593_CONFIG_MODE | CONFIG_ADC_CONFIG, reg);
}

/*Lock & Unlock I/O pin configuration register*/
void lock_config_reg(bool lock){
    i2c_driver_read_twobytes(AD5593_I2C_ADDRESS, AD5593_REG_READBACK | CONFIG_GP_CONTROL, reg);
    data[0] = (uint8_t)(reg >> 8);
    data[1] = (uint8_t)reg;
    if(lock){
        data[1] |= (1 << 7);
    }
    else{
        data[1] &= ~(1 << 7);
    }
    reg = (data[0] << 8) | data[1];
    i2c_driver_write_twobytes(AD5593_I2C_ADDRESS, AD5593_CONFIG_MODE | CONFIG_GP_CONTROL, reg);
}

/*Trigger the conversion of an ADC channel*/
void AD5593_ADC_convert(int channel){
    data[0] = 0x00;
    data[1] = (1 << channel);
    reg = (data[0] << 8) | data[1];
    i2c_driver_write_twobytes(AD5593_I2C_ADDRESS, AD5593_CONFIG_MODE | CONFIG_ADC_SEQUENCE, reg);
}

/*Read ADC conversion result*/
void AD5593_get_conv_result(int channel){
    i2c_driver_write_pointer_byte(AD5593_I2C_ADDRESS, AD5593_ADC_READBACK);
    uint16_t conv_result;
    uint8_t ch_address;
    i2c_driver_read_2bytes(AD5593_I2C_ADDRESS, &conv_result);
    ch_address = ((uint8_t)(conv_result >> 12)) & 0x07;
    switch(ch_address){
        case 0:
            ADC_result[0] = conv_result & 0x0FFF;
            break;
        case 1:
            ADC_result[1] = conv_result & 0x0FFF;
            break;
        case 2:
            ADC_result[2] = conv_result & 0x0FFF;
            break;
        case 3:
            ADC_result[3] = conv_result & 0x0FFF;
            break;
        default:
            send_string("Invalid channel. /n");
            break;
    }
}

/*Initialize the AD5593R module to work with INTERNAL VREF*/
void AD5593_init_w_VREF(void){
    AD5593_reset();     //rest the AD5593 module
    __delay_us(250);    //wait for the module to reset
    set_VREF(true);     //enable internal VREF
    set_ADC_range(_2xVREF);     //set max ADC value to 2xVREF
    set_ADC_BUFF(false);        //Disable ADC buffer
    ADC_ch_config();    //Configure ADC channels
}

/*Initialize the AD5593R module to work with EXTERNAL VREF*/
void AD5593_init_w_EVREF(void){
    AD5593_reset();     //rest the AD5593 module
    __delay_us(250);    //wait for the module to reset
    set_VREF(false);     //disable internal VREF
    set_ADC_range(_VREF);     //set max ADC value to VREF
    set_ADC_BUFF(false);        //Disable ADC buffer
    ADC_ch_config();    //Configure ADC channels
}

/*Trigger conversion and read ADC results*/
void AD5593_ADC_read(void){
    lock_config_reg(true);      //lock the internal registers
    __delay_us(5);
    AD5593_ADC_convert(0);      //trigger conversion  of channel 0
    __delay_us(5);             //wait for conversion to end
    lock_config_reg(false);     //unlock the internal registers
    AD5593_get_conv_result(0);  //get conversion result of ch0
    lock_config_reg(true);
    AD5593_ADC_convert(1);      //trigger conversion  of channel 1
    __delay_us(5);             //wait for conversion to end
    lock_config_reg(false);     //unlock the internal registers
    AD5593_get_conv_result(1);  //get conversion result of ch1
    lock_config_reg(true);
    AD5593_ADC_convert(2);      //trigger conversion  of channel 2
    __delay_us(5);             //wait for conversion to end
    lock_config_reg(false);     //unlock the internal registers
    AD5593_get_conv_result(2);  //get conversion result of ch2
    lock_config_reg(true);
    AD5593_ADC_convert(3);      //trigger conversion  of channel 3
    __delay_us(5);             //wait for conversion to end
    lock_config_reg(false);     //unlock the internal registers
    AD5593_get_conv_result(3);  //get conversion result of ch3
}