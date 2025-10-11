/*
 * config.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Tuan_nguyenvan
 */

#ifndef CONFIG_CLOCKS_H_
#define CONFIG_CLOCKS_H_

#include "S32K144.h"
#include <stddef.h>



/* PCC Register Bit Definitions */
#define PCC_CGC_MASK     0x40000000U  /* Clock Gate Control bit */

typedef enum {
	SUCCESS = 0,
	ERROR,
} Rvalue_t;

/**
 * @brief Initialize System Clocks
 * @return 0 if success, 1 if error
 */
int clock_init(void);

/**
 * @brief Enable Port Clocks
 * @return 0 if success, 1 if error
 */
int clock_enable_port(PORT_Type *port);


#endif /* CONFIG_CLOCKS_H_ */
