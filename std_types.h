/***********************************************************************************
 *File Name  : std_types.h
 *Description: Header file of common data types for AVR
 *Author     : Mohamed Abdelhamid
 ***********************************************************************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*we don't use the integer because it is compiler dependent*/
typedef unsigned char  			uint8;  	/*               0 ---> 255           */
typedef signed char    			sint8;		/*            -128 ---> 127           */
typedef unsigned short 			uint16;		/*               0 ---> 65535         */
typedef signed short   			sint16;		/*          -32768 ---> 32767         */
typedef unsigned long  			uint32;		/*               0 ---> 4,294,967,295 */
typedef signed long    			sint32;		/*   2,147,483,648 ---> 2,147,483,647 */
typedef unsigned long long 		uint64;		/*                0---> 18,446,744... */
typedef signed long long   		sint64;		/*   9,223,372,... ---> 9,223,372,... */
typedef float 					float32;
typedef double 					float64;

/*Boolean Data Type*/
typedef unsigned char 			boolean;

/*Boolean Values*/
#ifndef True
#define True  (1u)
#endif

#ifndef False
#define False (0u)
#endif

#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)

/*for null pointer*/
#define NULL  ((void*)0)

#endif /* STD_TYPES_H_ */
