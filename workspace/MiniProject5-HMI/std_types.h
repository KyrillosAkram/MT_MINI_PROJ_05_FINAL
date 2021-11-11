/*
 * TODO documenting std_types.h
 *
 * Description: type target abstraction for AVR8
 *
 *  Created on: Oct 8, 2021
 *
 *      Author: Kyrillos
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*
 *						  Primitive data types
 */

typedef unsigned char bool;
typedef unsigned char boolean;

typedef char int8;
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef int int16;
typedef long int32;
typedef unsigned long uint32;
typedef long long int64;
typedef unsigned long long uint64;

typedef float float32;
typedef double float64;


/*
 *                  	User defined data types
 */

typedef struct s_byte{
	uint8 bit1 :1;
	uint8 bit2 :1;
	uint8 bit3 :1;
	uint8 bit4 :1;
	uint8 bit5 :1;
	uint8 bit6 :1;
	uint8 bit7 :1;
}s_byte;

typedef union u_byte{
	s_byte bits;
	uint8 data;
}byte;

/*                   	register defined data type
 * -------------------------------------------------------------------
 * description : for ease of handling any register or just unsigned
 * 				 char and give the developer the ability to work
 * 				 with register as unsigned char or each bit separately
 */
typedef byte register_t;
typedef byte u_register;

#endif /* STD_TYPES_H_ */
