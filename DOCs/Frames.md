# Getting started

## Frame Structure

### Sent frames

`$xAACrr*`     

`$`  : Starting character.   
`x`  : Communication type , `U`: for Unicast , `B`: for broadcast.    
`AA` : Slave address -in decimal-.   
`C`  : Command type, `R` to require reading data, `G` to get the data read data, `C` for broadcast check.
`rr` : Calculated CRC08 value.
`*`  :  Ending character.

Please note that all frames end with the `CRC08` for the error checking and the usual "*".   

Examples:    

`$BR34*`    : Broadcast to all slaves to read at the same time.    
`$U01G37*`  : Send stored data in slave with address 01.    
`$U01C30*`  : check if broadcast frame was successfully sent to slave with address 01.    

### Acknowledgment frames

*READ acknowledgment frame structure*

`$xAACOKrr*`       

`$xAAC`  : The previously sent frame.    
`OK`     : When the frame executes successfully.     
`rr`     : Calculated CRC08 value.   
`*`      :  Ending character.   

Example:    
`$U01ROK26*`  : Ack indicating the successful operation of the previously send frame `$U01R22*`.    
`$U16ROK20*`  : Ack indicating the successful operation of the previously send frame `$U16R24*`.      

Frames arriving with a CRC error are automatically discarded   

*GET acknowledgment frame structure*

`$xAAC1111222233334444rr*`   

`$xAAC`  : The previously sent frame.        
`1111`   : Data read from input 1.   
`2222`   : Data read from input 2.   
`3333`   : Data read from input 3.   
`4444`   : Data read from input 4.    
`rr`     : Calculated CRC08 value.    
`*`      : Ending character.



