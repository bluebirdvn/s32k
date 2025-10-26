/*
 * config_gpio.h
 *
 *  Created on: Oct 25, 2025
 *      Author: Admin
 */

#ifndef USERLIBS_GPIO_CONFIG_GPIO_H_
#define USERLIBS_GPIO_CONFIG_GPIO_H_

#include "S32K144.h"
#include "config_clocks.h"

/* GPIO Direction */
#define GPIO_INPUT   0U
#define GPIO_OUTPUT  1U

/* GPIO Level */
#define GPIO_LOW     0U
#define GPIO_HIGH    1U

typedef struct {
	GPIO_Type *gpio;
	PORT_Type *port;
	uint32_t pin;
	uint8_t direction;
} GPIO_config_t;
/**
 * @brief GPIO initializer
 * configure gpio as output or input
 */
int gpio_init(GPIO_config_t *config);

/**
 * @brief Set GPIO ouput: 1 or 0
 */

int gpio_set_ouput(GPIO_Type *gpio, uint32_t pin, uint8_t status);

/**
 * @brief get status gpio
 */

uint8_t gpio_get_status(GPIO_Type *gpio, uint32_t pin);

/**
 * @brief toggling state of gpio
 */

int toggle_gpio(GPIO_Type *gpio, uint32_t gpio_num);


#endif /* USERLIBS_GPIO_CONFIG_GPIO_H_ */
