#include "Status_LED.h"
#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include "HEATER_CONTROL_H.h"


int main(void){

    WDTCTL = WDTPW | WDTHOLD;     // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;     // Unlock GPIOs

    gpio_init();                  // Set all pins correctly

    while (1)
    {
        //=== IDLE STATE ===
        while (!(P1IN & BIT2))  // While CFH is LOW, stay idle
        {
            set_status_led(7);
            __delay_cycles(500000);
            set_status_led(0);
            __delay_cycles(500000);
        }

        // === STARTUP STATE ===
        __delay_cycles(100000);
        system_startup();       // CFH is HIGH now, do startup sequence
        set_status_led(5);//purple
        __delay_cycles(1000);
       // === RUN STATE ===
        system_run();           // Keep running until CFH goes LOW

       // === RETURN TO IDLE ACTIONS ===
        setup_servo_pwm_p2_1(90);   // Reset servo back to idle position
        P2OUT &= ~BIT5;             // Turn solenoid OFF (if needed)
    }
    return 0;
}