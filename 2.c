#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h."
void circle()
{
    while (1)
    {
        printf("Duong Xuan Anh Tu - 1852845\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void button()
{
    gpio_pad_select_gpio(GPIO_NUM_0);
    gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT);
    while (1)
    {
        if (!gpio_get_level(GPIO_NUM_0))
        {
            printf("ESP32\n");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void app_main(void)
{
    xTaskCreate(&circle, "Cyclic task", 2048, NULL, 1, NULL);
    xTaskCreate(&button, "Acyclic task", 2048, NULL, 1, NULL);
    printf("Restart\n");
}
