#include "app_sensor.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "sensor"

static light_changed_f light_changed_cb = NULL;
static bool last_low = false;

// true = it is dark (light is low)
bool is_light_low(void)
{
    return gpio_get_level(LIGHT_DO_PIN) == LIGHT_DARK_LEVEL;
}

static void sensor_task(void *arg)
{
    // Give the BLE mesh stack a few seconds to start before we report anything
    vTaskDelay(pdMS_TO_TICKS(3000));

    last_low = is_light_low();
    ESP_LOGI(TAG, "start: light is %s", last_low ? "LOW (dark)" : "HIGH (bright)");

    while (1) {
        bool low = is_light_low();
        ESP_LOGI(TAG, "light is %s", low ? "LOW (dark)" : "HIGH (bright)");

        if (low != last_low) {
            last_low = low;
            if (light_changed_cb) {
                light_changed_cb(low);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void init_hw(light_changed_f cb)
{
    light_changed_cb = cb;

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LIGHT_DO_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
}