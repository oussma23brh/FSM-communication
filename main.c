/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "main.h"
#include <stdint.h>


void main(void)
{
    
    SYSTEM_Initialize();
    EUSART1_SetRxInterruptHandler(my_RX_ISR);
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    //sprintf(output_buffer,"I want to die\n");
    //send_string(output_buffer);
    //
    Initialize();
    send_string("Hello!\n");
    while (1)
    {
        if(frame_ready_flag){
            function_table[curr_state]();
        }
    }   
}

void my_RX_ISR(void){
    //if (PIR1bits.RC1IF) // Receive interrupt
    //{
        //frame character received
        char frame_char;
        //read from UART port
        frame_char = EUSART1_Read();
        //UART FSM
        switch(frame_state){
            //setup for next frame
            case SETUP:
                init_clear_buffer();
                frame_state = IDLE; 
            //wait for starting char
            //no break statement here in order not to miss a starting character
            case IDLE:
                if(frame_char ==  START_CHAR ){
                    fill_buffer(frame_char);
                    frame_state = PARSING; 
                }
                break;
            //fill buffer until receiving end char    
            case PARSING:
                fill_buffer(frame_char);

                if(frame_char == END_CHAR){
                    frame_ready_flag = 1; 
                    fill_buffer('*');
                    curr_state = DEST_CHK;
                    frame_state = SETUP; //back to SETUP state 
                }
                break;
        }
        //send_string(frame_buffer);  send_string("\r\n");
   // }
}

//clear and setup the buffer for the frame
void init_clear_buffer(void){
    frame_index = 0;
    uint8_t i;
    for(int i=0;i<20;i++){
        frame_buffer[i] = NULL;
    }
}

//fill buffer with received char
void fill_buffer(char received_char){
        frame_buffer[frame_index++] = received_char;
}

/*initialize FSM*/
void Initialize(void){
    curr_state = RST;
}

/*wait for the start of the frame*/
void Idle(void){
    while(!frame_ready_flag);
    curr_state = DEST_CHK;
}

/*checking transmission type*/
void Destination_Check(void){
    send_string("I am in Destination check state\n");
    switch(frame_buffer[1]){
        case BCAST_CHAR: 
            destination = BROADCAST;
            send_string("i am in broadcast\n");
            break;
        case UCAST_CHAR:
            destination  = UNICAST;
            send_string("i am in unicast\n");
            break;
        default:             
            send_string("Destination character error\n");
            break;
    }
    curr_state = PARSE;
}

void Parse(void){
    send_string("I am in Parse state\n");
    uint8_t i=0;
    if(destination == UNICAST){
            add_digit_1 = frame_buffer[i+2] - '0';
            i++;
            add_digit_2 = frame_buffer[i+2] - '0';
            i++;
    }
    command_index = i+2;
    command = frame_buffer[command_index];
    curr_state = DECODE;
}

    
void Decode(void){
    //get ID from the frame
    uint8_t frameID = parse_frame_ID();
    //get ID of device from DIPs
    uint8_t hardID = get_ID();         //hard_address from dip switches
  
    char message[200];
    /*
    sprintf(message,"address from frame & bID: %d %d        \n",frameID,hardID);
    send_string("\n");
    send_string(message);
    */
    send_string("I am in Decode state\n");
    send_string("address from frame: ");
    sprintf(frameAddress,"%d",frameID);
    send_string(frameAddress); send_string("\n");
    send_string("address from hardware is:");
    sprintf(realAdress,"%d",hardID); send_string("\n");
    send_string(realAdress);
    

    //respond to command on broadcast or if address matches  
    if((destination == BROADCAST) || ( (destination == UNICAST) && (frameID == hardID) )){
        switch(command){
            case READ_CMD:
                read_flag = 1;//set reading flag
                send_string("I am in reading command\n");
                break;
            case GET_CMD:
                if(destination == UNICAST){
                get_flag = 1;//set sending flag
                send_string("I am in sending command\n");
                }
                break;
            case BCAST_TEST:
                broadcast_test_flag = 1;
            default:
                send_string("Command character error\n");
                break;
        }
        curr_state = EXECUTE;
    }
    else{
        frame_ready_flag = 0;
        init_clear_buffer();
        curr_state = RST;       //if frameID and hardID don't match IGNORE the frame
        //check
    }
    
}

