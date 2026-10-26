#include "app_sw.h"
#include "esp_log.h"

#include <stddef.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

static bool m_status;

void init_hw(void)
{
    m_status = false;

    gpio_config_t io_conf;

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << RELAY_PIN);
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 1;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Relay module is active LOW: HIGH = relay OFF. Start with the relay OFF.
    gpio_set_level(RELAY_PIN, 1);
}

void switch_set(bool status)
{
    // Active LOW relay: ON = pin LOW, OFF = pin HIGH
    int level = status ? 0 : 1;

    gpio_set_level(RELAY_PIN, level);
    m_status = status;

    ESP_LOGI("switch", "switch_set: status=%d, GPIO%d level=%d",
             status, RELAY_PIN, gpio_get_level(RELAY_PIN));
}
bool switch_get(void)
{
    return m_status;
}
