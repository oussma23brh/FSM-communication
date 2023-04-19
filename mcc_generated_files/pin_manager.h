/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set DIP1 aliases
#define DIP1_TRIS                 TRISAbits.TRISA0
#define DIP1_LAT                  LATAbits.LATA0
#define DIP1_PORT                 PORTAbits.RA0
#define DIP1_ANS                  ANSELAbits.ANSA0
#define DIP1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define DIP1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define DIP1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define DIP1_GetValue()           PORTAbits.RA0
#define DIP1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define DIP1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define DIP1_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define DIP1_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set DIP2 aliases
#define DIP2_TRIS                 TRISAbits.TRISA1
#define DIP2_LAT                  LATAbits.LATA1
#define DIP2_PORT                 PORTAbits.RA1
#define DIP2_ANS                  ANSELAbits.ANSA1
#define DIP2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DIP2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DIP2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DIP2_GetValue()           PORTAbits.RA1
#define DIP2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DIP2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DIP2_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define DIP2_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set DIP3 aliases
#define DIP3_TRIS                 TRISAbits.TRISA2
#define DIP3_LAT                  LATAbits.LATA2
#define DIP3_PORT                 PORTAbits.RA2
#define DIP3_ANS                  ANSELAbits.ANSA2
#define DIP3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define DIP3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define DIP3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define DIP3_GetValue()           PORTAbits.RA2
#define DIP3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define DIP3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define DIP3_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define DIP3_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISCbits.TRISC3
#define SCL1_LAT                  LATCbits.LATC3
#define SCL1_PORT                 PORTCbits.RC3
#define SCL1_ANS                  ANSELCbits.ANSC3
#define SCL1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCL1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCL1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCL1_GetValue()           PORTCbits.RC3
#define SCL1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SCD1 aliases
#define SCD1_TRIS                 TRISCbits.TRISC4
#define SCD1_LAT                  LATCbits.LATC4
#define SCD1_PORT                 PORTCbits.RC4
#define SCD1_ANS                  ANSELCbits.ANSC4
#define SCD1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SCD1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SCD1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SCD1_GetValue()           PORTCbits.RC4
#define SCD1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SCD1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SCD1_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define SCD1_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set DIP4 aliases
#define DIP4_TRIS                 TRISDbits.TRISD0
#define DIP4_LAT                  LATDbits.LATD0
#define DIP4_PORT                 PORTDbits.RD0
#define DIP4_ANS                  ANSELDbits.ANSD0
#define DIP4_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define DIP4_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define DIP4_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define DIP4_GetValue()           PORTDbits.RD0
#define DIP4_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define DIP4_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define DIP4_SetAnalogMode()      do { ANSELDbits.ANSD0 = 1; } while(0)
#define DIP4_SetDigitalMode()     do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set DIP5 aliases
#define DIP5_TRIS                 TRISDbits.TRISD1
#define DIP5_LAT                  LATDbits.LATD1
#define DIP5_PORT                 PORTDbits.RD1
#define DIP5_ANS                  ANSELDbits.ANSD1
#define DIP5_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define DIP5_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define DIP5_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define DIP5_GetValue()           PORTDbits.RD1
#define DIP5_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define DIP5_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define DIP5_SetAnalogMode()      do { ANSELDbits.ANSD1 = 1; } while(0)
#define DIP5_SetDigitalMode()     do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set CTRL aliases
#define CTRL_TRIS                 TRISEbits.TRISE0
#define CTRL_LAT                  LATEbits.LATE0
#define CTRL_PORT                 PORTEbits.RE0
#define CTRL_ANS                  ANSELEbits.ANSE0
#define CTRL_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define CTRL_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define CTRL_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define CTRL_GetValue()           PORTEbits.RE0
#define CTRL_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define CTRL_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define CTRL_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define CTRL_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/