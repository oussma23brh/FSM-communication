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

/*defines*/
#define START_CHAR   's'
#define BCAST_CHAR   'b'
#define UCAST_CHAR   'u'
#define READ_CMD    'r'
#define GET_CMD    'g'
#define BCAST_TEST 't'
#define END_CHAR   '*'
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
void i2c_driver_init(void);
void i2c_driver_write_byte(uint8_t devaddr, uint8_t reg, uint8_t data);
void i2c_driver_write_twobytes(uint8_t devaddr, uint8_t reg, uint16_t data);
void i2c_driver_read_byte(uint8_t devaddr, uint8_t reg, uint8_t * data);
void i2c_driver_read_twobytes(uint8_t devaddr, uint8_t reg, uint16_t * data);
void ADC_reset(void);
void ADC_init(void);
void ADC_read(void);


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
uint16_t ADC_result0 = 0x0FFF;
double SC_voltage = 0;       //voltage at output of signal conditioning circuit
double voltage = 0;       //Analog value
char ResultBuffer[15];      //buffer to hold characters to be displayed on terminal
char DigitalBuffer[20];
char SCBuffer[20];




