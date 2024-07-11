# Timer Configuration Documentation

This document outlines the configuration and usage of three different timers in our system.     

## Timer Overview

1. **Transmission Timer**   : Controls the duration for which the LED stays on during transmission.
2. **Reception Timer**      : Controls the duration for which the LED stays on during reception.
3. **Voltage Reading Timer**: Sets a 150ms delay for the slave device before it starts reading the voltage.

## Timer Details

### 1. Transmission Timer

**Purpose**: Keeps the LED on for a specified duration during data transmission.   

**Configuration**:
```c
void my_RX_ISR() {
    // Configure the timer for transmission  
    RX_LED_SetLow();
    TMR3_StartTimer();
    ...
}
void Timer3IntHandler(void){
    //Set timer 
    RX_LED_SetHigh();
    TMR3_StopTimer();
    TMR3_Reload();
}

```

Usage:   
Start Transmission to turn on the LED and start the timer.    
The LED will automatically turn off after the specified duration.    

### 2. Reception Timer

Purpose: Keeps the LED on for a specified duration during data reception.

```c
// Configure the timer ISR
TMR1_SetInterruptHandler(Timer1IntHandler);

//the timer ISR
void Timer1IntHandler(void){
    TX_LED_SetHigh();
    TMR1_StopTimer();
    TMR1_Reload();
}

```


### 3. Voltage Reading Timer
Purpose: Introduces a 150ms delay before the slave device starts reading the voltage.

```c
// Configure the timer ISR
TMR0_SetInterruptHandler(Timer0IntHandler);

//the Timer ISR
void Timer0IntHandler(void){
    timer0_flag = 1;
}

{
/*Execute frame CMD */
    /*~~READ command~~*/
      TMR0_StartTimer();          //Start the timer
      while(!timer0_flag);        //wait for timer to finish
      TMR0_StopTimer();           //Stop the timer
      timer0_flag = 0;            //reset the timer's flag
      TMR0_Reload();              //Reload the timer
```

### **Summary**
The three timers are configured to control LED states during transmission and reception, and to manage a delay for voltage reading.    
By calling the respective StartTimer() functions, the timers will handle the LED states and delay automatically.
