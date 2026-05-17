#ifndef SENSORS_H
#define SENSORS_H

#include "esp_err.h"
#include <stdbool.h>

// Struct to store fused sensor telemetry
typedef struct {
    float temperature;
    float humidity;
    bool motion_detected;
    int ambient_light;
} sensor_data_t;

// Function declarations
void sensors_init(void);
esp_err_t sensors_read_all(sensor_data_t *data);

#endif // SENSORS_H