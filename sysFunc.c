/*
 * File:   sysFunc.c
 * Author: Faisal
 *
 * Created on June 16, 2017, 8:37 PM
 */


#include <xc.h>
#include "Keypad4x4.h"
#include "uart.h"
#include "sysFunc.h"
#include "led_control.h"

command_t recvCommand;
keypadState_t keypadState;
uint8_t currentKey, lastKey;

void gpioInit()
{
    ANSELH = 0x00;                  // Pins of the Matrix Keypad are configured as digital io's
    OPTION_REGbits.nRBPU = 0;       // Pull ups activated
    TRISCbits.TRISC5 = 0;           // Output to the RS485 Data direction control pin
    rs485Rx();
}

void clockInit()
{
    
}

void rs485Tx()
{
    PORTCbits.RC5 = 1;
}

void rs485Rx()
{
    PORTCbits.RC5 = 0;
}

/*****************************************************************************************************************
 *  Sorts the Received buffer data into the command format.
 *  
 * @param1 Buffer where data is received from the UART
 * @param2 Struct which will hold the command received and the associated parameters
 * 
 ****************************************************************************************************************/
err_t sortRxFrame(uint8_t *rxBuf, command_t *commandStruct)
{
    err_t err;
    command_t *command;
    command = rxBuf;
    if(command->startByte == STARTBYTE)
        if(command->panelId == PANELID)
            if(command->endByte == ENDBYTE)
            {
                commandStruct->commandType = command->commandType;
                commandStruct->param = command->param;
                err = ERR_OK;
                return err;
            }
            else { err = ERR_END; return err;}
        else { err = ERR_ID; return err;}
    else { err = ERR_STRT; return err;}  
}

void runProtocol(command_t *commandRecv)
{
    uint8_t command = commandRecv->commandType;
    switch(command){
        case SEND_BUTTON:
            sendButtonInfo(lastKey);
            commandRecv->commandType = COMMAND_NULL;
            break;
            
        case ACK_BUTTON:
            ackButton(commandRecv->param);
            commandRecv->commandType = COMMAND_NULL;
            break;
            
        case RESET_KEYPAD:
            resetKeypad();
            commandRecv->commandType = COMMAND_NULL;
            break;
            
        default:
            break;
    }
}

void sendButtonInfo(uint8_t button)
{
    uint8_t buffer[6];
    buffer[0] = STARTBYTE;
    buffer[1] = PANELID;
    buffer[2] = SEND_BUTTON;
    buffer[3] = 0x00;
    buffer[4] = button;
    buffer[5] = ENDBYTE;
    
    rs485Tx();
    USARTWriteString(buffer, sizeof(buffer));
    rs485Rx();
}

void ackButton(uint16_t valid_indicator)
{
    uint8_t buffer[6];
    
    buffer[0] = STARTBYTE;
    buffer[1] = PANELID;
    buffer[2] = ACK_BUTTON;
    buffer[3] = 0x00;
    buffer[4] = 0x00;
    buffer[5] = ENDBYTE;
    
    rs485Tx();
    USARTWriteString(buffer, 6);
    rs485Rx();
    
    keypadState.keyLock = 0;
    keypadState.keyPressIndicator = 0;
    keypadState.keyPressed = BUTTON_0;
    
    if(valid_indicator)
    {
        switch(lastKey)
        {
            case BUTTON_1:
                LED1 = ON;
                break;
                
            case BUTTON_2:
                LED2 = ON;
                break;
                
            case BUTTON_3:
                LED3 = ON;
                break;
                
            case BUTTON_4:
                LED4 = ON;
                break;
                
            case BUTTON_5:
                LED5 = ON;
                break;
                
            case BUTTON_6:
                LED6 = ON;
                break;
                
            case BUTTON_7:
                LED7 = ON;
                break;
                
            case BUTTON_8:
                LED8 = ON;
                break;
                
            case BUTTON_9:
                LED9 = ON;
                break;
                
            case BUTTON_10:
                LED10 = ON;
                break;
                
            case BUTTON_11:
                LED11 = ON;
                break;
                
            case BUTTON_12:
                LED12 = ON;
                break;
                
            case BUTTON_13:
                LED13 = ON;
                break;
                
            case BUTTON_14:
                LED14 = ON;
                break;
                
            case BUTTON_15:
                LED15 = ON;
                break;
                
            case BUTTON_16:
                LED16 = ON;
                break;
        }
    }
    
    lastKey = BUTTON_0;

}

void resetKeypad()
{
    uint8_t buffer[6];
    
    buffer[0] = STARTBYTE;
    buffer[1] = PANELID;
    buffer[2] = RESET_KEYPAD;
    buffer[3] = 0x00;
    buffer[4] = 0x00;
    buffer[5] = ENDBYTE;
    
    rs485Tx();
    USARTWriteString(buffer, 6);
    rs485Rx();
    
    keypadState.keyLock = 0;
    keypadState.keyPressIndicator = 0;
    keypadState.keyPressed = BUTTON_0;
    lastKey = BUTTON_0;
    
    LED_ON = OFF;
}

void controllerInit(void) 
{
    gpioInit();
    USARTInit(9600);
    initKeypad();
    
    return;
}

uint8_t scanKeypad()
{
    if(!keypadState.keyPressIndicator && !keypadState.keyLock)
    {
        getKey(&keypadState);
        
        if(keypadState.keyPressIndicator)
        {
            lastKey = keypadState.keyPressed;
            keypadState.keyLock = 1;
            return 0;
        }
    }
    return 1;
}

void checkCommandRx()
{
    uint8_t buffer[6];
    
    if(rxCount >= (RECEIVE_BUFF_SIZE / 2))
    {
        USARTReadBuffer(buffer, sizeof(buffer));
        rxCount -= (RECEIVE_BUFF_SIZE / 2);
        sortRxFrame(buffer, &recvCommand);
        runProtocol(&recvCommand);
    }
}
