/**
  ADC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc.c

  @Summary
    This is the generated driver implementation file for the ADC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for ADC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F25K22
        Driver Version    :  2.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc.h"
#include "device_config.h"

/*Sliding filter object*/
sideparm gside[MAX_CHANNEL] = 
{   
    {true,{0.0f},&gside[0].sidebuff[0], 0.0f},
    {true,{0.0f},&gside[1].sidebuff[0], 0.0f},
    {true,{0.0f},&gside[2].sidebuff[0], 0.0f}
};

adc_handle_t adc[] = 
{
    {ADC_VBAT, 0x00, &gside[0], false, 0U},
    {ADC_CITY_POWER , 0x00, &gside[1], false, 0U},
    {ADC_GEN_POWER , 0x00, &gside[2], false, 0U}
};
//adc_channel_t adc_currentCh = Ch_Battery;

/**
  Section: ADC Module APIs
*/

void (*ADC_InterruptHandler)(void);

void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface
    
    // TRIGSEL CCP5; NVCFG VSS; PVCFG FVRbuf2; 
    ADCON1 = 0x00; 
    
    // ADFM right; ACQT 20; ADCS FOSC/64; 
    ADCON2 = 0xBE; 
    
    // ADRESL 0; 
    ADRESL = 0x00;
    
    // ADRESH 0; 
    ADRESH = 0x00;
    
    // GO_nDONE stop; ADON enabled; CHS AN0; 
    ADCON0 = 0x01;
    
    // Enabling ADC interrupt.
//    PIE1bits.ADIE = 1;
	
	// Set Default Interrupt Handler
    ADC_SetInterruptHandler(ADC_DefaultInterruptHandler);
}

void ADC_SelectChannel(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;  
}

void ADC_StartConversion(void)
{
    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
}


bool ADC_IsConversionDone(void)
{
    // Start the conversion
    return ((bool)(!ADCON0bits.GO_nDONE));
}

adc_result_t ADC_GetConversionResult(void)
{
    // Conversion finished, return the result
     return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

adc_result_t ADC_GetConversion(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE)
    {
    }
//    printf("finished !\r\n");
    // Stop on the ADC module
    ADCON0bits.ADON = 0;
    // Conversion finished, return the result
    return (((adc_result_t)((ADRESH << 8) + ADRESL)) & 0x3FF);
}

void ADC_TemperatureAcquisitionDelay(void)
{
    __delay_us(200);
}

void ADC_ISR(void)
{
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
	
	if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}

void ADC_SetInterruptHandler(void (* InterruptHandler)(void)){
    ADC_InterruptHandler = InterruptHandler;
}

void ADC_DefaultInterruptHandler(void){
    // add your ADC interrupt custom code
    // or set custom function using ADC_SetInterruptHandler()
//    adc[gChannelId].adc_done_flag = true;
}

/*Get AD sampling value*/
//uint16_t Get_AdcValue(void)
//{
//    return ((ADRESH<<8) + ADRESL) & 0x3FF;
//}
/**
 End of File
*/