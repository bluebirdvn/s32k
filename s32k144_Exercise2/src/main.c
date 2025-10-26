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
#include "config_adc.h"
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

/* ----- Pin mapping ----- */
#define LED_RED_PIN     (0u)    /* PTD0  */
#define LED_GREEN_PIN   (15u)   /* PTD15 */
#define LED_BLUE_PIN    (16u)   /* PTD16 */


#define LED_HOLD_MS     (3000u)



static void delay_ms(uint32_t ms)
{
    volatile uint32_t k = 3000u;
    while (ms--) {
        for (volatile uint32_t i = 0; i < k; i++) {
            __NOP();
        }
    }
}

static int board_leds_init(void)
{
    int rc;

    rc = clock_enable_port((uint8_t)PCC_PORTD_INDEX);
    if (rc != 0) return rc;

    {
        Port_Pin_Config_t pdef;

        port_config_default(LED_RED_PIN, &pdef);
        pdef.port_mux      = PORT_MUX_GPIO;
        pdef.port_pulling  = PORT_PULL_DISABLED;
        pdef.port_interrupt= PORT_INT_DISABLED;

        /* PTD0 */
        rc = port_init(&pdef, (uint8_t)LED_RED_PIN, PORTD);
        if (rc != 0) return rc;

        /* PTD15 */
        rc = port_init(&pdef, (uint8_t)LED_GREEN_PIN, PORTD);
        if (rc != 0) return rc;

        /* PTD16 */
        rc = port_init(&pdef, (uint8_t)LED_BLUE_PIN, PORTD);
        if (rc != 0) return rc;
    }

    {
        GPIO_config_t g;

        /* PTD0 */
        g.port = PORTD;
        g.gpio = GPIOD;
        g.pin = LED_RED_PIN;
        g.direction = GPIO_OUTPUT;
        rc = gpio_init(&g);
        if (rc != 0) return rc;

        /* PTD15 */
        g.pin = LED_GREEN_PIN;
        rc = gpio_init(&g);
        if (rc != 0) return rc;

        /* PTD16 */
        g.pin = LED_BLUE_PIN;
        rc = gpio_init(&g);
        if (rc != 0) return rc;
    }


    gpio_set_ouput(GPIOD, LED_RED_PIN,   LED_OFF);
    gpio_set_ouput(GPIOD, LED_GREEN_PIN, LED_OFF);
    gpio_set_ouput(GPIOD, LED_BLUE_PIN,  LED_OFF);

    return 0;
}


static inline void led_show(uint8_t r, uint8_t g, uint8_t b)
{
    gpio_set_ouput(GPIOD, LED_RED_PIN,   r);
    gpio_set_ouput(GPIOD, LED_GREEN_PIN, g);
    gpio_set_ouput(GPIOD, LED_BLUE_PIN,  b);
}

int main(void)
{
    (void)clock_init();

    if (board_leds_init() != 0) {
        for (;;) { __NOP(); }
    }

    for (;;)
    {
        /* Red 3s */
        led_show(LED_ON,  LED_OFF, LED_OFF);
        delay_ms(LED_HOLD_MS);

        /* Green 3s */
        led_show(LED_OFF, LED_ON,  LED_OFF);
        delay_ms(LED_HOLD_MS);

        /* Blue 3s */
        led_show(LED_OFF, LED_OFF, LED_ON);
        delay_ms(LED_HOLD_MS);
    }

    return 0;
}
