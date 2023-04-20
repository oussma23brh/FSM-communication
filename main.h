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
#define START_CHAR   's'
#define BCAST_CHAR   'b'
#define UCAST_CHAR   'u'
#define READ_CMD    'r'
#define GET_CMD    'g'
#define BCAST_TEST 't'
#define END_CHAR   '*'


/*prototypes*/
void my_RX_ISR(void);
void init_clear_buffer(void);
void fill_buffer(char received_char);
void Initialize(void);
void Idle(void);
void Destination_Check(void);
void Parse(void);
void Decode(void);
void Execute(void);
int get_ID(void);
int parse_frame_ID(void);




/*types*/
typedef enum {SETUP, IDLE, PARSING} UART_state;
UART_state frame_state;
//transmitted data destination
typedef enum {BROADCAST , UNICAST, MULTICAST} comm_mode;
comm_mode destination, prev_destination = UNICAST;
//
typedef enum { RST , DEST_CHK , PARSE , DECODE , EXECUTE } State_Type ;
//table containing a function for each state
void (*function_table [])() = { Idle , Destination_Check , Parse , Decode , Execute };
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
char frame_buffer[20];
//index for the frame buffer
int frame_index;
//store ADC conversion result




