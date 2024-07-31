#include "uart.h"
#include "std_types.h"
#include "main_config.h"
#include "timer.h"
#include "external_eeprom.h"
#include "I2C.h"
#include "PWM.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "gpio.h"
#include"dc_motor.h"
void Second_counter(void);
uint8 second_counter=0;
uint8 First_Pass[6];
uint8 Second_Pass[6];
uint8 Pass[6];
Timer1_ConfigType Timerconfig={0,31250,Prescaler_256,ctc};
int main()
{
	uint8 request=NO_REQUEST;
	uint8 internal_request=NO_REQUEST;
	uint8 i;
	uint8 flag;
	uint8 Password=0;
	Timer1_setCallBack(Second_counter);
	UART_ConfigType UARTconfig={EIGHT,EVEN,ONE,9600};
	UART_init(&UARTconfig);
	TWI_ConfigType twi_config = { 10, 400000, PRESCALER_1 };
	TWI_init(&twi_config);
	Buzzer_init();
	DcMotor_Init();
	while(1)
	{
		request=UART_recieveByte();
		switch(request)
		{
			case PASSWORD_CREATE_REQUEST:
					internal_request=UART_recieveByte();
					switch(internal_request)
					{
						case FIRST_PASS_REQUEST:
							UART_receiveString(First_Pass);
							break;
						case SECOND_PASS_REQUEST:
							UART_receiveString(Second_Pass);
							for(i=0;i<5;i++)
								{
									if(First_Pass[i]!=Second_Pass[i])
										{
											UART_sendByte(PASSWORD_CREATE_NOT_MATCH);
											break;
										}
									else
										{
											flag=EEPROM_writeByte(PASSWORD_ADDRESS+i,First_Pass[i]);
											_delay_ms(10);
											if(i==4)
											{
												UART_sendByte(PASSWORD_CREATE_MATCH);
											}
										}
								}
							break;
					}
					break;
			case PASSWORD_CHECK_REQUEST:
				UART_receiveString(Pass);
				for(i=0;i<5;i++)
				{
					EEPROM_readByte(PASSWORD_ADDRESS+i,&Password);
					if(Password!=Pass[i])
					{
						UART_sendByte(PASSWORD_NOT_MATCH);
						break;
					}
					else
					{
						if(i==4)
						{
						UART_sendByte(PASSWORD_MATCH);
						}
					}
				}
					break;
			case DOOR_OPEN_REQUEST:
					DcMotor_Rotate(CW,50);
					_delay_ms(15000);
					DcMotor_Rotate(STOP,0);
					_delay_ms(2000);
					DcMotor_Rotate(ACW,50);
					_delay_ms(15000);
				break;
			case BUZZER_REQUEST:
					Buzzer_on();
					_delay_ms(60000);
					Buzzer_off();
					break;
		}
	}
}
void Second_counter(void)
{

	second_counter++;

}

