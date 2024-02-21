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



void main(void)
{
    
    SYSTEM_Initialize();
    i2c_driver_init();  //initialize I2C serial communication
    EUSART1_SetRxInterruptHandler(my_RX_ISR);
    TMR0_SetInterruptHandler(Timer0IntHandler);
    TMR1_SetInterruptHandler(Timer1IntHandler);
    TMR3_SetInterruptHandler(Timer3IntHandler);
    
    INTERRUPT_GlobalInterruptEnable();      // Enable the Global Interrupts
    
    INTERRUPT_PeripheralInterruptEnable();  // Enable the Peripheral Interrupts
    
    Initialize();       // Initialize the parsing FSM
    
    //send_string("Hello!\n");
    //AD5593_init_w_EVREF();        //reset and ititialize AD5593 to operate with EVREF
    ADC_reset();                  //reset the LMP92001
    //send_string("Reset DONE! \n");
    __delay_ms(1);       //wait for the adc to reset
    ADC_init();        //initialize the LMP92001
    //send_string("ADC ready!\n");    
    while (1)
    {
        if(frame_ready_flag){
            function_table[curr_state]();
        }
    }   
}

void my_RX_ISR(void){
    RX_LED_SetLow();
    TMR3_StartTimer();      //Start the timer
        //frame character received
        char frame_char;
        //read from UART port
        frame_char = EUSART1_Read();
        //UART FSM
        switch(frame_state){
            //setup for next frame
            case SETUP:
                frame_index = 0;
                clear_buffer(frame_buffer);
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
                //to avoid being stuck in an infinite-loop if '*' doesn't arrive
                if (frame_index >= MAX_BUFFER_SIZE) frame_state = SETUP;
                fill_buffer(frame_char);
                if(frame_char == END_CHAR){
                    frame_ready_flag = 1; 
                    fill_buffer('\0');
                    curr_state = ERROR_CHECK;
                    frame_state = SETUP; //back to SETUP state 
                }
                break;
        }
}

void Timer0IntHandler(void){
    timer0_flag = 1;
}

void Timer1IntHandler(void){
    TX_LED_SetHigh();
    TMR1_StopTimer();
    TMR1_Reload();
}

void Timer3IntHandler(void){
    RX_LED_SetHigh();
    TMR3_StopTimer();
    TMR3_Reload();
}

//clear and setup the buffer for the frame
void clear_buffer(char* buffer){
    int i;
    for(i=0;i<strlen(buffer);i++){
        buffer[i] = '\0';
    }
}

//fill buffer with received char
void fill_buffer(char received_char){
        frame_buffer[frame_index++] = received_char;
}

/*initialize FSM*/
void Initialize(void){
    curr_state = RST;
    frame_state = SETUP;
}

/*wait for the start of the frame*/
void Idle(void){
    while(!frame_ready_flag);
    curr_state = ERROR_CHECK;
}

void ReceivedFrameChecksum(void){
    //send_string("The received frame: "); 
    send_string(frame_buffer); send_string("\n");
    clear_buffer(TrimmedFrame);
    clear_buffer(CRCresult);
    clear_buffer(FrameCheckSum);
    TrimFrame(); //Trim the received frame
    
    GetChecksumValue();//obtain the checksum value sent with the frame
    
    int hexFrameCheckSum = (int)strtol(FrameCheckSum, NULL, 16);
    
    
    ChecksumCalc(TrimmedFrame); //Calculate the checksum for the trimmed frame
    //send_string("Result of XOR checksum: ");    send_string(CRCresult); send_string("\n");
    int hexCRCresult = (int)strtol(CRCresult, NULL, 16);

    //check whether there was an error on transmission or not
    if(hexCRCresult == hexFrameCheckSum){       
        //send_string("No Error! Frame is valid.\n");
        curr_state = DEST_CHK;
    }
    else{
        //send_string("Error! Ignore frame.\n");
        frame_ready_flag = 0;
        curr_state = RST;
    }
    
}

