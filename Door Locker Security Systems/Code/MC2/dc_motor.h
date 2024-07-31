#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "gpio.h"
extern void PWM_Timer0_Start(uint8 duty_cycle);
#define DC_MOTOR_PORT PORTB_ID
#define DC_MOTOR_ENABLE_PIN PIN3_ID
#define DC_MOTOR_PIN_1 PIN0_ID
#define DC_MOTOR_PIN_2 PIN1_ID
typedef enum {STOP,CW,ACW}DcMotor_State;
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif
