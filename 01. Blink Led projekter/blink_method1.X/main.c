#include <pic18.h>
#include "mcc_generated_files/mcc.h"
#include <xc.h>


void main(void)
{
    SYSTEM_Initialize();

    while (1)
    {
        led1_SetHigh();
        __delay_ms(1000);
        led1_SetLow();
        __delay_ms(1000);
    }
}
/**
 End of File
*/