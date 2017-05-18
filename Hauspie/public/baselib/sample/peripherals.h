/* This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by	 
 * the Free Software Foundation, either version 3 of the License, or	 
 * (at your option) any later version.					 
 * 									 
 *  is distributed in the hope that it will be useful,		 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	 
 * GNU General Public License for more details.				 
 * 									 
 * You should have received a copy of the GNU General Public License	 
 * along with .  If not, see <http://www.gnu.org/licenses/>.	 
 */
#ifndef __PERIPHERALS__H__
#define __PERIPHERALS__H__

#include <stdint.h>

/* PIN function selection */
#define PINSEL     ((volatile uint32_t*)0x4002C000) /* 11 words Array */
#define PINMODE    ((volatile uint32_t*)0x4002C040) /* 10 words Array */
#define PINMODE_OD ((volatile uint32_t*)0x4002C068) /* 5 words Array */

/* Can be used to make a pin from a port and pin
   For example, P0.3 is port 0, pin 3
*/
#define PIN_MAKE(port, pin) ((port) << 5 | (pin))
#define GET_PORT(pin) (((pin) >> 5) & 0x7)
#define GET_PIN(pin) ((pin) & 0x1F)

/* MBED Pins */
#define MBED_BASE_LED1  PIN_MAKE(1,18)
#define MBED_BASE_LED2  PIN_MAKE(1,20)
#define MBED_BASE_LED3  PIN_MAKE(1,21)
#define MBED_BASE_LED4  PIN_MAKE(1,23)

#define MBED_BASE_DIP5  PIN_MAKE(0,9)
#define MBED_BASE_DIP6  PIN_MAKE(0,8)
#define MBED_BASE_DIP7  PIN_MAKE(0,7)
#define MBED_BASE_DIP8  PIN_MAKE(0,6)
#define MBED_BASE_DIP9  PIN_MAKE(0,0)
#define MBED_BASE_DIP10 PIN_MAKE(0,1)
#define MBED_BASE_DIP11 PIN_MAKE(0,18)
#define MBED_BASE_DIP12 PIN_MAKE(0,17)
#define MBED_BASE_DIP13 PIN_MAKE(0,15)
#define MBED_BASE_DIP14 PIN_MAKE(0,16)
#define MBED_BASE_DIP15 PIN_MAKE(0,23)
#define MBED_BASE_DIP16 PIN_MAKE(0,24)
#define MBED_BASE_DIP17 PIN_MAKE(0,25)
#define MBED_BASE_DIP18 PIN_MAKE(0,26)
#define MBED_BASE_DIP19 PIN_MAKE(1,30)
#define MBED_BASE_DIP20 PIN_MAKE(1,31)
#define MBED_BASE_DIP21 PIN_MAKE(2,5)
#define MBED_BASE_DIP22 PIN_MAKE(2,4)
#define MBED_BASE_DIP23 PIN_MAKE(2,3)
#define MBED_BASE_DIP24 PIN_MAKE(2,2)
#define MBED_BASE_DIP25 PIN_MAKE(2,1)
#define MBED_BASE_DIP26 PIN_MAKE(2,0)
#define MBED_BASE_DIP27 PIN_MAKE(0,11)
#define MBED_BASE_DIP28 PIN_MAKE(0,10)
#define MBED_BASE_DIP29 PIN_MAKE(0,5)
#define MBED_BASE_DIP30 PIN_MAKE(0,4)


/* GPIO */
#define FIO0DIR (*((volatile uint32_t*) 0x2009C000))
#define FIO1DIR (*((volatile uint32_t*) 0x2009C020))
#define FIO2DIR (*((volatile uint32_t*) 0x2009C040))
#define FIO3DIR (*((volatile uint32_t*) 0x2009C060))
#define FIO4DIR (*((volatile uint32_t*) 0x2009C080))

#define FIO0MASK (*((volatile uint32_t*) 0x2009C010))
#define FIO1MASK (*((volatile uint32_t*) 0x2009C030))
#define FIO2MASK (*((volatile uint32_t*) 0x2009C050))
#define FIO3MASK (*((volatile uint32_t*) 0x2009C070))
#define FIO4MASK (*((volatile uint32_t*) 0x2009C090))

#define FIO0PIN (*((volatile uint32_t*) 0x2009C014))
#define FIO1PIN (*((volatile uint32_t*) 0x2009C034))
#define FIO2PIN (*((volatile uint32_t*) 0x2009C054))
#define FIO3PIN (*((volatile uint32_t*) 0x2009C074))
#define FIO4PIN (*((volatile uint32_t*) 0x2009C094))

#define FIO0SET (*((volatile uint32_t*) 0x2009C018))
#define FIO1SET (*((volatile uint32_t*) 0x2009C038))
#define FIO2SET (*((volatile uint32_t*) 0x2009C058))
#define FIO3SET (*((volatile uint32_t*) 0x2009C078))
#define FIO4SET (*((volatile uint32_t*) 0x2009C098))


#define FIO0CLR (*((volatile uint32_t*) 0x2009C01C))
#define FIO1CLR (*((volatile uint32_t*) 0x2009C03C))
#define FIO2CLR (*((volatile uint32_t*) 0x2009C05C))
#define FIO3CLR (*((volatile uint32_t*) 0x2009C07C))
#define FIO4CLR (*((volatile uint32_t*) 0x2009C09C))

#endif
