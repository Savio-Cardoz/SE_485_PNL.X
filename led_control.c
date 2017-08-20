/*
 * File:   led_control.c
 * Author: Cardoz
 *
 * Created on August 20, 2017, 6:38 PM
 */


#include <xc.h>
#include "led_control.h"

void init_controller_led_pins()
{
    TRISA &= 0xE0;              // Pins RA0 - RA4 set as output to the de-multiplexer.
    
}

void light_led(uint16_t led_register, uint8_t LED_EN)
{
    uint8_t i;
    if(LED_EN && led_register)              // switch on the DEMUX only if any of the LEDS are meant to be ON (w.r.t. led_register)
    {
        DEMUX_EN = ON;
        for(i = 0; i < NO_OF_LEDS; i++)
        {
            if(led_register & 0x0001)       // If the LSB is SET the respective iteration number of i is pushed to the de-multiplexer
            {   
                DEMUX_PORT = i;
            }

            led_register >> 1;
        }
    }
}