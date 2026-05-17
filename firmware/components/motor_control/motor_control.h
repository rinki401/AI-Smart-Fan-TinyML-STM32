#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>

void motor_pwm_init(void);
void motor_set_speed(uint8_t duty_cycle);
void motor_check_thermal_safety(float current_motor_temp);

#endif // MOTOR_CONTROL_H