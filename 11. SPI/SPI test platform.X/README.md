# SPI test platform

![image](https://user-images.githubusercontent.com/44589560/145692659-5d53711a-0d69-42cf-bb63-2c2c45f7d0ed.png)

![image](https://user-images.githubusercontent.com/44589560/145696218-5606cc57-d12e-45b2-8a68-09da8af13ca1.png)

![image](https://user-images.githubusercontent.com/44589560/145695939-8f5df443-2cb4-47b7-811b-c83e879c6a4b.png)

What you use MCC spi files are generated:
```
void SPI1_Initialize(void);
bool SPI1_Open(spi1_modes_t spi1UniqueConfiguration);
void SPI1_Close(void);
uint8_t SPI1_ExchangeByte(uint8_t data);
void SPI1_ExchangeBlock(void *block, size_t blockSize);
void SPI1_WriteBlock(void *block, size_t blockSize);
void SPI1_ReadBlock(void *block, size_t blockSize);
void SPI1_WriteByte(uint8_t byte);
uint8_t SPI1_ReadByte(void);
```
