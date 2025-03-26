/*
 * SPDX-FileCopyrightText: 2015-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "unity.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"

#define LED_PIN 2

esp_err_t err;

TEST_CASE("led blinking 3 seconds","[FreeRTOS-task1]")
{
    for(int i=0; i<=30; i++)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(100/portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

TEST_CASE("led blinking 6 seconds","[FreeRTOS-task2]")
{
    for(int i=0; i<=6; i++)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }    
}

void app_main(void)
{   
    esp_log_level_set("*", ESP_LOG_DEBUG);
    ESP_LOGI("app_main","starting app_main function....");

    gpio_pad_select_gpio(LED_PIN);
    if(LED_PIN != 2)
    {
        ESP_LOGI("app_main","selected GPIO pin number not inbuilt led pin");
    }
    else
    {
        ESP_LOGI("app_main","selected GPIO pin number: %d", LED_PIN);
    }

    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    ESP_LOGI("app_main","selected GPIO pin mode: GPIO_MODE_OUTPUT");

    UNITY_BEGIN();
    unity_run_menu();
    UNITY_END();
}