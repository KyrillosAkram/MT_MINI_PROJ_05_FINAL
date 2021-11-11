 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 * contributer: Kyrillos Akram
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "gpio.h"

#define USE_ALL_MCU_FEATURES 0
#define USE_LEGACY_CODE 0

#define UART_PORT_ID PORTD_ID
#define UART_RX_PIN_ID PIN0_ID
#define UART_TX_PIN_ID PIN1_ID
#define UART_END_OF_DATA ('•')

typedef enum{
	UART_ASYNC_MODE_SPEED_NORMAL,
	UART_ASYNC_MODE_SPEED_DOUBLE
}UART_AsyncType;

typedef enum{
	UART_OPERATING_MODE_ASYNC,
	UART_OPERATING_MODE_SYNC
}UART_OperatingModeType;

typedef enum{
	UART_CHANNELS_OFF,
	UART_TX_ONLY,
	UART_RX_ONLY,
	UART_TX_RX
}UART_UsedChannelType;

typedef enum{
	UART_INTERRUPT_OFF,
	UART_INTERRUPT_ON
}UART_InterruptType;

#if (__AVR_ATmega16__ | __AVR_ATmega32__) & USE_ALL_MCU_FEATURES
typedef enum{
	UART_Data_Size_5_BITS,
	UART_Data_Size_6_BITS,
	UART_Data_Size_7_BITS,
	UART_Data_Size_8_BITS,
	UART_Data_Size_9_BITS=7
}UART_DataSizeType;
#endif

typedef enum{
	UART_PARITY_DISABLED,
	UART_PARITY_EVEN=2,
	UART_PARITY_ODD
}UART_ParityModeType;

typedef enum{
	UART_STOPBIT_1_BIT,
	UART_STOPBIT_2_BIT
}UART_StopBitType;


typedef struct{
	uint32 baudRate;
	UART_UsedChannelType usedChannel:2;
	UART_ParityModeType parityMode:2;
	UART_StopBitType stopBit:1;
	UART_OperatingModeType operatingMode:1;
	UART_AsyncType asyncMode:1;
	UART_InterruptType interruptStatus:3;
#if (__AVR_ATmega16__ | __AVR_ATmega32__) & USE_ALL_MCU_FEATURES
	UART_DataSizeType dataSize:3;
	uint8 :5;
#endif
}UART_configType;




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

#if USE_LEGACY_CODE
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(uint32 baud_rate);

#else
void UART_init(UART_configType* config_ptr);
#endif

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
