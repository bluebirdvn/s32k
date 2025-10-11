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
int clock_enable_port(PORT_Type *port)
{
	uint32_t pcc_index;
    volatile uint32_t *pcc_reg = NULL;

	if (port == IP_PORTA) {
		pcc_index = PCC_PORTA_INDEX;
	} else if (port == IP_PORTB) {
		pcc_index = PCC_PORTB_INDEX;
	} else if (port == IP_PORTC) {
		pcc_index = PCC_PORTC_INDEX;
	} else if (port == IP_PORTD) {
		pcc_index = PCC_PORTD_INDEX;
	} else if (port == IP_PORTE) {
		pcc_index = PCC_PORTE_INDEX;
	} else {
		return ERROR;
	}

	pcc_reg = &(IP_PCC->PCCn[pcc_index]);
	if (pcc_reg == NULL) {
		return 1;
	}

	*pcc_reg |= PCC_CGC_MASK;

	if (!(*pcc_reg & PCC_CGC_MASK)) {
		return ERROR;
	}

	return 0;
}
