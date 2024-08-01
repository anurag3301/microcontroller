#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define BUTTON_PIN 23
#define LED_PIN 12

void app_main() {
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    bool led_state = true;

    while(1){
        if(gpio_get_level(BUTTON_PIN) == 0){
            led_state = !led_state;
            ESP_LOGI("Button State Switch", "%d", led_state);
            gpio_set_level(LED_PIN, led_state);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}
