/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F25K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"





void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0xE1;
    LATB = 0x7E;
    LATC = 0x40;

    /**
    TRISx registers
    */
    TRISA = 0xA1;
    TRISB = 0xA0;
    TRISC = 0xAE;

    /**
    ANSELx registers
    */
    ANSELC = 0x2E;
    ANSELB = 0x00;
    ANSELA = 0x00;
//
//    /**
//    WPUx registers
//    */
    WPUB = 0x00;
    INTCON2bits.nRBPU = 1;

//    ANSELA= 0b00000000;         //1：模拟  0：数字
//    TRISA = 0b10100001;         //0：输出，1：输入
//    PORTA = 0b11100001;         //初始状态:
//
//    ANSELB= 0b00000000;         //1：模拟  0：数字
//    TRISB = 0b1010000;         //0：输出，1：输入
//    PORTB = 0b01111110;         //初始状态：注意此版本NB有RELOAD和RESET管脚
//
//    ANSELC= 0b00101110;         //1：模拟  0：数字
//    TRISC = 0b10101110;         //0：输出，1：输入
//    PORTC = 0b01100001;         //初始状态:
//
//    RCONbits.IPEN = 1;          //使能中断优先级
//    INTCONbits.GIE = 0;         //关闭中断
//    INTCONbits.PEIE = 1;        //使能低优先级中断

}
  
//void PIN_MANAGER_IOC(void)
//{   
//	// Clear global Interrupt-On-Change flag
//    INTCONbits.RBIF = 0;
//}

/**
 End of File
*/