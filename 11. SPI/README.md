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

```
/*Initialise SSP in SPI mode */ 
void init_SSPl(void) 
{
  IODIR0 = IODIR0IPIN_S5Pl_SS; //Enable SSEL pin as GPIO
  PINSEL0 I= 0x000A8000; //Enable SSPl pins wih SSEL as GPIO
  //PINSEL0 I= 0x000AA000; //Enable SSPl pins wiht SSEL as SS 

  /* Set DSS data to 8-bit, Frame format SPI, CPOL - 0, CPHA - 0, and SCR 
     (serial clock Rate (presscaler) is 15 */
     
  SSP1CR0 = 0xFF07;
  SSPlCRl = 0x00000002; //Configure as SPI Master
  
  /* SSPCPSR clock prescale register, master mode, minimum divisor 
     is 0x02 MAX 254 */
  
  SSPlCPSR = 15;
} 


/*Send data to the SSP the start address and number of bytes (size of 
array) must be given*/
void SSPlSendData(unsigned char *data_add,unsigned char arr_size) 
{
  int i; 
  SSP1_SS(0); //Select slave active low
  
  for(i=0;i<arr_size;i++)
  {
    while ( (SSPlSR & SSPSR_BSY) ); // Wait until the Busy bit is cleared
    
    SSPlDR = *data_add;
    while ((SSPlSR & SSPSR_BSY) ); // Wait until the Busy bit is cleared
    
    data_ add++;
  }
  
  SSPl_SS(l); //de-select slave
} 
 

/*Receive data to the SSP the start address of where the data should be 
stored, size of the data must be given */
void SSPlReceiveData(unsigned char *data_add,unsigned char arr_size) 
{
  int i;
  
  SSP1_SS(0);
  
  for(i=0; i<arr_size; i++) 
  {
    SSPlDR = 0x00; //dummy write
    while ( (SSPlSR & SSPSR_BSY) ); // Wait until the Busy bit is cleared
    
    *data_add= SSPlDR; 
    while ( (SSPlSR & SSPSR_BSY) ); // Wait until the Busy bit is cleared
    
    data_add++; 
  }
  
  SSPl_SS(l); 
} 


## Example SPI devices 
* 25LC020A - 2K SPI Bus Serial EE PROM 
* TC77-5.0 - Thermal Sensor with SPI Interface 
* MCP3201 - 2.7V 12-Bit AID Converter with SPI Serial Interface 
* MCP4822 - 12-Bit DAC with Internal VREF and SPI Interface 
* MCP41010 - Single/Dual Digital Potentiometer with SPI Interface 
* MCP6S92 - Single-Ended, Rail-to-Rail 1/0, Low-Gain PGA 
* MCP23S08 - 8-Bit 1/0 Expander with Serial Interface 
* The PICkit™ Serial SPI Demo Board was designed to easily 
