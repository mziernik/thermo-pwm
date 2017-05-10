/*
 * IncFile1.h
 *
 * Created: 2015-10-25 10:42:57
 *  Author: User
 */


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define true 1
#define false 0


// MACROS FOR EASY PIN HANDLING FOR ATMEL GCC-AVR
//these macros are used indirectly by other macros , mainly for string concatination
#define _SET(type,name,bit)          type ## name  |= _BV(bit)
#define _CLEAR(type,name,bit)        type ## name  &= ~ _BV(bit)
#define _TOGGLE(type,name,bit)       type ## name  ^= _BV(bit)
#define _GET(type,name,bit)          ((type ## name >> bit) &  1)
#define _PUT(type,name,bit,value)    type ## name = ( type ## name & ( ~ _BV(bit)) ) | ( ( 1 & (unsigned char)value ) << bit )

//these macros are used by end user
#define OUTPUT(pin)         _SET(DDR, pin)
#define INPUT(pin)          _CLEAR(DDR, pin)
#define HIGH(pin)           _SET(PORT, pin)
#define LOW(pin)            _CLEAR(PORT, pin)
#define TOGGLE(pin)         _TOGGLE(PORT, pin)
#define READ(pin)           _GET(PIN, pin)
#define PUT(pin, value)     _PUT(PIN, pin, value)

//  #define PIN(pin, state) if (state) HIGH(pin); else LOW(pin);

#endif /* INCFILE1_H_ */