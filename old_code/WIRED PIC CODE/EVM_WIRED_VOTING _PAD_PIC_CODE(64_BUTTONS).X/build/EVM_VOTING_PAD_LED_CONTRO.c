/*
 * File:   VOTING_PAD_LED.c
 * Author: PC 7
 *
 * Created on February 18, 2015, 1:14 PM
 * UPDATED on April 23, 2015, 4:22 PM FOR 16 BUTTONS
 * UPDATED ON 20/06/2015 FOR 32 BUTTONS
 * UPDATED ON 22/07/2015 FOR 64 BUTTONS
 *  Note : Do Not write lot off code in ISR
 */

#include <stdio.h>
#include <pic16f882.h>
#include <GenericTypeDefs.h>

// PIC16F882 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

/***************************************** FUNCTIONS ****************************************/
VOID i2c_data_receive();
VOID i2c_init();
VOID Init_Interrupt() ;
VOID Port_init();
VOID delay(unsigned int li);
/*********************************************************************************************/

/**************************************** VARIABLES ******************************************/
unsigned char i2c_data;
bit keypad1=0,keypad2=0,flag=0;
unsigned char *val1,*val2,*val3,*val4,i,j,k,l,m,store1[16]={0},store2[16]={0},store3[16]={0},store4[16]={0};
unsigned char val_rx,Count1=0,Count2=0,Count3=0,Count4=0,temp1=32,temp2=32,temp3=32,temp4=32;
/**********************************************************************************************/

/*//////////////////////////////////////////// CODE ///////////////////////////////////////////*/
VOID interrupt low_isr(VOID)                            //ISR ROUTINE
{
    if(SSPIF==1)                                        // ROUTINE FOR I2C_INTERRUPT
    {
      i2c_data=SSPBUF;                                  // TAKE BUFFER DATA INTO VARIABLE
      if(i2c_data==0)                                   //IF CLEAR COMMAND RECEVIED SET FLAG BIT
      {
          flag=1;
      }
      i2c_data_receive();                               // FOR ANY DATA OTHER THAN CLEAR COMMAND
      SSPIF=0;                                          //CLEAR I2C  INTERRUPT FLAG
    }
}

VOID i2c_init()
{
    TRISCbits.TRISC3=1;  //set SCL as i/p
    SMP=0;               //Sample bit
    SSPEN=1;             //Enable i2c_module
    CKP=1;               //Sets Idle Clock Polarity As High
    SSPM0=0;             //set into slave mode
    SSPM1=1;             //set into slave mode
    SSPM2=1;             //set into slave mode
    SSPM3=0;             //set into slave mode
    GCEN=1;              //Genral check enable
    SSPADD=0x80;         //address of slave
}

VOID Init_Interrupt()             //////Interrupt INITIALISATION///////////
{
     PEIE=1;     //Peripheral interrupts enble bit
     GIE=1;      ///Global interrupt enble bit
     SSPIE=1;    // Enables Spi Interrupt

}

VOID i2c_data_receive()            ///store data send bye atmega 32 into array
{
    if((i2c_data!=0)&&(i2c_data!=0x80))
      {

      if((i2c_data>0)&&(i2c_data<17))         //1ST KEYPAD(1 TO 16 BUTTONS)
        {

            temp1=0;                            //default value
            store1[Count1]=i2c_data-1;          //masking of received data suitable to blink led (as CD4067 starts from 0 and ends on 15 )
            temp1=Count1;                       //to load only stored data location
            i2c_data=0;                         //clear received data variable
            Count1++;                           //increment Count to save next button data
        }

      if((i2c_data>16)&&(i2c_data<33))          //2ND KEYPAD(17 TO 32 BUTTONS)
        {
            temp2=0;                            //default value
            store2[Count2]=i2c_data-17;         //masking of received data suitable to blink led (as CD4067 starts from 0 and ends on 15 )
            temp2=Count2;                       //to load only stored data location
            i2c_data=0;                         //clear received data variable
            Count2++;                           //increment Count to save next button data
        }
      if((i2c_data>32)&&(i2c_data<49))          //3RD KEYPAD(33 TO 48BUTTONS)
        {
            temp3=0;                            //default value
            store3[Count3]=i2c_data-33;         //masking of received data suitable to blink led (as CD4067 starts from 0 and ends on 15 )
            temp3=Count3;                       //to load only stored data location
            i2c_data=0;                         //clear received data variable
            Count3++;                           //increment Count to save next button data
        }

      if((i2c_data>48)&&(i2c_data<65))          //4TH KEYPAD(49 TO 64 BUTTONS)
        {
            temp4=0;                            //default value
            store4[Count4]=i2c_data-49;         //masking of received data suitable to blink led (as CD4067 starts from 0 and ends on 15 )
            temp4=Count4;                       //to load only stored data location
            i2c_data=0;                         //clear received data variable
            Count4++;                           //increment Count to save next button data
        }

      }


}
VOID Port_init()
{
    ANSEL = 0x00;                   // Make all pins of portA as Digital pins.
    ANSELH = 0x00;                  // Make all pins of portB as Digital pins.
    OPTION_REG=0x00;                //to turn on weak pull-ups of portb make RBPU as zero
    WPUB=0x0F;                      //to turn on weak pull-ups of portb
     TRISA=0xf0;                    //sets portA<4:7> as o/p
     TRISB=0x00;                    //sets portB<0:7> as o/p
     PORTA=0x00;                    //make portA  zero
     PORTB=0xFF;                    //make portB  zero

}
void delay(unsigned int li)         //////delay rotine
  {
    unsigned int k,j;
	 for(k=0;k<=li;k++)
	 {
	   for(j=0;j<=1;j++);
	 }
  }

