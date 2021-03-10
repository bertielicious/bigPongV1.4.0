
#include "config.h"
#include "arrays.h"
#include "sendSPIbyte.h"
#include "sendNoSPIbyte.h"
//void _interrupt isr(void)
__interrupt() void MY_ISR(void)
{
    uchar col;
    uchar row;
    if(INTCONbits.TMR0IF == HI)
    {
        col = 0; // clear col 0 of LED matrix display
        for(row = 0; row < 8; row++)
        {
            if(col<8)
            {
                CS = LO;
                sendNoSPIbyte();
                sendSPIbyte(col+1, 0x00);
                CS = HI;
            }
    
        else
            {
                CS = LO;
                sendSPIbyte(col-7, 0x00);
                sendNoSPIbyte();
                CS = HI;
            }
                    
        }
        DIAGNOSTIC_GREEN_LED = ~DIAGNOSTIC_GREEN_LED;
        INTCONbits.TMR0IF = 0;
    }
}