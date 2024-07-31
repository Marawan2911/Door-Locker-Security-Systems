#include "dc_motor.h"
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_PORT,DC_MOTOR_ENABLE_PIN,PIN_OUTPUT); 	//making portb pin3 as output pin (enable pin for motor)
	GPIO_setupPinDirection(DC_MOTOR_PORT,DC_MOTOR_PIN_1,PIN_OUTPUT);		//making portb pin0 as output pin (first input pin of the motor)
	GPIO_setupPinDirection(DC_MOTOR_PORT,DC_MOTOR_PIN_2,PIN_OUTPUT);		//making portb pin1 as output pin (second input pin of the motor)
	GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_1,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_2,LOGIC_LOW);					// stopping the motor at first.
}
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Start(speed);
	switch(state)
	{
		case STOP:
			GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_1,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_2,LOGIC_LOW);
			break;
		case CW:
			GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_1,LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_2,LOGIC_LOW);
			break;
		case ACW:
			GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_1,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_PORT,DC_MOTOR_PIN_2,LOGIC_HIGH);
			break;
	}
}
