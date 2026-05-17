#ifndef TINYML_ENGINE_H
#define TINYML_ENGINE_H

#include "sensors.h"
#include <stdint.h>

void tinyml_init(void);
uint8_t tinyml_predict_comfort(const sensor_data_t *data);

#endif // TINYML_ENGINE_H