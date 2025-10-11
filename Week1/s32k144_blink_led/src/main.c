/* Copyright 2023 NXP */
/* License: BSD 3-clause
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "S32K144.h"

#include "config_gpio.h"
#include "config_clocks.h"
#include "s32_core_cm4.h"
#include <stdio.h>

#if defined (__ghs__)
    #define __INTERRUPT_SVC  __interrupt
    #define __NO_RETURN _Pragma("ghs nowarning 111")
#elif defined (__ICCARM__)
    #define __INTERRUPT_SVC  __svc
    #define __NO_RETURN _Pragma("diag_suppress=Pe111")
#elif defined (__GNUC__)
    #define __INTERRUPT_SVC  __attribute__ ((interrupt ("SVC")))
    #define __NO_RETURN
#else
    #define __INTERRUPT_SVC
    #define __NO_RETURN
#endif


#define GPIO_PD_0 0u
#define GPIO_PD_15 15u
#define GPIO_PD_16 16u



void gpio_config_t(GPIO_config_t *config, GPIO_Type *type, PORT_Type *port, uint32_t num_gpio, uint8_t direction)
{
	config->port = port;
	config->gpio = type;
	config->pin = num_gpio;
	config->direction = direction;
}


void delay_ms(uint32_t ms)
{
    for (volatile uint32_t i = 0; i < 4000 * ms; i++) { NOP(); }
}


int main(void) {

	GPIO_config_t pin0, pin15, pin16;

	gpio_config_t(&pin0, IP_PTD, IP_PORTD, GPIO_PD_0, GPIO_OUTPUT);
	gpio_config_t(&pin15, IP_PTD, IP_PORTD, GPIO_PD_0, GPIO_OUTPUT);
	gpio_config_t(&pin16, IP_PTD, IP_PORTD, GPIO_PD_0, GPIO_OUTPUT);

	gpio_init(&pin0);
	gpio_init(&pin15);
	gpio_init(&pin16);

	gpio_set_ouput(IP_PTD, GPIO_PD_0, GPIO_HIGH);
	gpio_set_ouput(IP_PTD, GPIO_PD_15, GPIO_HIGH);
	gpio_set_ouput(IP_PTD, GPIO_PD_16, GPIO_HIGH);

	for (;;) {
		gpio_set_ouput(IP_PTD, GPIO_PD_0, GPIO_LOW);

		delay_ms(3000);

		gpio_set_ouput(IP_PTD, GPIO_PD_0, GPIO_HIGH);
		gpio_set_ouput(IP_PTD, GPIO_PD_15, GPIO_LOW);

		delay_ms(3000);

		gpio_set_ouput(IP_PTD, GPIO_PD_15, GPIO_HIGH);
		gpio_set_ouput(IP_PTD, GPIO_PD_16, GPIO_LOW);

		delay_ms(3000);

		gpio_set_ouput(IP_PTD, GPIO_PD_16, GPIO_HIGH);
	}

	return 0;
}


