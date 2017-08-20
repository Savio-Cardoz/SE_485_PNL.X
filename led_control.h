/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LED_CONTROL_H
#define	LED_CONTROL_H

#include <xc.h>

#include "sysFunc.h" // include processor files - each processor file is guarded.  

typedef struct			// Using to access individual bits/pins of a register/port
{
	uint16_t bit0:1;
	uint16_t bit1:1;
	uint16_t bit2:1;
	uint16_t bit3:1;
	uint16_t bit4:1;
	uint16_t bit5:1;
	uint16_t bit6:1;
	uint16_t bit7:1;
    uint16_t bit8:1;
    uint16_t bit9:1;
    uint16_t bit10:1;
    uint16_t bit11:1;
    uint16_t bit12:1;
    uint16_t bit13:1;
    uint16_t bit14:1;
    uint16_t bit15:1;
} _io16_reg;

#define REGISTER_16BIT(rg,bt) ((volatile _io16_reg*)&rg)->bit##bt

volatile uint16_t led_indication_reg;

#define LED1 REGISTER_16BIT(led_indication_reg, 0)
#define LED2 REGISTER_16BIT(led_indication_reg, 1)
#define LED3 REGISTER_16BIT(led_indication_reg, 2)
#define LED4 REGISTER_16BIT(led_indication_reg, 3)
#define LED5 REGISTER_16BIT(led_indication_reg, 4)
#define LED6 REGISTER_16BIT(led_indication_reg, 5)
#define LED7 REGISTER_16BIT(led_indication_reg, 6)
#define LED8 REGISTER_16BIT(led_indication_reg, 7)
#define LED9 REGISTER_16BIT(led_indication_reg, 8)
#define LED10 REGISTER_16BIT(led_indication_reg, 9)
#define LED11 REGISTER_16BIT(led_indication_reg, 10)
#define LED12 REGISTER_16BIT(led_indication_reg, 11)
#define LED13 REGISTER_16BIT(led_indication_reg, 12)
#define LED14 REGISTER_16BIT(led_indication_reg, 13)
#define LED15 REGISTER_16BIT(led_indication_reg, 14)
#define LED16 REGISTER_16BIT(led_indication_reg, 15)

#define DEMUX_EN REGISTER_BIT(PORTA, 4)

#define NO_OF_LEDS 16
#define DEMUX_PORT PORTA

void init_controller_led_pins();
void light_led(uint16_t led_register, uint8_t LED_EN);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

