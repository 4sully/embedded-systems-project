#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include <Status_LED.h>

void set_status_led(unsigned char value)
{
    if(value>7){
        value=0;
    }
    // Clear existing outputs (turn off all RGB pins first)
    P6OUT |= (BIT0 | BIT1 | BIT2);
    
    // Set outputs based on input bits
    if (value & BIT0) P6OUT &= ~BIT0;  // Red (P6.0)
    if (value & BIT1) P6OUT &= ~BIT1;  // Green (P6.1)
    if (value & BIT2) P6OUT &= ~BIT2;  // Blue (P6.2)
}