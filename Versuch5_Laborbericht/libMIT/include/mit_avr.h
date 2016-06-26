/**
 * mit_avr.h
 *
 *  \author H. Frank - FB EIT - h_da
 *  \copyright 2013 by FB EIT - h_da
 */

#ifndef MIT_AVR_H_
#define MIT_AVR_H_

#if defined (__AVR_ATmega128__)
#  include <mit_avr/atmega128.h>
#elif defined (__AVR_ATmega32__)
#  include <mit_avr/atmega32.h>
#endif

#endif /* MIT_AVR_H_ */
