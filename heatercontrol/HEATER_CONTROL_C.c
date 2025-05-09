#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include "servo_pwm.h" //servo control
#include  "HEATER_CONTROL_H.h"
#include "adc_thermocouple.h" //thermocouple reading#
#include <stdbool.h>
#include "adc_p1_4.h"
#include "adc_p1_5.h"

void gpio_init(void)
{
    // P1.2 = input (call for heat-CFH)
    P1DIR &= ~BIT2;
    //P1REN |= BIT2;
    //P1OUT |= BIT2;

    //P1.3 = input,thermocouple for flame sense
    P1DIR &= ~BIT3;
    //P1OUT |= BIT3;

    // P2.0 = ignitor, P2.5 = solenoid
    P2DIR |= BIT0 | BIT5;
    P2OUT &= ~(BIT0 | BIT5); // Make sure they're off

    P6DIR |= (BIT0 | BIT1 | BIT2);  // Set RGB pins as outputs
    P6OUT |= (BIT0 | BIT1 | BIT2);  // Start with all OFF (pins high)

}

void system_startup(void)
{
    thermocouple_init();//sets up ADC to read thermocouple
    while(1){
        set_status_led(4);//blue
        P2OUT |= BIT0;   // Ignitor ON
        P2OUT |= BIT5;   // Solenoid ON
        __delay_cycles(2000000);  // Wait 2s @ 1MHz
        bool is_flame_proved = false;
        is_flame_proved=(thermocouple_read() > 10);//value tbd after testing and finetuning
        if(is_flame_proved){
            break;
        }else{
            set_status_led(6);//cyan
            P2OUT &= ~BIT0;//ignitor off
            P2OUT &= ~BIT5;//solenoid closed
            __delay_cycles(10000000);//retry delay set to 10s
        }
    }
    setup_servo_pwm_p2_1(180); // Rotate servo to full open
    __delay_cycles(2000000);  // stabilize main flame
    P2OUT &= ~BIT0;//ignitor off
    P2OUT &= ~BIT5;//solenoid closed

}

void system_run(void)
{
    setpoint_init();
    adc_init_p1_4();
    set_status_led(2);//green
    while (P1IN & BIT2)//active cfh
    {
       unsigned int current_temp = adc_read_p1_4();
       unsigned int setpoint_val = setpoint_read();
       if(current_temp < setpoint_val){
        setup_servo_pwm_p2_1(45);
       }
       else{
        setup_servo_pwm_p2_1(90);
       }
    }
}