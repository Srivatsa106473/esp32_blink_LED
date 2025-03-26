/*
 * SPDX-FileCopyrightText: 2015-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 #include "unity.h"
 #include "freertos/FreeRTOS.h"
 #include "freertos/task.h"
 #include "driver/gpio.h"
 #include "esp_err.h"
 #include "esp_log.h"
 
 #define INBUILT_LED_GPIO_PIN 2
 
 esp_err_t err;
//  static const char *TAG = "LED_BLINK_TEST";

 void led_blink()
 {
     err = gpio_set_direction(INBUILT_LED_GPIO_PIN, GPIO_MODE_OUTPUT);
     if(err != ESP_OK)
     {
        ESP_LOGE("led_blink","check the mode for led pin ");
     }
     else
     {
        ESP_LOGI("led_blink","GPIO mode set to OUTPUT mode");
     }

     while (1)
     {
        // Turn the LED ON
        gpio_set_level(INBUILT_LED_GPIO_PIN, 1);
        ESP_LOGI("led_blink", "LED_ON");
        vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for 3 seconds
         
        // Turn the LED OFF
        gpio_set_level(INBUILT_LED_GPIO_PIN, 0);
        ESP_LOGI("led_blink", "LED_OFF");
        vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for 3 seconds
     }
 }
 
 TEST_CASE("led blinking", "[FreeRTOS-task]")
 {
     // Create the led_blink task
     xTaskCreate(led_blink, "blinking esp32 inbuilt led", 4096, NULL, 1, NULL);
     
     // Optionally, check the remaining stack size
     int stack_watermark = uxTaskGetStackHighWaterMark(NULL);
     ESP_LOGI("Stack", "Remaining stack: %d bytes", stack_watermark);
     if(stack_watermark < 0)
     {
        ESP_LOGE("TEST_CASE","Stack overflow.......");
     }
 }
 
 void app_main(void)
 {
    ESP_LOGI("app_main","starting app_main() function");
    esp_log_level_set("*", ESP_LOG_DEBUG);
     // Start Unity testing
     UNITY_BEGIN();
     unity_run_menu();  // This will start the test cases
     UNITY_END();  // End Unity testing
 }
 