#include "lcd.h"
#include "main_config.h"
#include "keypad.h"
#include"uart.h"
#include "std_types.h"
#include <util/delay.h>
#include "timer.h"
#include<avr/interrupt.h>
#include"gpio.h"
uint8 second_counter=0;
uint8 First_Pass[7];
uint8 Second_Pass[7];
uint8 Pass[7];
uint8 System_Mode =NORMAL_SYSTEM_MODE;
uint8 trials_counter=0;
Timer1_ConfigType Timerconfig={0,31250,Prescaler_256,ctc};
uint8 lol_status=PASSWORD_NOT_MATCH;
void Second_counter(void);
uint8 Create_Password(void);
uint8 Enter_password(void);
void Display_Options(void);
void Block_Mode(void);
int main()
{
	uint8 password_status=0xff;
	LCD_init();
	Timer1_setCallBack(Second_counter);
	UART_ConfigType UARTconfig={EIGHT,EVEN,ONE,9600};
	UART_init(&UARTconfig);
	while(password_status!=PASSWORD_CREATE_MATCH)
	{
		password_status=Create_Password();
	}
while(1){
	if(System_Mode==NORMAL_SYSTEM_MODE)
	{
		Display_Options();
	}
	else
	{
		Block_Mode();
	}
}

}
uint8 Create_Password(void)
{
	uint8 i;
	uint8 key=NOT_PRESSED;
	uint8 status;
	UART_sendByte(PASSWORD_CREATE_REQUEST);
	_delay_ms(5);
	UART_sendByte(FIRST_PASS_REQUEST);
	_delay_ms(5);
	for(i=0;i<5;i++)
	{
		LCD_displayStringRowColumn(0,0,"plz enter pass:");
		KEYPAD_WaitKey(&key);
		First_Pass[i]=key;
		LCD_displayStringRowColumn(1,i,"*");
	}
	First_Pass[5]='#';
	First_Pass[6]='\0';
	LCD_clearScreen();
	UART_sendString(First_Pass);
	_delay_ms(5);
	UART_sendByte(PASSWORD_CREATE_REQUEST);
	_delay_ms(5);
	UART_sendByte(SECOND_PASS_REQUEST);
	_delay_ms(5);
	for(i=0;i<5;i++)
		{
			LCD_displayStringRowColumn(0,0,"plz re-enter the:");
			LCD_displayStringRowColumn(1,0,"same pass:");
			KEYPAD_WaitKey(&key);
			Second_Pass[i]=key;
			LCD_displayStringRowColumn(1,10+i,"*");
		}
	Second_Pass[5]='#';
	Second_Pass[6]='\0';
	UART_sendString(Second_Pass);
	_delay_ms(5);
	status=UART_recieveByte();
	_delay_ms(5);
	return status;

}
uint8 Enter_password(void)
{
	uint8 i;
	uint8 key=NOT_PRESSED;
	uint8 status=0xFF;
	LCD_clearScreen();
	for(i=0;i<5;i++)
		{
			LCD_displayStringRowColumn(0,0,"plz enter pass:");
			KEYPAD_WaitKey(&key);
			Pass[i]=key;
			LCD_displayStringRowColumn(1,i,"*");
		}
	Pass[5]='#';
	Pass[6]='\0';
	UART_sendByte(PASSWORD_CHECK_REQUEST);
	_delay_ms(5);
	UART_sendString(Pass);
	_delay_ms(5);
	status=UART_recieveByte();
	_delay_ms(5);
	return status;
}
void Display_Options(void)
{
	uint8 key=NOT_PRESSED;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change Pass");
	KEYPAD_WaitKey(&key);
	if(key=='+')
		{
			while((trials_counter<3)&&(lol_status==PASSWORD_NOT_MATCH))
			{
				lol_status=Enter_password();
				LCD_clearScreen();
				if(lol_status==PASSWORD_MATCH)
					{
						Timer1_init(&Timerconfig);
						UART_sendByte(DOOR_OPEN_REQUEST);
						while(second_counter<15)
							{
								LCD_displayStringRowColumn(0,0,"Door is Unlocking");
							};
						second_counter=0;
						while(second_counter<2){
							LCD_clearScreen();
												};
						second_counter=0;
						while(second_counter<15)
							{
								LCD_displayStringRowColumn(0,0,"Door is Locking");
							};
						second_counter=0;
						Timer1_deInit();
						trials_counter=0;
					}
				else
					{
						trials_counter++;
					}
			}
			if((trials_counter==3)&&(lol_status==PASSWORD_NOT_MATCH))
				{
					System_Mode=BLOCK_SYSTEM_MODE;
				}
		}

	else if (key=='-')
		{
			while((trials_counter<3)&&(lol_status==PASSWORD_NOT_MATCH))
				{
					lol_status=Enter_password();
					LCD_clearScreen();
					if(lol_status==PASSWORD_MATCH)
						{
							while(lol_status!=PASSWORD_CREATE_MATCH)
								{
									lol_status=Create_Password();
								}
							trials_counter=0;
						}
					else
						{
							trials_counter++;
						}
				}
			if((trials_counter==3)&&(lol_status==PASSWORD_NOT_MATCH))
				{
					System_Mode=BLOCK_SYSTEM_MODE;
				}

		}
}
void Block_Mode(void)
{
	UART_sendByte(BUZZER_REQUEST);
	Timer1_init(&Timerconfig);
	LCD_clearScreen();
	LCD_displayString("ERROR");
	while(second_counter<60){}

	Timer1_deInit();
	second_counter=0;
	trials_counter=0;
	System_Mode=NORMAL_SYSTEM_MODE;
}
void Second_counter(void)
{

	second_counter++;

}
