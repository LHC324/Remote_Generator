/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F25K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc.h"
#include "multi_timer.h"
#include "Event.h"
#include "eusart1.h"

Timer Status_Handle;
Timer MotorStop_Handle;
Timer VoltageCheck_Handle;
Timer Report_Handle;
Timer Led_Handle;
Timer Uart1Rec_Handle;
Timer Uart2Rec_Handle;

Timers Timer_Grounps[] = 
{
    {&Status_Handle, Status_Check, 0U, 20U},
//    {&MotorStop_Handle, Gen_Stop, 5U, 500U},
    {&VoltageCheck_Handle, Voltage_Check, 10U, 50U},
    {&Report_Handle, Timing_Report, 15U, 1000U},
    {&Led_Handle, Run_Stutas, 20U, 100U},
    {&Uart1Rec_Handle, Uart1_Handle, 25U, 20U},
    {&Uart2Rec_Handle, Uart2_Handle, 30U, 10U}
};

void Timers_Init(void)
{
    for(uint8_t i = 0; i < (sizeof(Timer_Grounps) / sizeof(Timers)); i++)
    {   /*Initialize timed task chain*/
        timer_init(Timer_Grounps[i].Timer_handle, Timer_Grounps[i].Timer_CallBack, Timer_Grounps[i].Delay_StartTimes, Timer_Grounps[i].RepeatTimes, Timer_Grounps[i].Timer_handle); 
        timer_start(Timer_Grounps[i].Timer_handle);
    }
}


/*
                         Main application
 */
void main(void)
{  
//    uint8_t rxData = 0;
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
//    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    /*Task timer initialization*/
    Timers_Init();
    /*Hit the watchdog*/
    SWDTEN = 1;    
    
    while (1)
    {
        // Add your application code
//         LATCbits.LATC0 ^= 1;
//        __delay_ms(2000);
        
        /*Polling timer task*/
        timer_loop();
//        Uart1_Send("hello world\r\n", strlen("hello world\r\n"));
//        __delay_ms(500);
//        Uart1_Handle(NULL);
//        if(EUSART1_is_rx_ready())
//            {
//                rxData = EUSART1_Read();
//                if(EUSART1_is_tx_ready())
//                {
//                    EUSART1_Write(rxData);
//                }
//            }
        CLRWDT();
    }
}
/**
 End of File
*/