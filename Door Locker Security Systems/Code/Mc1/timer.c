#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h" // Include the timer header file

/* Global variables to hold the address of the callback function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/* Interrupt Service Routine for Timer1 Compare Mode */
ISR(TIMER1_COMPA_vect)
{
    if(g_callBackPtr != NULL_PTR)
    {
        (*g_callBackPtr)(); /* Call the function g_callBackPtr(); */
    }
}

/* Interrupt Service Routine for Timer1 Overflow Mode */
ISR(TIMER1_OVF_vect)
{
    if(g_callBackPtr != NULL_PTR)
    {
        (*g_callBackPtr)(); /* Call the function g_callBackPtr(); */
    }
}

/* Function to initialize Timer1 with given configuration */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
    // Set timer1 initial count
    TCNT1 = Config_Ptr->initial_value;

    // Set the Compare value
    OCR1A = Config_Ptr->compare_value;

    // Configure timer control register TCCR1A
    // 1. Timer1 Mode
    // 2. Prescaler
    TCCR1A |= (1 << FOC1A); // Force Output Compare (FOC1A) enabled

    TCCR1B |= (Config_Ptr->mode << WGM12); // Set Timer1 mode

    TCCR1B |= (Config_Ptr->prescaler); // Set Timer1 prescaler

    // Enable Timer1 Compare A Interrupt
    TIMSK |= (1 << TOIE1);

    // Enable Timer1 Compare A Interrupt
    TIMSK = (1 << OCIE1A);
    // Enable global Interrupt
	SREG=(1<<7);
}

/* Function to deinitialize Timer1 */
void Timer1_deInit(void)
{
    // Stop Timer1
    TCCR1B = 0;
    TCCR1A = 0;
}

/* Function to set callback function for Timer1 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
    /* Save the address of the callback function in a global variable */
    g_callBackPtr = a_ptr;
}
