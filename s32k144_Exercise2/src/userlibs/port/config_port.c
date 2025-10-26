/*
 * config_port.c
 *
 *  Created on: Oct 26, 2025
 *      Author: Admin
 */


#include "config_port.h"
#include "config_clocks.h"
/**
 * @brief Initializing a pin in a port
 * @param: struct Port_Config, number pin, Porttype
 * @return 0 if success, 1 if failure
 */

int port_init(const Port_Pin_Config_t *config, uint_8 pin, PORT_Type *port)
{
	uint32_t reg = 0u;

	reg |= PORT_PCR_MUX(config->port_mux);

	reg |= PORT_PCR_PE(config->port_pulling);

	reg |= PORT_PCR_IRQC(config->port_interrupt);

	base->PCR[pin] = reg;

	return 0;
}

/**
 * @brief config pin muxing
 * @param Port_MuxAlt_t, Port_Type, pin number
 * @return 0 if success, 1 if failure
 */

int port_muxing_init(Port_MuxAlt_t mux, uint_8 pin, PORT_TYPE *port)
{
	uint32_t reg = port->PCR[pin];

	reg |= PORT_PCR_MUX(config->port_mux);

	port->PCR[pin] = reg;

	return 0;
}

/**
 * @brief config pin pulling
 * @param Port_Pulling_t, PORT_TYPE, pin number
 * @return 0 if success, 1 if failure
 */

int port_pulling_init(Port_Pulling_t pulling, uint8_t pin, PORT_TYPE *port)
{
	uint32_t reg = port->PCR[pin];

	reg |= PORT_PCR_PE(config->port_pulling);

	port->PCR[pin] = reg;

	return 0;
}

/**
 * @brief config interrupt pin
 * @param PORT_InterruptConfig_t, pin number, PORT_TYPE
 * @return 0 if success, 1 if failure
 */
int port_interrupt_init(PORT_InterruptConfig_t type, uint8_t pin, PORT_TYPE *port)
{
	uint32_t reg = port->PCR[pin];

	reg |= PORT_PCR_IRQC(config->port_interrupt);

	port->PCR[pin] = reg;

	return 0;
}

/**
 * @brief clear flag interrupt
 * @param pin number, PORT_TYPE
 * @return 0 if success, 1 if failure
 */
int clear_interrupt_flag(uint8_t pin, PORT_Type *port)
{
	port->PCR[pin] |= PORT_PCR_ISF_MASK;
}

/**
 * @brief get interrupt flag
 * @param pin number, PORT_TYPE
 * @return true if set, false if clear
 */

bool get_interrupt_flag(uint8_t pin, PORT_Type *port)
{
	return (port->PCR[pin] & PORT_PCR_ISF_MASK) != 0u;
}

/**
 * @brief set default config pin
 * @param pin number, PORT_TYPE
 * @return 0 if success, 1 if failure
 */

int port_config_default(uint8_t pin, Port_Pin_Config_t *port)
{
	port->port_mux = PORT_MUX_GPIO;
	port->port_pulling = PORT_PULL_DISABLED;
	port->port_interrupt = PORT_INT_DISABLED;
}