/*checking transmission type*/
void Destination_Check(void){
    switch(frame_buffer[1]){
        case BCAST_CHAR: 
            destination = BROADCAST;
            break;
        case UCAST_CHAR:
            destination  = UNICAST;
            break;
        default:             
            frame_ready_flag = 0;
            curr_state = RST;   //return to IDLE
            break;
    }
    curr_state = PARSE;
}

void Parse(void){
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
    frameID = parse_frame_ID();     //get ID from the frame
    
    hardID = get_ID();         //get ID of device from DIPs
  
    char message[200];
  
    //send_string("I am in Decode state\n");
    //send_string("address from frame: ");
    //sprintf(frameAddress,"%d",frameID);
    //send_string(frameAddress); send_string("\n");
    //send_string("address from hardware is:");
    //sprintf(realAdress,"%d",hardID); 
    //send_string(realAdress);  send_string("\n");
    

    //respond to command on broadcast or if address matches  
    if((destination == BROADCAST) || ( (destination == UNICAST) && (frameID == hardID) )){
        switch(command){
            case READ_CMD:
                read_flag = 1;//set reading flag
                break;
            case GET_CMD:
                get_flag = 1;//set sending flag
                break;
            case BCAST_TEST:
                broadcast_test_flag = 1;
                break;
            default:
                //send_string("Command character error\n");
                goto exitToRST;
                break;
        }
        curr_state = EXECUTE;
    }
    else{
exitToRST:
        frame_ready_flag = 0;
        frame_index = 0;
        clear_buffer(frame_buffer);
        curr_state = RST;       //if frameID and hardID don't match IGNORE the frame
        //send_string("Device address error.\n");
    }   
}

void Execute(void){  

    char acknowledge_frame[30];
    /*clear the acknowledgment frame*/
    uint8_t k;
    for(k=0;k<30;k++){
        acknowledge_frame[k] = NULL;
    }
    //send_string("received frame: "); send_string(frame_buffer); send_string("\n");
    
    /*push characters (START_CHAR -> CMD_CHAR) to acknowledgment frame*/
    sprintf(acknowledge_frame,"$U%.2d%c",hardID,command);
    
    /*Execute frame CMD */
    /*~~READ CMD~~*/
    if(read_flag){
        TMR0_StartTimer();          //Start the timer
        while(!timer0_flag);        //wait for timer to finish
        TMR0_StopTimer();           //Stop the timer
        timer0_flag = 0;            //reset the timer's flag
        TMR0_Reload();              //Reload the timer
        //AD5593_ADC_read();        //Call AD5593_read
        ADC_read();                 //trigger the LMP92001 conversion
        if(destination == BROADCAST){ 
            frame_ready_flag = 0;
            read_flag = 0; //clear read flag at the end of operation
            prev_destination = destination;     //update the previous destination state
            goto exitToIDLe;    //exit and don't respond to 'BROADCAT frame'
        }     
        /*acknowledge the read command*/
        sprintf(acknowledge_frame + strlen(acknowledge_frame),"OK");
        read_flag = 0; //clear read flag at the end of operation
    /*~~GET CMD~~*/
    }else if(get_flag){
        if(destination == BROADCAST){   
            frame_ready_flag = 0;
            get_flag = 0; //clear get flag at the end of operation
            prev_destination = destination;     //update the previous destination state
            goto exitToIDLe;    //exit immediately on "BROADCAST get frame"
        }
       
        /*ADC conversion result*/
        char data_ch1[10],data_ch2[10],data_ch3[10],data_ch4[10];
        sprintf(data_ch1,"%0.4x",ADC_result[0]);  data_ch1[4] = '\0';
        sprintf(data_ch2,"%0.4x",ADC_result[1]);  data_ch2[4] = '\0';
        sprintf(data_ch3,"%0.4x",ADC_result[2]);  data_ch3[4] = '\0';
        sprintf(data_ch4,"%0.4x",ADC_result[3]);  data_ch4[4] = '\0';
        
        //send_string("Result of ch1    "); send_string(data_ch1); send_string("\n");
        //send_string("Result of ch2    "); send_string(data_ch2); send_string("\n");
        //send_string("Result of ch3    "); send_string(data_ch3); send_string("\n");
        //send_string("Result of ch4    "); send_string(data_ch4); send_string("\n");
        
        /*fill acknowledgment frame with ADC data*/
        memcpy(acknowledge_frame + strlen(acknowledge_frame), data_ch1, strlen(data_ch1));
        memcpy(acknowledge_frame + strlen(acknowledge_frame), data_ch2, strlen(data_ch2));
        memcpy(acknowledge_frame + strlen(acknowledge_frame), data_ch3, strlen(data_ch3));
        memcpy(acknowledge_frame + strlen(acknowledge_frame), data_ch4, strlen(data_ch4));
        get_flag = 0; //clear get flag at the end of operation

    /*~~BCAST TEST CMD~~*/    
    }else if(broadcast_test_flag){
        //send_string("Broadcast test.\n");
        if(BROADCAST == prev_destination){
            //send_string("Broadcast frame received\n");
            sprintf(acknowledge_frame + strlen(acknowledge_frame),"%s","YS");
        }else{
            //send_string("Broadcast frame not received\n");
            sprintf(acknowledge_frame + strlen(acknowledge_frame),"%s","NO");
        }       
        broadcast_test_flag = 0; //clear flag at the end of operation
    }
    /*add checksum for acknowledgment frame*/
    ACKframeChecksum(acknowledge_frame);
    //send_string("The acknowledge frame: ");
    send_string(fullAckFrame); send_string("\n");
    frame_ready_flag = 0;   //clear frame flag when done with executing
    prev_destination = destination;     //update the previous destination state
exitToIDLe:
    curr_state = RST;      //back to initial state
}


