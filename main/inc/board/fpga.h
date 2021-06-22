/*
 * fpga.h
 *
 *  Created on: 2020-06-25 22:01
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_BOARD_FPGA_H_
#define INC_BOARD_FPGA_H_

#include <stdint.h>

#include "chip/spi.h"

typedef enum {
    CONF_RD = 0x3a,
    DATA_RD = 0x3b
} fpga_cmd_t;

extern void fpga_init_board(void);

extern void fpga_setpin_dc(spi_transaction_t *);
extern void fpga_setpin_reset(uint8_t val);

extern void fpga_read_conf(uint32_t *buff);
extern void fpga_read_data(uint32_t *buff);

#endif /* INC_BOARD_FPGA_H_ */
