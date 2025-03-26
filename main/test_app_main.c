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
 
 void blink_3_sec()
 {
    for(int i=0; i<=30; i++)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(100/portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(100/portTICK_PERIOD_MS);
        ESP_LOGI("blink_3_sec","blink-3-sec : %d",i);
        // taskYIELD();
    }
    ESP_LOGI("blink_3_sec","blinking 3 seconds completed");
    vTaskDelete(NULL);
 }

 void blink_6_sec()
 {
    for(int i=0; i<=6; i++)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        ESP_LOGI("blink_6_sec","blink-6-sec : %d",i);
        // taskYIELD();
         // Task is done, delete it
    }
    ESP_LOGI("blink_6_sec","blinking 6 seconds completed");
    vTaskDelete(NULL);
 }

 TEST_CASE("led blinking 3,6 seconds","[FreeRTOS-task1]")
 {
    xTaskCreate(blink_3_sec, "led blink for 3 sec", 4096, NULL, 1 ,NULL);
    xTaskCreate(blink_6_sec, "led blink for 6 sec", 4096, NULL, 2 ,NULL);
}
 
//  TEST_CASE("led blinking 6 seconds","[FreeRTOS-task2]")
//  {
//      err = xTaskCreate(blink_6_sec, "led blink for 6 sec", 4096, NULL, 1 ,NULL);
//      if(err != ESP_OK)
//      {
//          ESP_LOGE("TEST CASE", "error found at xTaskCreate - blink_6_sec function");
//      }
//      else
//      {
//          ESP_LOGI("TEST CASE", "executing xTaskCreate - blink_6_sec function");
//      }
//  }
 
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