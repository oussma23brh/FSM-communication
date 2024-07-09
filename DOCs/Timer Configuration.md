# Timer Configuration Documentation

This document outlines the configuration and usage of three different timers in our system.     

## Timer Overview

1. **Transmission Timer**   : Controls the duration for which the LED stays on during transmission.
2. **Reception Timer**      : Controls the duration for which the LED stays on during reception.
3. **Voltage Reading Timer**: Sets a 150ms delay for the slave device before it starts reading the voltage.

## Timer Details

### 1. Transmission Timer

Usage:   
Call startTransmission() to turn on the LED and start the timer.    
The LED will automatically turn off after the specified duration.    

### 2. Reception Timer

Purpose: Keeps the LED on for a specified duration during data reception.

### **Summary**
The three timers are configured to control LED states during transmission
and reception, and to manage a delay for voltage reading.    
By calling the respective start functions, the timers will handle the LED 
states and delay automatically.
