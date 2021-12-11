#include "mcc_generated_files/mcc.h"
void toggleLED(void);

void main(void)
{
    SYSTEM_Initialize();

    while (1)
    {
        if (1 == PORTAbits.RA1) 
        {
            led1_Toggle();
            __delay_ms(500);
        }    
    }
}

void toggleLED(void) {
    led1_Toggle();
}