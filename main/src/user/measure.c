/*
 * measure.c
 *
 *  Created on: 2018-02-13 22:57
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "board/fpga.h"

#define TAG "measure"

static void measure_task(void *pvParameter)
{
    ESP_LOGI(TAG, "started.");

    fpga_init_board();

    fpga_setpin_reset(0);
    vTaskDelay(100 / portTICK_RATE_MS);
    fpga_setpin_reset(1);
    vTaskDelay(100 / portTICK_RATE_MS);

    while (1) {
        uint32_t data_recv[2] = {0};

        fpga_read_conf(data_recv);

        ESP_LOGW(TAG, "gate_shift: %u, gate_total: %u", data_recv[0], data_recv[1]);

        fpga_read_data(data_recv);

        double sig_freq = (double)data_recv[0] / data_recv[1] * CONFIG_FPGA_REF_CLK_FREQ;

        ESP_LOGI(TAG, "sig_clk_cnt: %u, ref_clk_cnt: %u, sig_freq: %lf Hz", data_recv[0], data_recv[1], sig_freq);

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void measure_init(void)
{
    xTaskCreatePinnedToCore(measure_task, "measureT", 2048, NULL, 7, NULL, 1);
}
