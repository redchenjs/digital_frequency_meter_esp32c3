/*
 * fpga.c
 *
 *  Created on: 2018-03-16 12:30
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "esp_log.h"

#include "driver/gpio.h"

#include "chip/spi.h"
#include "board/fpga.h"

#define TAG "fpga"

static spi_transaction_t spi_trans[2] = {0};

void fpga_init_board(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = BIT64(CONFIG_FPGA_DC_PIN) | BIT64(CONFIG_FPGA_RST_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = false,
        .pull_down_en = false,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "initialized, dc: %d, rst: %d", CONFIG_FPGA_DC_PIN, CONFIG_FPGA_RST_PIN);
}

void fpga_setpin_dc(spi_transaction_t *t)
{
    gpio_set_level(CONFIG_FPGA_DC_PIN, (int)t->user);
}

void fpga_setpin_reset(uint8_t val)
{
    gpio_set_level(CONFIG_FPGA_RST_PIN, val);
}

void fpga_read_conf(uint32_t *buff)
{
    spi_trans[0].length = 8;
    spi_trans[0].rxlength = 0;
    spi_trans[0].tx_data[0] = CONF_RD;
    spi_trans[0].rx_buffer = NULL;
    spi_trans[0].user = (void *)0;
    spi_trans[0].flags = SPI_TRANS_USE_TXDATA;

    spi_device_transmit(spi_host, &spi_trans[0]);

    spi_trans[1].length = 64;
    spi_trans[1].rxlength = 64;
    spi_trans[1].tx_buffer = NULL;
    spi_trans[1].rx_buffer = (uint8_t *)buff;
    spi_trans[1].user = (void *)1;
    spi_trans[1].flags = 0;

    spi_device_transmit(spi_host, &spi_trans[1]);
}

void fpga_read_data(uint32_t *buff)
{
    spi_trans[0].length = 8;
    spi_trans[0].rxlength = 0;
    spi_trans[0].tx_data[0] = DATA_RD;
    spi_trans[0].rx_buffer = NULL;
    spi_trans[0].user = (void *)0;
    spi_trans[0].flags = SPI_TRANS_USE_TXDATA;

    spi_device_transmit(spi_host, &spi_trans[0]);

    spi_trans[1].length = 64;
    spi_trans[1].rxlength = 64;
    spi_trans[1].tx_buffer = NULL;
    spi_trans[1].rx_buffer = (uint8_t *)buff;
    spi_trans[1].user = (void *)1;
    spi_trans[1].flags = 0;

    spi_device_transmit(spi_host, &spi_trans[1]);
}
