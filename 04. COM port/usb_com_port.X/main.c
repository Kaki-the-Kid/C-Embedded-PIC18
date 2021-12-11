#include "mcc_generated_files/mcc.h"

void main(void)
{
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    EUSART1_Initialize();
              
    while (1)
    {
        EUSART1_is_rx_ready();
        char tmp = EUSART1_Read();
    }
}