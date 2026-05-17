#include "motor_control.h"
#include "driver/ledc.h"
#include "esp_log.h"

static const char *TAG = "MOTOR_CTRL";

#define MOTOR_PWM_PIN       GPIO_NUM_18
#define MAX_TEMP_THRESHOLD  45.0f  // Critical cutoff temperature

void motor_pwm_init(void) {
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_8_BIT, // Range 0 to 255
        .freq_hz          = 5000,             // 5kHz frequency to remove buzzing noise
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = MOTOR_PWM_PIN,
        .duty           = 0,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    ESP_LOGI(TAG, "Hardware PWM channel loaded.");
}

void motor_set_speed(uint8_t duty_cycle) {
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty_cycle));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
}

void motor_check_thermal_safety(float current_motor_temp) {
    if (current_motor_temp >= MAX_TEMP_THRESHOLD) {
        ESP_LOGE(TAG, "CRITICAL DETECTED: Fan casing temperature reached %.2f C! Initiating Trip.", current_motor_temp);
        motor_set_speed(0); // Immediately cut-off power 
        // System enters fail-safe block till manually cleared
    }
}