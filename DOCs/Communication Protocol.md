# Communication Protocol Documentation

This document outlines the structure and components of our custom communication protocol.

## Frame Structure

Each communication frame follows a specific structure designed for clarity and error checking. The frame format is as follows:

### Sent frames

`$xAACrr*`     

### Breakdown of Frame Components

1. **`$` (Starting Character)**: 
    - The frame begins with the `$` character to indicate the start of a new message.

2. **`x` (Communication Type)**:
    - **`U`**: Unicast - Communication directed to a single recipient.
    - **`B`**: Broadcast - Communication sent to all recipients.

3. **`AA` (Slave Address)**:
    - This is a two-digit decimal value representing the address of the slave device.

4. **`C` (Command Type)**:
    - **`R`**: Require reading data from the slave.
    - **`G`**: Get the data that has been read.
    - **`C`**: Broadcast check to confirm communication.

5. **`rr` (CRC08 Value)**:
    - A calculated 8-bit CRC (Cyclic Redundancy Check) value used for error checking. This ensures data integrity.

6. **`*` (Ending Character)**:
    - The frame ends with the `*` character to indicate the end of the message.

## Error Checking

All frames include a `CRC08` value for error checking to maintain data integrity.    

The communication is considered complete when the frame ends with the `*` character.   

### Examples

- **`$BR34*`**: Broadcast to all slaves to read at the same time.
- **`$U01G37*`**: Send stored data in slave with address 01.
- **`$U01C30*`**: Check if broadcast frame was successfully sent to slave with address 01.

## Acknowledgment Frames

### READ Acknowledgment Frame Structure   

`$xAAROKrr*`       

- **`$xAAR`**: The previously sent frame.
- **`OK`**: When the frame executes successfully.
- **`rr`**: Calculated CRC08 value.
- **`*`**: Ending character.

#### Example

- **`$U01ROK26*`**: Acknowledgment indicating the successful operation of the previously sent frame `$U01R22*`.
- **`$U16ROK20*`**: Acknowledgment indicating the successful operation of the previously sent frame `$U16R24*`.

Frames arriving with a CRC error are automatically discarded.

### GET Acknowledgment Frame Structure

`$xAAG1111222233334444rr*`   

- **`$xAAG`**: The previously sent frame.
- **`1111`**: Data read from input 1.
- **`2222`**: Data read from input 2.
- **`3333`**: Data read from input 3.
- **`4444`**: Data read from input 4.
- **`rr`**: Calculated CRC08 value.
- **`*`**: Ending character.

#### Example

- **`$U01G0aea08a105a06d30F*`**: Acknowledgment of a GET frame in response to the previously sent frame `$U01G37*`.
  - Sends to the master the data acquired from the 4 different inputs successively.
  - The data is in hexadecimal but the `0x` is omitted in the message.
  - `0F` is the calculated CRC code of `$U01G0aea08a105a06d3`.

### Broadcast Check Acknowledgment Frame Structure    

`$UAACSSrr*`    

- **`$UAAC`**: The previously sent frame.
- **`SS`**: Response to the broadcast check.
  - **`YS`**: YES - Indicates a successful broadcast to the probe with address `AA`.
  - **`NO`**: NO - Indicates an unsuccessful broadcast to the probe with address `AA`.
