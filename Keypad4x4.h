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
#ifndef __KEYPAD4X4_H
#define __KEYPAD4X4_H



#include <xc.h> // include processor files - each processor file is guarded.  

#define KEYPAD_PORT PORTB
#define KEYPAD_PORT_DIR TRISB
#define ROW_1 RB3
#define ROW_2 RB2
#define ROW_3 RB1
#define ROW_4 RB0
#define COL_1 RB4
#define COL_2 RB5
#define COL_3 RB6
#define COL_4 RB7

#define keyLocked 1
#define keyUnlocked 0
#define True 1
#define False 0

enum button {   BUTTON_0 = 0,
                BUTTON_1,
                BUTTON_2,
                BUTTON_3,
                BUTTON_4,
                BUTTON_5,
                BUTTON_6,
                BUTTON_7,
                BUTTON_8,
                BUTTON_9,
                BUTTON_10,
                BUTTON_11,
                BUTTON_12,
                BUTTON_13,
                BUTTON_14,
                BUTTON_15,
                BUTTON_16,
            };

typedef struct {
    char keyPressIndicator:1;  // Indicates if a key was pressed
    char keyPressSound:1;      // Flag for audible key press indication
    char keyLock:1;           // keypad locked/unlocked status indicator. 1 locked, 0 unlocked
    char keyPressed;        // Holds the value of the key pressed        
}keypadState_t;

void initKeypad(void);
void ackKeyPress();
void getKey(keypadState_t *keypadState);
char buttonPressedIndicator();
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */



#endif  /* KEYPAD4X4_H */

