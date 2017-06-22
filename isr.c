#include <stdint.h>
#include <xc.h>
#include "sysFunc.h"
#include "uart.h"

void interrupt ISR(void)
{
    if (PIR1bits.RCIF) 
    {
        rxCount++;
        USARTHandleRxInt();
        PIR1bits.RCIF = 0;
        return;
    }
}