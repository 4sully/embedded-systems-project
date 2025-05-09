#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include "servo_pwm.h"

unsigned int deg2us(unsigned int deg);

void setup_servo_pwm_p2_1(unsigned int degrees)
{
    unsigned int width_us = deg2us(degrees);

    // Configure GPIO for P5.0
    P5DIR |= BIT0;                            // Set P2.1 as output
    P5SEL0 |= BIT0;
    P5SEL1 &= ~BIT0;

    // Timer2_B1 setup on CCR1
    TB2CCR0 = 20000 - 1;                        // 20ms period (50Hz for servo)
    TB2CCTL1 = OUTMOD_7;                        // CCR1 reset/set
    TB2CCR1 = width_us;                         // Pulse width in microseconds
    TB2CTL = TBSSEL__SMCLK | MC__UP | TBCLR;    // SMCLK, up mode, clear timer
}


unsigned int deg2us(unsigned int deg){//0-180degrees to 500-2500us
    unsigned int us = 500;
    us= us+ deg*(2000/180);
    return us;
}