/*
 * config_clocks.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Tuan_nguyenvan
 */

#include "config_clocks.h"



/**
 * @brief Initialize System Clocks
 * @return 0 if success, 1 if error
 * @In this project, we set to default setting of MCU
 */

int clock_init(void)
{
	return 0;
}

/**
 * @brief Enable Port Clocks
 * @return 0 if success, 1 if error
 */
int clock_enable_port(uint8_t port_index)
{
    volatile uint32_t *pcc_reg = NULL;

	pcc_reg = &(IP_PCC->PCCn[port_index]);
	if (pcc_reg == NULL) {
		return 1;
	}

    if (!(pcc_reg & PCC_PR_MASK)) {
    	return ERROR;
    }

	*pcc_reg |= PCC_CGC_MASK;

	if (!(*pcc_reg & PCC_CGC_MASK)) {
		return ERROR;
	}

	return 0;
}



/**
 * @brief Disable Port Clocks
 * @return 0 if success, 1 if error
 */
int clock_disable_port(uint8_t port_index)
{
    volatile uint32_t *pcc_reg = NULL;

    pcc_reg = &(IP_PCC->PCCn[port_index]);

    if (pcc_reg == NULL)
    		return ERROR;

    if (!(pcc_reg & PCC_PR_MASK)) {
    	return ERROR;
    }

    *pcc_reg &= ~(PCC_CGC_MASK);

    return 0;
}
