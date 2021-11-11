/*==============================================================
 * File name  : common_macros.h
 *
 * Description: header file contains common used macro functions
 * 				and static const, generic for any 8bit register
 *
 *  Created on: Oct 8, 2021
 *
 *      Author: Kyrillos
 *
 *        Note: safe macros and not make conflicts but any defined
 *        		macro before disable this header macros
 *
 *==============================================================*/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*--------------------------- macro constant ---------------------------*/
#ifndef TRUE
	#define TRUE (1u)
#endif

#ifndef FALSE
	#define FALSE (0u)
#endif

#ifndef ON
	#define ON (1u)
#endif

#ifndef OFF
	#define OFF (0u)
#endif

#ifndef NULL
	#define NULL ((void*)(0u))
#endif

#ifndef LOGIC_HIGH
	#define LOGIC_HIGH (1u)
#endif

#ifndef LOGIC_LOW
	#define LOGIC_LOW (0u)
#endif

#ifndef OUTPUT
	#define OUTPUT (1u)
#endif

#ifndef INPUT
	#define INPUT (0u)
#endif

#ifndef UNDEFINED
	#define UNDEFINED (-1u)
#endif

#ifndef loop_for_ever
	#define loop_for_ever for(;;)
#endif

#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)

/*----------------------------------------------------------------------*/


/*----------------------- macro functions ----------------------*/

/*To check if a certain bit is cleared or not in a 8bit register*/
#ifndef BIT_IS_CLEAR
	#define BIT_IS_CLEAR(REG,BIT_NUM) (!(((REG))&(1<<(BIT_NUM))))
#endif

/*To check if a certain bit is set or not in a 8bit register*/
#ifndef BIT_IS_SET
	#define BIT_IS_SET(REG,BIT_NUM)  ((REG)&(1<<(BIT_NUM)))
#endif

/*To make a rotating shift to left*/
#ifndef RTL
	#define RTL(REG,NUM_OF_SHIFT) ((REG)=(((REG)<<(NUM_OF_SHIFT))|((REG)>>(8-(NUM_OF_SHIFT)))));
#endif

/*To make a rotating shift to right*/
#ifndef RTR
	#define RTR(REG,NUM_OF_SHIFT) ((REG)=(((REG)>>(NUM_OF_SHIFT))|((REG)<<(8-(NUM_OF_SHIFT)))));
#endif

/*To set a certain bit in register */
#ifndef SET_BIT
	#define SET_BIT(REG,BIT_NUM) ((REG)|=(1<<(BIT_NUM)));
#endif

/*To set a certain bit in register */
#ifndef CLEAR_BIT
	#define CLEAR_BIT(REG,BIT_NUM) ((REG)&=~(1<<(BIT_NUM)));
#endif

/*To toggle a certain bit in given register */
#ifndef TOGGLE_BIT
	#define TOGGLE_BIT(REG,BIT_NUM) ((REG)^=(1<<(BIT_NUM)));
#endif

#define FIRST_BITS_HIGH(NUM) ((1<<(NUM))-1)

#define BIT_MASK(NUM) (1<<(NUM))

#define REGESTER_INSERT_BIT(REG,BIT_NUM,BOOLEAN_DATA) (REG)=((((REG)&(~(1<<(BIT_NUM))))|((BOOLEAN_DATA)<<(BIT_NUM))));

#define REGESTER_INSERT_SUCCESSIVE_BITS(REG,BIT_NUM,NUM_BITS,DATA) (REG)=(((((REG)&(~(((1<<(NUM_BITS))-1)<<(BIT_NUM))))|(((1<<(NUM_BITS))-1)&(DATA))<<(BIT_NUM))));
/*----------------------------------------------------------------------*/




#endif /* COMMON_MACROS_H_ */
