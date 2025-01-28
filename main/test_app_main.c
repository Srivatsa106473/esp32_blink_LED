#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "unity.h"

// Builtin LED GPIO pin for ESP32
#define LED_GPIO_PIN 2

// Function to toggle the LED 
void toggle_led(bool state) {
    gpio_set_level(LED_GPIO_PIN, state);
}

// Setup Unity Test Framework
void setUp(void) {
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);
}

// Unity Test for turning on the LED
void test_toggle_led_on(void) {
    toggle_led(true);
    TEST_ASSERT_EQUAL(1, gpio_get_level(LED_GPIO_PIN)); // Check if the LED is ON
}

// Unity Test for turning off the LED
void test_toggle_led_off(void) {
    toggle_led(false);
    TEST_ASSERT_EQUAL(0, gpio_get_level(LED_GPIO_PIN)); // Check if the LED is OFF
}

// Main application entry point
void app_main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_toggle_led_on);  // Run test for turning the LED on
    RUN_TEST(test_toggle_led_off); // Run test for turning the LED off
    UNITY_END();

    // Main application loop to blink the LED
    while (1) {
        toggle_led(true);  // Turn on the LED
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        toggle_led(false); // Turn off the LED
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
