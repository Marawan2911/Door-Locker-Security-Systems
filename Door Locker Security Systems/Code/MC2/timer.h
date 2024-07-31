#ifndef TIMER_H_
#define TIMER_H_

#include"common_macros.h"
#include "std_types.h"




typedef enum
{
	Normal,ctc
}Timer1_Mode;


typedef enum
{
	Noclock,Prescaler_1,Prescaler_8,Prescaler_64,Prescaler_256,Prescaler_1024
}Timer1_Prescaler;





typedef struct {
     uint16 initial_value;
     uint16 compare_value; // it will be used in compare mode only.
     Timer1_Prescaler prescaler;
     Timer1_Mode mode;
} Timer1_ConfigType;

// Function prototypes
void Timer1_init(const Timer1_ConfigType * Config_Ptr); // Initialize Timer1 with given configuration
void Timer1_deInit(void); // Deinitialize Timer1
void Timer1_setCallBack(void(*a_ptr)(void)); // Set callback function for Timer1

#endif /* TIMER_H_ */

