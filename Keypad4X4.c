#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif 
#include <xc.h>
#include <htc.h>
#include "Keypad4x4.h"

enum button buttonPressed;

keypadState_t currentKeypadStatus;        // define a structure to return the state of keypad of structure type keypadStatus

/**************************************************************************************/
/*          Function to Initialize the controller port to which the 4X4 keypad is connected
 *          Rows are set as outputs and columns as inputs           
            Arguments Taken: None
            Returns:    None
 */
void initKeypad(void)
{
	KEYPAD_PORT_DIR = 0xF0;	// Last 4 pins (Column) input, First 4 pins (Rows) output
    KEYPAD_PORT = 0xFF;     // Initial value to wake up controller on Pin-change at the column inputs.
}

/**************************************************************************************/
/*          Function to check key pressed           
            Arguments Taken: None
            Returns:    Key pressed indicator bit   member of structure keypadStatus
                        Key pressed value           member of structure keypadStatus
 */
void getKey(keypadState_t *keypadState)                
{	
/****   Make ROW 2 LOW and check for columns 1,2,3,4    *****/    
    PORTB = 0xFE;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_1;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_2;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_3;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_4;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
/****   Make ROW 2 LOW and check for columns 1,2,3,4    *****/
    PORTB = 0xFD;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_5;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_6;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_7;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_8;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
/****   Make ROW 3 LOW and check for columns 1,2,3,4    *****/
    PORTB = 0xFB;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_9;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return; 
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_10;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_11;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_12;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
/****   Make ROW 4 LOW and check for columns 1,2,3,4    *****/
    PORTB = 0xF7;
    if ((PORTB & 0x10) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_13;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x20) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_14;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x40) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_15;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else if ((PORTB & 0x80) == 0x00)
    { 
        __delay_ms(100);
        buttonPressed = BUTTON_16;
        keypadState->keyPressIndicator = True;
        keypadState->keyPressed = buttonPressed;
        return;
    }
    
    else {
            keypadState->keyPressIndicator = False;
            keypadState->keyPressed = BUTTON_0;
            return;
    }
    
}

//char buttonPressedIndicator()
//{
//    getKey();
//    if(currentKeypadStatus.keyPressIndicator == True)
//        return 1;
//    else return 0;
//}
