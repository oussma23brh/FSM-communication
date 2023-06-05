/* 
 * File:   main.h
 * Author: oussama
 *
 * Created on 01 March 2023, 15:45
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

/*included files*/
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "ADC_driver.h"

/*defines*/
#define START_CHAR   '$'
#define BCAST_CHAR   'B'
#define UCAST_CHAR   'U'
#define READ_CMD    'R'
#define GET_CMD    'G'
#define BCAST_TEST 'C'
#define END_CHAR   '*'
#define MAX_BUFFER_SIZE 20


/*prototypes*/
void my_RX_ISR(void);
void clear_buffer(char* buffer);
void fill_buffer(char received_char);
void Initialize(void);
void Idle(void);
void ReceivedFrameChecksum(void);
void Destination_Check(void);
void Parse(void);
void Decode(void);
void Execute(void);
int get_ID(void);
int parse_frame_ID(void);
void ChecksumCalc(char* dataString);
void TrimFrame(void);
void TrimAckFrame(char* AckFrame);
void GetChecksumValue(void);
void ACKframeChecksum(char* acknowledge_frame);
void PrintString(char* String);





/*types*/
typedef enum {SETUP, IDLE, PARSING} UART_state;
UART_state frame_state;
//transmitted data destination
typedef enum {BROADCAST , UNICAST, MULTICAST} comm_mode;
comm_mode destination, prev_destination = UNICAST;
//
typedef enum { RST , ERROR_CHECK, DEST_CHK , PARSE , DECODE , EXECUTE } State_Type ;
//table containing a function for each state
void (*function_table [])() = { Idle , ReceivedFrameChecksum, Destination_Check , Parse , Decode , Execute };
//the currently running state
State_Type curr_state ; 

/*global variables*/
//flags to control execution of the commands
uint8_t read_flag=0;
uint8_t get_flag=0;
uint8_t broadcast_test_flag=0;
//flag to start filling the buffer
char frame_ready_flag=0;
//flag to set_up the buffer
char init_buffer_flag = 0;
//array to hold the address of destination device
char frameAddress[2];
char realAdress[2];//real address of prob
int add_digit_1,add_digit_2;
//char to store command 
char command;
uint8_t command_index;
//array to store content of the received frame
char frame_buffer[MAX_BUFFER_SIZE];
//index for the frame buffer
int frame_index;
//store ADC conversion result
char fullAckFrame[MAX_BUFFER_SIZE];// Acknowledgement frame to be sent as handshake
char TrimmedFrame[MAX_BUFFER_SIZE]; // received frame trimmed of start and end characters and CRC
char TrimmedAckFrame[MAX_BUFFER_SIZE];//Trimmed Acknowledge frame
char FrameCheckSum[3]; //Checksum value received from the frame
char CRCresult[2];// CRC result calculated from received frame




