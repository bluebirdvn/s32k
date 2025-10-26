/*
 * config_port.h
 *
 *  Created on: Oct 25, 2025
 *      Author: Admin
 */

#ifndef USERLIBS_PORT_CONFIG_PORT_H_
#define USERLIBS_PORT_CONFIG_PORT_H_

#include "S32K144.h"
#include <stdbool.h>
typedef enum {
    PORT_MUX_DISABLED = 0u,    /* Pin disabled */
    PORT_MUX_GPIO     = 1u,    /* GPIO functionality */
    PORT_MUX_ALT2     = 2u,    /* Alternative 2 */
    PORT_MUX_ALT3     = 3u,    /* Alternative 3 */
    PORT_MUX_ALT4     = 4u,    /* Alternative 4 */
    PORT_MUX_ALT5     = 5u,    /* Alternative 5 */
    PORT_MUX_ALT6     = 6u,    /* Alternative 6 */
    PORT_MUX_ALT7     = 7u     /* Alternative 7 */
} Port_MuxAlt_t;

typedef enum {
	NO_PULLING = 0u,
	PULL_UP    = 1u,
	PULL_DOWN  = 2u
} Port_Pulling_t;


typedef enum {
    PORT_INT_DISABLED       = 0x0u,  /* Interrupt disabled */
    PORT_INT_DMA_RISING     = 0x1u,  /* DMA request on rising edge */
    PORT_INT_DMA_FALLING    = 0x2u,  /* DMA request on falling edge */
    PORT_INT_DMA_EITHER     = 0x3u,  /* DMA request on either edge */
    PORT_INT_LOGIC_ZERO     = 0x8u,  /* Interrupt when logic 0 */
    PORT_INT_RISING_EDGE    = 0x9u,  /* Interrupt on rising edge */
    PORT_INT_FALLING_EDGE   = 0xAu,  /* Interrupt on falling edge */
    PORT_INT_EITHER_EDGE    = 0xBu,  /* Interrupt on either edge */
    PORT_INT_LOGIC_ONE      = 0xCu   /* Interrupt when logic 1 */
} PORT_InterruptConfig_t;


typedef struct {
	Port_MuxAlt_t port_mux;
	Port_Pulling_t port_pulling;
	PORT_InterruptConfig_t port_interrupt;
} Port_Pin_Config_t;


/**
 * @brief Initializing a pin in a port
 * @param: struct Port_Config, number pin, Porttype
 * @return 0 if success, 1 if failure
 */

int port_init(const Port_Pin_Config_t config, uint_8 pin, PORT_Type *port);

/**
 * @brief config pin muxing
 * @param Port_MuxAlt_t, Port_Type, pin number
 * @return 0 if success, 1 if failure
 */

int port_muxing_init(Port_MuxAlt_t mux, uint_8 pin, PORT_TYPE *port);

/**
 * @brief config pin pulling
 * @param Port_Pulling_t, PORT_TYPE, pin number
 * @return 0 if success, 1 if failure
 */

int port_pulling_init(Port_Pulling_t pulling, uint8_t pin, PORT_TYPE *port);

/**
 * @brief config interrupt pin
 * @param PORT_InterruptConfig_t, pin number, PORT_TYPE
 * @return 0 if success, 1 if failure
 */
int port_interrupt_init(PORT_InterruptConfig_t type, uint8_t pin, PORT_TYPE *port);

/**
 * @brief clear flag interrupt
 * @param pin number, PORT_TYPE
 * @return 0 if success, 1 if failure
 */
int clear_interrupt_flag(uint8_t pin, PORT_Type *port);

/**
 * @brief get interrupt flag
 * @param pin number, PORT_TYPE
 * @return true if set, false if clear
 */

bool get_interrupt_flag(uint8_t pin, PORT_Type *port);

/**
 * @brief set default config pin
 * @param pin number, PORT_TYPE
 * @return 0 if success, 1 if failure
 */

int port_config_default(uint8_t pin, PORT_Type *port);

#endif /* USERLIBS_PORT_CONFIG_PORT_H_ */
