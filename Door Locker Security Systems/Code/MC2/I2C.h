 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: mohamm
 *
 *******************************************************************************/ 

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
/*******************************************************************************
 *                              Type  Definitions                                  *
 ******************************************************************************/

typedef uint8 TWI_Address;
typedef uint32 TWI_BaudRate;
typedef enum{
	PRESCALER_1, PRESCALER_4, PRESCALER_16, PRESCALER_64
}TWI_Prescaler;


typedef struct{
TWI_Address address;
TWI_BaudRate bit_rate;
TWI_Prescaler prescaler;
}TWI_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* function is used for initializing the TWI
 *
 *
 */
void TWI_init(const TWI_ConfigType * Config_Ptr);
/* function is used for Start trasnmit with the TWI
 *
 *
 */
void TWI_start(void);
/* function is used for Stop trasnmit with the TWI
 *
 *
 */
void TWI_stop(void);
/* function is used for Send byte with the TWI
 *
 *
 */
void TWI_writeByte(uint8 data);
/* function is used for read byte with ACK using TWI
 *
 *
 */

uint8 TWI_readByteWithACK(void);
/* function is used for read byte with NACK using TWI
 *
 *
 */
uint8 TWI_readByteWithNACK(void);
/* function is used for getting the status of TWI
 *
 *
 */
uint8 TWI_getStatus(void);


#endif /* I2C_H_ */
