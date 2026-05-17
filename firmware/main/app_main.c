#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sensors.h"
#include "motor_control.h"
#include "tinyml_engine.h"

// External Telemetry Task Reference
extern void vMQTTTelemetryTask(void *pvParameters);
extern void telemetry_update_metrics(sensor_data_t data, uint8_t current_speed);

void vAIControlPipelineTask(void *pvParameters) {
    sensor_data_t shared_sensor_stream;
    uint8_t calculated_pwm = 0;

    // Peripherals Initializations
    sensors_init();
    motor_pwm_init();
    tinyml_init();

    while (1) {
        // 1. Fetch Sensor Streams
        if (sensors_read_all(&shared_sensor_stream) == ESP_OK) {
            
            // 2. Safety Thermal Evaluation
            motor_check_thermal_safety(shared_sensor_stream.temperature);

            // 3. Low-latency edge inference
            calculated_pwm = tinyml_predict_comfort(&shared_sensor_stream);

            // 4. Update PWM Duty Cycle
            motor_set_speed(calculated_pwm);

            // 5. Pipe metrics to network buffer
            telemetry_update_metrics(shared_sensor_stream, calculated_pwm);
        }

        // Standard FreeRTOS block for 100ms cycle
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}

void app_main(void) {
    // FreeRTOS standard scheduler using Dual-Core Capabilities of ESP32-S3
    xTaskCreatePinnedToCore(vAIControlPipelineTask, "AI_Inference_Core", 4096, NULL, 10, NULL, 1);
    xTaskCreatePinnedToCore(vMQTTTelemetryTask, "Telemetry_Core", 4096, NULL, 5, NULL, 0);
}