#include "adc_thermocouple.h"
#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>

void thermocouple_init(void)
{
    P1SEL0 |= BIT3;    // Configure P1.3 as ADC input (A3)
    P1SEL1 |= BIT3;     //p1.3 is thermocouple input

    ADCCTL0 |= ADCSHT_2 | ADCON;      // ADC ON, sampling time = 16 ADC clocks
    ADCCTL1 |= ADCSHP;                // ADC sample-and-hold pulse mode
    ADCCTL2 &= ~ADCRES;               
    ADCCTL2 |= ADCRES_3;              // 12-bit conversion results

    ADCMCTL0 |= ADCINCH_3;            // A3 is input channel
}

unsigned int thermocouple_read(void)
{
    ADCMCTL0 &= ~ADCINCH_15;          // Clear input channel bits
    ADCMCTL0 |= ADCINCH_3;            // A3 is input channel
    ADCCTL0 |= ADCENC | ADCSC;         // Enable and start conversion
    while (ADCCTL1 & ADCBUSY);          // Wait until conversion is done
    return ADCMEM0;                    // Read result
}
