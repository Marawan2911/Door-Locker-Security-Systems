#include "buzzer.h" // Include buzzer header file
#include "gpio.h"   // Include GPIO header file

/*
 * Description:
 * Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * Turn off the buzzer through the GPIO.
 */
void Buzzer_init(){
    GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT); // Set the buzzer pin direction as output
}

/*
 * Description:
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void){
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID ,LOGIC_HIGH); // Set the buzzer pin to high logic level (turn on)
}

/*
 * Description:
 * Function to disable the Buzzer through the GPIO
 */
void Buzzer_off(void){
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID ,LOGIC_LOW); // Set the buzzer pin to low logic level (turn off)
}