//get the address of the device from dip switches
int get_ID(void){
    return  DIP1_GetValue() | DIP2_GetValue() << 1 | DIP3_GetValue() << 2 | DIP4_GetValue() << 3 | DIP5_GetValue() << 4;
}

//get the address received from the frame
int parse_frame_ID(void){
    return add_digit_1 * 10 + add_digit_2;
}

/*Fuction that finds the checksum of a given string*/
void ChecksumCalc(char* dataString){
    uint8_t xorTemp;
    xorTemp = (uint8_t)dataString[0];
    for(int i = 1; i < strlen(dataString); i++){
        xorTemp ^= (uint8_t)dataString[i];
        }
    sprintf(CRCresult,"%.2X",xorTemp);
}

/*  Function that removes the CHECKSUM_VAL and END_CHAR(*)  */
void TrimFrame(void){
    uint8_t index = 0;
    uint8_t i;
    for(i = 0; i < strlen(frame_buffer)-3; i++){
        TrimmedFrame[index] = frame_buffer[i];
        index++;
    }
    TrimmedFrame[index] = '\0';
}

/*Function that puts the checksum value in an array*/
void GetChecksumValue(void){
    uint8_t index = 0;
    uint8_t i=0; 
    
    for(i = strlen(frame_buffer)-3; i < strlen(frame_buffer)-1; i++){
        FrameCheckSum[index] = frame_buffer[i];
        index++;
    }
    //send_string("Received frame: "); send_string(&receivedFrame); send_string("\n");
    FrameCheckSum[index]='\0';
}

void ACKframeChecksum(char* frame){

    clear_buffer(fullAckFrame); 
    
    ChecksumCalc(frame); //Calculate the checksum for ACK frame

    sprintf(fullAckFrame, "%s%c%c%c\0",frame,CRCresult[0],CRCresult[1],END_CHAR);
    //send_string("Acknowledgment frame to be sent: ");  send_string(fullAckFrame);  send_string("\n");
}

/**
 End of File
*/