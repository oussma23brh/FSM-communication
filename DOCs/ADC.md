# Getting Started

This documentation provides an overview of the ADC configuration and usage. It includes initialization, channel configuration, and reading data from the ADC.

## ADC Configuration

### Initialize the ADC

The initialization of the ADC involves resetting the device, configuring the channels, and setting the reference voltage.

#### Function: `void AD5593_init_w_VREF(void)`

This function initializes the ADC with the specified reference voltage.

**Steps included:**

1. **Reset the ADC**: Ensure the ADC is in a known state.
2. **Set Vref and ADC Max Value**: Choose between external or internal reference voltage.
3. **Disable ADC buffer**: Disable ADC buffer 
4. **Configure the Channels**: Set up the ADC channels using `ADC_ch_config()`.

#### Example Code

```c
void AD5593_init_w_VREF(void)
{
    // Reset the ADC
    AD5593_reset();

   //Set the reference voltage and maximum ADC value
   set_VREF(false);    
   set_ADC_range(_VREF);     

   //Disable ADC buffer
   set_ADC_BUFF(false);        

   // Configure the channels
   ADC_ch_config();
}
```
### Request a Read from the ADC
To request a read from the ADC, follow these steps: lock the buffer, trigger the conversion, unlock the buffer, and retrieve the conversion results.

#### Function: `void AD5593_ADC_read(void)`    
This function performs an ADC read operation, including locking and unlocking the internal registers, triggering the conversion, and obtaining the result.

```c
void AD5593_ADC_read(void) {
    lock_config_reg(true);      // Lock the internal registers
    __delay_us(5);
    
    AD5593_ADC_convert(0);      // Trigger conversion of channel 0
    __delay_us(5);              // Wait for conversion to end
    
    lock_config_reg(false);     // Unlock the internal registers
    AD5593_get_conv_result(0);  // Get conversion result of channel 0
}
```

### Breakdown of the Function Example of channel 0
1. **Lock the Buffer** :     
`lock_config_reg(true);`

This ensures the internal registers are locked during configuration.

2. **Trigger Conversion** :   
`AD5593_ADC_convert(0);   
__delay_us(5);   
`
Initiates the conversion for channel 0 and waits for it to complete.   

3. **Unlock the Buffer** :    
`lock_config_reg(false);`

Unlocks the internal registers after the conversion is done.

4. **Get Conversion Result** :
`AD5593_get_conv_result(0);`

Retrieves the conversion result for channel 0.

### Summary
This documentation provides a concise guide to initializing the ADC and requesting a read from it.     
The functions AD5593_init_w_VREF() and AD5593_ADC_read() encapsulate the necessary steps for these operations.    


