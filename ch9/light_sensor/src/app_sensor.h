#ifndef app_sensor_h_
#define app_sensor_h_

#include <stdbool.h>

// LDR module (LM393) digital output goes to this GPIO
#define LIGHT_DO_PIN 34

// What level DO gives when it is DARK.
// Most LM393 modules give 1 (HIGH) in the dark. If your result is
// backwards when we test, change this to 0.
#define LIGHT_DARK_LEVEL 1

typedef void (*light_changed_f)(bool);
void init_hw(light_changed_f);
bool is_light_low(void);

#endif