#include "mcc_generated_files/mcc.h"

void main(void)
{
    SYSTEM_Initialize();

    while (1)
    {
        // Add your application code
        int x = knap_GetValue();       
        
        if(knap_GetValue == 1)
        {
            // ... Do something
        }
    }
}