/***********************************************************************************
 *File Name  : common_macros.h
 *Description: Header file of common Macros for bits operations
 *Author     : Mohamed Abdelhamid
 ***********************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*to give the bit value 1*/
#define SET_BIT(REG,Bit)         (REG |= (1<<Bit))
/*to give the bit value 0*/
#define CLEAR_BIT(REG,Bit)       (REG &= (~(1<<Bit)))
/*to toggle the current bit value*/
#define TOGGLE_BIT(REG,Bit)      (REG ^= (1<<Bit))
/*to get the the bit value at the register*/
#define GET_BIT(REG,Bit)	     ((REG & (1<<Bit)) >> Bit)
/*to to check if the bit is set (if bit value is 1)*/
#define BIT_IS_SET(REG,Bit)      (REG & (1<<Bit))
/*to check if the bit is cleared (if bit value is 0)*/
#define BIT_IS_CLEARED(REG,Bit)  ( !(REG & (1<<Bit)) )

#endif /* COMMON_MACROS_H_ */
