#ifndef ADC_P1_5_H
#define ADC_P1_5_H

#include <msp430.h>

// Initializes ADC on P1.5 (A5 channel)
void setpoint_init(void);

// Reads ADC value from P1.5 (A5 channel)
unsigned int setpoint_read(void);

#endif // ADC_P1_5_H
