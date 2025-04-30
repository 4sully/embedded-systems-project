#include <msp430.h>
#include "adc_p1_4.h"

void adc_init_p1_4(void)
{
    // Set P1.4 as analog input (A4)
    P1SEL0 |= BIT4;
    P1SEL1 |= BIT4;
    
    // Turn on ADC, set sample-and-hold time
    ADCCTL0 |= ADCSHT_2 | ADCON;         // Sampling time 16 ADC clocks, ADC ON
    ADCCTL1 |= ADCSHP;                   // Use sampling timer
    ADCCTL2 &= ~ADCRES;                  
    ADCCTL2 |= ADCRES_1;                 // 10-bit resolution (0-1023)

    ADCMCTL0 |= ADCINCH_4;               // Select channel A4 (P1.4)
}

unsigned int adc_read_p1_4(void)
{
    ADCCTL0 |= ADCENC | ADCSC;            // Enable and start conversion
    while (!(ADCIFG));                    // Wait for the ADC flag (conversion done)
    return ADCMEM0;                       // Return the result
}
