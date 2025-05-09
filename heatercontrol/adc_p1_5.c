#include "adc_p1_5.h"
void setpoint_init(void)
{
    P1SEL0 |= BIT5;    // Configure P1.5 as ADC input (A5)
    P1SEL1 |= BIT5;    // P1.5 is thermocouple input

    ADCCTL0 |= ADCSHT_2 | ADCON;      // ADC ON, sampling time = 16 ADC clocks
    ADCCTL1 |= ADCSHP;                // ADC sample-and-hold pulse mode
    ADCCTL2 &= ~ADCRES;               
    ADCCTL2 |= ADCRES_3;              // 12-bit conversion results (0-4095)

    ADCMCTL0 &= ~ADCINCH_15;          // Clear input channel bits
    ADCMCTL0 |= ADCINCH_5;            // A5 is input channel
}

unsigned int setpoint_read(void)
{
    ADCMCTL0 &= ~ADCINCH_15;          // Clear input channel bits
    ADCMCTL0 |= ADCINCH_5;            // A5 is input channel

    ADCCTL0 |= ADCENC | ADCSC;        // Enable and start conversion
    while (ADCCTL1 & ADCBUSY);        // Wait until conversion is done
    return ADCMEM0;                   // Read result
}