VOID main()
{
    Port_init();                                                    //PORT INTIALISATION
    i2c_init();                                                     //I2C INTIALISATION
    Init_Interrupt();                                               //INTERRUPT INTIALISATION
    val1= &store1[0];                                               //LOAD FIRST POSTION ADRESS
    val2= &store2[0];                                               //LOAD FIRST POSTION ADRESS
    val3= &store3[0];                                               //LOAD FIRST POSTION ADRESS
    val4= &store4[0];                                               //LOAD FIRST POSTION ADRESS
  while(1)
       {
       if(flag==1)                                                  //IF CLEAR COMMAND RECIVED FROM MASTER CONTROLLER ATMEGA32/ ANY OTER CONTROOLER IF USED
          {
            PORTB=0xFF;                                             //DISABLE ALL DEMULTIPLEXER
            val1= &store1[0];                                       //LOAD FIRST POSTION ADRESS
            val2= &store2[0];                                       //LOAD FIRST POSTION ADRESS
            val3= &store3[0];                                       //LOAD FIRST POSTION ADRESS
            val4= &store4[0];                                       //LOAD FIRST POSTION ADRESS
              temp1=32;                                             //LOAD DEFAULT VALUE
              temp2=32;                                             //LOAD DEFAULT VALUE
              temp3=32;                                             //LOAD DEFAULT VALUE
              temp4=32;                                             //LOAD DEFAULT VALUE
                for(k=0;k<=16;k++)                                  //FOR CLEARING ALL DATA STORED
                  {
                    store1[k]=0;
                    store2[k]=0;
                    store3[k]=0;
                    store4[k]=0;
                  }
                Count1=0;                                             //LOAD DEFAULT VALUE
                Count2=0;                                             //LOAD DEFAULT VALUE
                Count3=0;                                             //LOAD DEFAULT VALUE
                Count4=0;                                             //LOAD DEFAULT VALUE
                flag=0;                                               //CLEAR FALG
           }
        if((temp1<16)&&((Count1>0)&&(Count1<18)))                  // first voting pads  16 buttons
          {
             PORTB=0xFF;                                          //Turn of multiplexer at start
            for(i=0;i<=temp1;i++)                                 //To load only stored value increment i upto temp1
             {

                 PORTA=*(val1);                                    //Transfer data from array  to portA using pointer *val1
                PORTBbits.RB0=0;                                   //Turn on multiplexer
                 delay(1);                                         //min delay between on and off of encoder
                 val1++;                                           //increment pointer to blink next button led
                 PORTB=0xFF;                                       //Turn off multiplexer
                 if(val1>&store1[temp1])                           // in case pointer value becomes greater than address of array make it zero
                 {
                     val1= &store1[0];
                 }
             }
          }
        if((temp2<16)&&((Count2>0)&&(Count2<18)))                  // Second voting pads  16 buttons
          {
            PORTB=0xFF;                                             //Turn of multiplexer at start
            for(j=0;j<=temp2;j++)                                   //To load only stored value increment J upto temp2
             {
                 PORTA=*(val2);                                     //Transfer data from array  to portA using pointer *val2
                 PORTBbits.RB1=0;                                   //Turn on multiplexer
                 delay(1);                                          //min delay between on and off of encoder
                 val2++;                                            //increment pointer to blink next button led
                 PORTB=0xFF;                                        //Turn off multiplexer
                 if(val2>&store2[temp2])                            // in case pointer value becomes greater than address of array make it zero
                 {
                    val2= &store2[0];
                 }
             }
          }
        if((temp3<16)&&((Count3>0)&&(Count3<18)))                   // Third voting pads  16 buttons
          {
             PORTB=0xFF;                                            //Turn of multiplexer at start
            for(l=0;l<=temp3;l++)                                   //To load only stored value increment L upto temp3
             {

                 PORTA=*(val3);                                     //Transfer data from array  to portA using pointer *val3
                 PORTBbits.RB2=0;                                   //Turn on multiplexer
                 delay(1);                                          //min delay between on and off of encoder
                 val3++;                                            //increment pointer to blink next button led
                 PORTB=0xFF;                                        //Turn off multiplexer
                 if(val3>&store3[temp3])                            // in case pointer value becomes greater than address of array make it zero
                 {
                     val3= &store3[0];
                 }
             }
          }
        if((temp4<16)&&((Count4>0)&&(Count4<18)))                   // Forth voting pads  16 buttons
          {
            PORTB=0xFF;                                             //Turn of multiplexer at start
            for(m=0;m<=temp4;m++)                                   //To load only stored value increment M upto temp4
             {
                 PORTA=*(val4);                                     //Transfer data from array  to portA using pointer *val4
                  PORTBbits.RB3=0;                                  //Turn on multiplexer
                 delay(1);                                          //min delay between on and off of encoder
                 val4++;                                            //increment pointer to blink next button led
                 PORTB=0xFF;                                        //Turn off multiplexer
                 if(val4>&store4[temp4])                            // in case pointer value becomes greater than address of array make it zero
                 {
                    val4= &store4[0];
                 }
             }
          }
        PORTB=0xFF;                                                 //Turn off multiplexer
        }
}
