/*
 * config_gpio.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Tuan_nguyenvan
 */
#include "config_clocks.h"
#include "config_gpio.h"

int gpio_init(GPIO_config_t *config)
{
    volatile uint32_t *pcr_reg;
    volatile uint32_t *pddr_reg;
    int status;

    if (config == NULL) {
        return ERROR;
    }

    if (config->pin > 31) {
        return ERROR;
    }

    status = clock_enable_port(config->port);
    if (status != SUCCESS) {
        return ERROR;
    }

    pcr_reg = &(config->port->PCR[config->pin]);
    pddr_reg = &(config->gpio->PDDR);

    *pcr_reg &= ~PORT_PCR_MUX_MASK;
    *pcr_reg |= PORT_PCR_MUX(1);


    if (config->direction == GPIO_OUTPUT) {
        /* Set bit to 1 for output */
        *pddr_reg |= (1U << config->pin);
    }
    else {
        /* Clear bit to 0 for input */
        *pddr_reg &= ~(1U << config->pin);
    }

    return SUCCESS;

}

/**
 * @brief Set GPIO ouput: 1 or 0
 */

int gpio_set_ouput(GPIO_Type *gpio, uint32_t pin, uint8_t status)
{
    volatile uint32_t *pdor_reg;

    /* Validate input */
    if (gpio == NULL || pin > 31) {
        return ERROR;
    }

    /* Get PDOR register address */
    pdor_reg = &(gpio->PDOR);

    if (status == GPIO_HIGH) {
        /* Set bit to 1 (High) */
        *pdor_reg |= (1U << pin);
    }
    else {
        /* Clear bit to 0 (Low) */
        *pdor_reg &= ~(1U << pin);
    }

    return SUCCESS;
}

/**
 * @brief get status gpio
 */

uint8_t gpio_get_status(GPIO_Type *gpio, uint32_t pin)
{
    volatile uint32_t *pdir_reg;
    uint32_t pin_value;

    if (gpio == NULL || pin > 31) {
        return 0;
    }

    /* Get PDIR register address */
    pdir_reg = &(gpio->PDIR);

    /* Read pin value */
    pin_value = *pdir_reg & (1U << pin);

    /* Return 1 if bit is set, 0 if cleared */
    return (pin_value != 0) ? 1U : 0U;
}

/**
 * @brief toggling state of gpio
 */

int toggle_gpio(GPIO_Type *gpio, uint32_t gpio_num)
{
    volatile uint32_t *ptor_reg;

    /* Validate input */
    if (gpio == NULL || gpio_num > 31) {
        return ERROR;
    }

    /* Get PTOR register address */
    ptor_reg = &(gpio->PTOR);

    /* Toggle pin by writing 1 to PTOR */
    *ptor_reg = (1U << gpio_num);

    return SUCCESS;
}
