#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LED_PIN 12

void app_main() {
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); 
    while(1){
        ESP_LOGI("LED", "Turning on!!"); 
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "Turning off!!"); 
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