void Execute(void){  
    send_string("I am in execute\n");
    char acknowledge_frame[30];
    /*clear the acknowledgment frame*/
    uint8_t k;
    for(k=0;k<30;k++){
        acknowledge_frame[k] = NULL;
    }
    /*push characters (START_CHAR -> CMD_CHAR) to acknowledgment frame*/
    uint8_t i = 0;
    for(i=0;i<command_index+1;i++){
        acknowledge_frame[i] = frame_buffer[i];
    }
    /*Execute frame CMD */
    /*READ CMD*/
    if(read_flag){
        //read data from adc and store it
        if(destination == BROADCAST)    goto exitToIDLe;     //exit and don't respond to 'BROADCAT frame'
        /*acknowledge the read command*/
        acknowledge_frame[i++] = 'o';
        acknowledge_frame[i++] = 'k';
        acknowledge_frame[i++] = '*';//add END_CHAR to acknowledgment frame
        read_flag = 0; //clear read flag at the end of operation
    /*GET CMD*/
    }else if(get_flag){
        if(destination == BROADCAST)    goto exitToIDLe;    //exit immediately on "BROADCAST get frame"
        /*ADC conversion result*/
        uint16_t data = 1111;
        char data_buffer[20];
        sprintf(data_buffer,"%d",data);
        uint8_t j=0;
        /*fill acknowledgment frame with ADC data*/
        for(j=0;j<strlen(data_buffer);j++){
            acknowledge_frame[i+j] = data_buffer[j];
        }
        acknowledge_frame[i+j] = '*';//add END_CHAR to acknowledgment frame
        get_flag = 0; //clear get flag at the end of operation
    /*BCAST TEST CMD*/    
    }else if(broadcast_test_flag){
        if(BROADCAST == prev_destination){
            acknowledge_frame[i++] = 'y';
        }else{
            acknowledge_frame[i++] = 'n';
        }   
        acknowledge_frame[i] = '*';//add END_CHAR to acknowledgment frame
        broadcast_test_flag = 0; //clear flag at the end of operation
    }
    send_string("I am the final frame: \n");
    send_string(acknowledge_frame); send_string("\n");
    frame_ready_flag = 0;   //clear frame flag when done with executing
    prev_destination = destination;     //update the previous destination state
exitToIDLe:
    curr_state = IDLE;      //back to initial state
}


//get the address of the device from dip switches
int get_ID(void){
    return  DIP1_GetValue() | DIP2_GetValue() << 1 | DIP3_GetValue() << 2 | DIP4_GetValue() << 3 | DIP5_GetValue() << 4;
}

//get the address received from the frame
int parse_frame_ID(void){
    return add_digit_1 * 10 + add_digit_2;
}

/*nitialize the LMP92001 ADC & configure the 4 channels*/
void ADC_init(void){
    i2c_driver_write_byte(ADC_I2C_ADDRESS, ADC_CH_EN_1, 0x0F);      //configure ADC channels
    i2c_driver_write_byte(ADC_I2C_ADDRESS, GEN_CONTROL, 0x02);       //lock the internal registers
}

/*Reset the LMP92001 module*/
void ADC_reset(void){
    send_string("Start of reset \n");
    i2c_driver_write_byte(ADC_I2C_ADDRESS,GEN_CONTROL,0x80);  //send reset command words
    //I2C1_Write1ByteRegister(ADC_I2C_ADDRESS, GEN_CONTROL, 0x80);        //send reset command words
    send_string("End of reset \n");
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


/**
 End of File
*/