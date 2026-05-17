#include "sensors.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "TELEMETRY_SYSTEM";

static sensor_data_t local_metrics;
static uint8_t active_speed = 0;

void telemetry_update_metrics(sensor_data_t data, uint8_t current_speed) {
    local_metrics = data;
    active_speed = current_speed;
}

void vMQTTTelemetryTask(void *pvParameters) {
    while (1) {
        // Simulating telemetry frame broadcast over network pipelines
        ESP_LOGI(TAG, "[Telemetry Update] Temp: %.2f°C | Motion: %s | Fan PWM: %d", 
                 local_metrics.temperature, 
                 local_metrics.motion_detected ? "Active" : "None", 
                 active_speed);
        
        vTaskDelay(pdMS_TO_TICKS(5000)); // Stream every 5 seconds 
    }
}