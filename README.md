# Getting started

## toolchain

Before starting compilation and build, update repositories and install the depencencies

```sh
git clone *https* or *SSH* *URL*
```

## Project configuration

Before starting the configuration, download MPLAB X IDE SOFTWARE.

Open existing project-> link to "FSM-communication"

## Building project

Click on 'Clean and build' Icon.

Open folder "FSM-communication" -> dist -> default -> production and make sure hex file named "FSM-communication.production.hex" is present.

## Running project

Download and Open Pickit 3 IDE software.

1. Connect the 6 connectors with the device.
2. Check if the probe is communicating succesfully
   PicKit 3 IDE -> Tools -> Check communication:   
         '*Green* for sucess.'
         '*Red* for fail.'
4. Send the code to the pic18 microcontroller
   Auto Import Hex + write device   
         link to: FSM-communication -> dist -> default -> production -> FSM-communication.production.hex
         '*Green* for sucess.'
         '*Red* for fail.'
   
Note: Make sure the Vdd icon is *UNCHECKED*

## Debug Project 

Use any graphical serial terminal that includes RS485

