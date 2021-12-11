# SPI signals 
## The SPI bus specifies four logic signals. 
* SCLK - Serial Clock (output from master) 
*  MOSI - Master Output, Slave Input (output from master) 
*  MISO - Master Input, Slave Output (output from slave) 
* SS - Slave Select (active low; output from master) 

<b>Alternative naming conventions</b> 
* SCK, CLK - Serial Clock (output from master) 
*  SDI, DI, SI - Serial Data In 
* SDO, DO, SO - Serial Data Out 
* SSEL - Slave Select

![image](https://user-images.githubusercontent.com/44589560/145690779-8f8c1b7b-92e1-4e45-8843-474a383ed473.png)

1. The master pulls the slave select low and then issues clock cycles. 
2. The clock frequency is not specified in the SPI protocol and can be anything from 0 up to 70MHz depending on the characteristics of the slave device. 
3. The data transfer then takes place. 
4. The master then de-selects the slave.

## Basic serial data transfer

![image](https://user-images.githubusercontent.com/44589560/145690830-2380f27e-f524-4100-afb2-6b9cb356e48a.png)

The registers within the master and slave act like shift registers shifting one bit on every cycle of the SCLK.

## Data transfer details 
* Most SPI interfaces have two configuration bits, called clock polarity (CPOL) and clock phase (CPHA). 
* CPOL determines whether the shift clock's idle state is low (CPOL=O) or high (CPOL=1 ) . 
* CPHA determines on which clock edges data is shifted in and out (for CPHA=O, MOSI data is shifted out on falling edge, M ISO data is shifted in on rising edge). 
* As each bit has two states, this allows for four different combinations, all of which are incompatible with each other. 
* For two SPI devices to talk to each other, they need to be set to use the same clock polarity and phase settings.

## SPI Data Transfer Modes
* These four modes are the combinations of CPOL and CPHA. 
* Modes 0 and 3 are the most common. 
* With SPI modes 0 and 3, data is always latched in on the rising edge of SCK and always output on the falling edge of SCK.

![image](https://user-images.githubusercontent.com/44589560/145690981-e0ee697f-b1ba-4172-87b2-9ab7cab98110.png)

## Multiple Slaves
 If multiple slave devices exist, the master normally generates a separate slave select signal for each slave. - Star connection. 

![image](https://user-images.githubusercontent.com/44589560/145691012-0e2cc3db-6883-4d8d-866c-3320fa354c84.png)

## SPI Bus characteristics 
* It is up to the master and slave devices to know whether a received byte is meaningful or not. 
* So a device must discard the received byte in a ''transmit only'' frame or generate a dummy byte for a ''receive only'' frame. 
* No Acknowledgement 
* Master doesn't even know if slave is present! 
* Slaves can be thought of as 10 devices of the master.

